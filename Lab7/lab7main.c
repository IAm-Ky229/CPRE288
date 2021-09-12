/*
 * lab7main.c
 *
 *  Created on: Mar 13, 2020
 *      Author: kylusp
 */

#include "ping.h"
#include "lcd.h"
#include "Timer.h"


main(void){


int stagger = 0;
float distance = 0;

    timer_init();
    lcd_init();
    ping_init();

    while(1){

        //Get sensor reading
        distance = ping_getDistance();

        //Don't print every time (too fast)
        if(stagger == 10){
        printf("DELTA IN MAIN: %f\n", distance);
        //lcd_printf("%.5f", result);
        stagger = 0;
        }
        stagger++;


    }

}
