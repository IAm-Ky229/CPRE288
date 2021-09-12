/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Description: Added timer_init call, and including Timer.h
 */

#include "Timer.h"
#include "lcd.h"


int main (void) {

	timer_init(); // Initialize Timer, needed before any LCD screen functions can be called 
	              // and enables time functions (e.g. timer_waitMillis)

	lcd_init();   // Initialize the LCD screen.  This also clears the screen. 


	char str[] = {"                    Microcontrollers are lots of fun!"};
	//33

	char copy[20];
	int k;
	for(k = 0; k < 20; k++){
	    copy[k] = str[k];
	}
int move = 0;
	while(1){
	    lcd_printf(copy);
	    //for(int i = 0; i < strlen(copy); i++) {
	    //lcd_printf(copy);
	   // }
	    int j;
	    move++;
	    for(j = 0; j < 20; j++) {
	                copy[j] = str[j + move];
	            }
	    if(strlen(copy) == 0){
//	        lcd_init();
	        lcd_clear();
	        int i;
	        for(i = 0; i < 20; i++) {
	                copy[i] = str[i];
	            }
	        move = 0;
	    }
	    timer_waitMillis(300);
	}

	// Print "Hello, world" on the LCD

	// lcd_puts("Hello, world"); // Replace lcd_printf with lcd_puts
        // step through in debug mode and explain to TA how it works
    
	// NOTE: It is recommended that you use only lcd_init(), lcd_printf(), lcd_putc, and lcd_puts from lcd.h.
       // NOTE: For time functions, see Timer.h

	return 0;
}
