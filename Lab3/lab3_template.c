/**
 * lab3_template.c
 * 
 * Template file for CprE 288 lab 3
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

#include "button.h"
#include "Timer.h"
#include "lcd.h"
#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity,  COM1

#warning "Possible unimplemented functions"
#define REPLACEME 0



int main(void) {

	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	button_init();
	            // Don't forget to initialize the cyBot UART before trying to use it
	
	// YOUR CODE HERE
	
	printf("got here");
	while(1)
	{
	button_getButton();
      // YOUR CODE HERE

	
	}
	
}
