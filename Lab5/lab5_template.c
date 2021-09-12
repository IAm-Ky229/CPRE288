/**
 * lab5_template.c
 *
 * Template file for CprE 288 Lab 5
 *
 * @author Diane Rover, 2/15/2020
 *
 */

#include "Timer.h"
#include "lcd.h"
#include "cyBot_Scan.h"  // For scan sensors
#include "uart.h"
#include <stdio.h>

// Uncomment or add any include directives that are needed
#include "open_interface.h"
// #include "movement.h"
#include "button.h"


#warning "Possible unimplemented functions"
#define REPLACEME 0


int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	uart_init();
    cyBOT_init_Scan();
    char c;

//    uart_sendChar('E');
//    char returned = uart_receive();
//
//    printf("character: %c", returned);

	while(1)
	{
	    c = uart_receive();
	    printf("character: %c", c);
	    uart_sendChar(c);
      // YOUR CODE HERE


	}

}
