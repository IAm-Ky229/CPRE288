/**
 * lab4_template.c
 *
 * Template file for CprE 288 lab 4
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 *
 * @author Phillip Jones, updated 6/4/2019
 */

#include "button.h"
#include "timer.h"
#include "lcd.h"
#include <string.h>

#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART1)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1

#include "cyBot_Scan.h"  // For scan sensors


#warning "Possible unimplemented functions"
#define REPLACEME 0


void printToConsole(char* toPrintOut);

main(void) {
	button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();

  // initialize the cyBot UART1 before trying to use it

	//cyBot_uart_init_PHJ_first_half();


  // (Uncomment ME for PuTTy to CyBot UART init part of lab)
	cyBot_uart_init_clean();  // Clean UART initialization, before running your UART GPIO init code

	// Complete this code for configuring the GPIO PORTB part of UART1 initialization (your UART GPIO init code)
     SYSCTL_RCGCGPIO_R |= 0b00000010;
	   while ((SYSCTL_PRGPIO_R & 0b00000010) == 0) {};
     GPIO_PORTB_AFSEL_R |= 0b00000011;
     GPIO_PORTB_PCTL_R &= 0xFFFFFFEE;     // Force 0's in the desired locations
     GPIO_PORTB_PCTL_R |= 0x00000011;     // Force 1's in the desired locations
		 // Or see the notes for a coding alternative to assign a value to the PCTL field
     GPIO_PORTB_DEN_R |= 0b00000011;
     GPIO_PORTB_DIR_R &= ~0b00000010;      // Force 0's in the desired locations
     GPIO_PORTB_DIR_R |= 0b00000010;      // Force 1's in the desired locations

    //(Uncomment ME for UART init part of lab)
		cyBot_uart_init_last_half();  // Complete the UART device configuration

	// Initialze scan sensors
    cyBOT_init_Scan();
    cyBOT_Scan_t data;


	// YOUR CODE HERE
    char toPrint1[] = "Angle";
    char toPrint2[] = "PING Distance";
    char toPrint3[] = "IR raw value";
    int k;
    for(k = 0; k < 5; k++){
        cyBot_sendByte(toPrint1[k]);
    }
    cyBot_sendByte('\t');
    for(k = 0; k < 13; k++){
            cyBot_sendByte(toPrint2[k]);
        }
    cyBot_sendByte('\t');
    for(k = 0; k < 12 ; k++){
            cyBot_sendByte(toPrint3[k]);
        }
    cyBot_sendByte('\n');
    cyBot_sendByte('\r');

	while(1)
	{
	    if(cyBot_getByte_blocking() == 'm'){

	        int i;
	        char bruh[80];
	        char* format = "%d\t%lf\t%d\n\r";
	        for(i = 0; i <= 180; i+= 5){
	            cyBOT_Scan(i, &data);
	            sprintf(bruh,format, i, data.sound_dist, data.IR_raw_val);
	            printToConsole(bruh);


//	            cyBot_sendByte('\t');
//	            sprintf(bruh2,%f,data.sound_dist);
//	            printToConsole(bruh2);
//	            cyBot_sendByte('\t');
//	            sprintf(bruh3,%d,data.IR_raw_val);
//	            printToConsole(bruh3);
//cyBot_sendByte('\n');
	        }
	        cyBot_sendByte('\r');

	    }

      // YOUR CODE HERE


	}

}

void printToConsole(char* toPrintOut)
{
    int k;
    for(k = 0; k < strlen(toPrintOut); k++){
                cyBot_sendByte(toPrintOut[k]);
            }
}
