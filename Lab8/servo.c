/*
 * servo.c
 *
 *  Created on: Apr 7, 2020
 *      Author: Admin
 */


#include "servo.h"
#include "Timer.h"
#include "lcd.h"
#include <stdio.h>

main(void) {
    timer_init();
    servo_init();

    printf(servo_move(90)); //move to 90 degrees
    timer_waitMillis(1000); //wait 1 second
    printf(servo_move(30)); //move to 30 degrees
    timer_waitMillis(1000); //wait 1 second
    printf(servo_move(150)); //move to 150 degrees
    timer_waitMillis(1000); //wait 1 second
    printf(servo_move(90)); //move back to 90 degrees

}

void servo_init(void) {

    //intialization of system timer
    SYSCTL_RCGCTIMER_R |= 0b10;
    while ((SYSCTL_PRTIMER_R & 0b10) == 0) {}

    //initialization of GPTM
    TIMER1_CTL_R &= ~0x100; //Ensure the TBEN bit is clear before modifying the CFG register
    TIMER1_CTL_R &= 0x4000; //Since the signal is inverted we need to uninvert it
    TIMER1_CFG_R |= 0x4; // Timer config set so Timer mode register controls it
    TIMER1_TBMR_R |= 0b1010; //Turns on the PWM (mode register)
    TIMER1_TBPR_R |= 0x4; //Extends the timer of TBILR the extra 3 bits we need (timer prescale register)
    TIMER1_TBILR_R |= 0xE200; //Sets the interval load with the least significant 16 bits (timer interval load)

    //for the PWM period were using a time of 20ms which is 320,000 clock cycles
    //This is 4E200 in hex which is what is inputed to the timer

    //initialize GPIO port B pin 5
    SYSCTL_RCGCGPIO_R |= 0b10;
    while((SYSCTL_PRGPIO_R & 0b10) == 0) {}
    GPIO_PORTB_AFSEL_R |= 0b100000;
    GPIO_PORTB_PCTL_R |= 0x700000;
    GPIO_PORTB_DEN_R |= 0b100000;

    TIMER1_CTL_R |= 0x100; //turn on the timer
}

int servo_move(float degrees) {

    // 1 ms is 16000 clock cycles

    //we only have 1 ms to work with so out formula for the remaining time is
    // (degrees/180) * 16000 so 90degrees would be 8000 + 16000 as expected
    int moveTime = startTime + ((degrees/180) * 16000);
    TIMER1_TBMATCHR_R = moveTime;

    return moveTime; // returns the move time for debugging and fulfills the requirements.
}

