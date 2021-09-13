/*
 * ping.c
 *
 *  Created on: Mar 10, 2020
 *      Author: kylusp
 */
#include "lcd.h"
#include "Timer.h"
#include <stdio.h>
#include "ping.h"

 volatile float rising_edge = 0;
 volatile float falling_edge = 0;
 volatile float delta = 0;
 volatile int edge = 1;
 volatile int interruptstatus = 0;


 // extern float distance;

void ping_handler(void){
    TIMER3_ICR_R |= 0x400; // clear the interrupt

    float rising;
    float falling;
		//If edge equals one, we know we hit a positive edge
        if(edge == 1){
            rising_edge = TIMER3_TBR_R;
  			//Our next edge will be negative
            edge = 0;
        }
		//If edge equals zero, we know we hit a negative edge
        else if(edge == 0){
            falling_edge = TIMER3_TBR_R;
			
			//We can now compute delta

            delta = rising_edge - falling_edge;

            interruptstatus = 1;

            //Our next edge will be positive
            edge = 1;
        }

    }

void ping_init(){

		//Initialize timer
        SYSCTL_RCGCTIMER_R |= 0b1000;
        while((SYSCTL_PRTIMER_R) & 0b1000 == 0){}

        // shut off the timer while configuring
        TIMER3_CTL_R &= ~0x100;
        // 16 bit mode
        TIMER3_CFG_R |= 0x4;
        // edge-time, capture mode
        TIMER3_TBMR_R |= 0x7;
        // count-down
		TIMER3_TBMR_R &= ~0x08;
		// starting value to count down from
        TIMER3_TBILR_R |= 0xFFFF;
        // prescalar
        TIMER3_TBPR_R |= 0xFF;
        // enable interrupt mask
        TIMER3_IMR_R |= 0x400;
        // count both edges
        TIMER3_CTL_R |= 0xC00;
        TIMER3_ICR_R |= 0x400;

		//Initialize GPIO port B
        SYSCTL_RCGCGPIO_R |= 0b10;
        while((SYSCTL_PRGPIO_R & 0b10) == 0) {}
        GPIO_PORTB_AFSEL_R |= 0b1000;
        GPIO_PORTB_PCTL_R |= 0x7000;
		GPIO_PORTB_DEN_R |= 0b1000;

		//Enable interrupts for timer 3
        NVIC_EN1_R |= 0x10;
		NVIC_PRI9_R |= 0x20;

		//Enable global interrupts and assign ISR
        IntRegister(INT_TIMER3B,ping_handler);

        IntMasterEnable();
    }
	
    void ping_trigger(){
		
		//Disable timer 3
        TIMER3_CTL_R &= ~0x300;
		//TIMER3_IMR_R &= ~0x400;

		//Make port B an output, disable alternate function
        GPIO_PORTB_AFSEL_R &= ~0x08;
        GPIO_PORTB_DIR_R |= 0b1000;

        GPIO_PORTB_DATA_R &= ~0x08;
        timer_waitMicros(1000);

		//Pulse to enable sensor
        GPIO_PORTB_DATA_R |= 0b1000;
        timer_waitMicros(10);
        GPIO_PORTB_DATA_R &= ~0x08;

        //Make port B an input from timer, enable alternate function
        GPIO_PORTB_DIR_R &= ~0x08;
        GPIO_PORTB_AFSEL_R |= 0b1000;

        //Enable timer interrupts
        TIMER3_IMR_R |= 0x400;
        TIMER3_ICR_R |= 0x400;
        //Re-enable timer 3
        TIMER3_CTL_R |= 0x100;

    }
	
    float ping_getDistance(){
        float distance = 0; //this lies as well
		
		//Enable sensor
        ping_trigger();
		
		//While we haven't detected both edges
        while(!interruptstatus){}

        distance = (((1/delta)/2) * 0.000001) * 0.0343;
        // (1/delta) = time, divide by 2 and multiply 0.000001 to convert to microseconds, multiply by the speed of sound per microsecond

        interruptstatus = 0;
        return distance;
		 
    }


