/*
 * lab6main.c
 *
 *  Created on: Feb 25, 2020
 *      Author: kylusp
 */


#include "adc.h"

#include "lcd.h"

#include "Timer.h"

#include <math.h>
#include <stdio.h>

int main(void){

    adc_init();
    timer_init();
    lcd_init();

    int digitalvalue;
    double distance;
    int interval = 0;
    while(1){
        digitalvalue = adc_read();
        //printf("digitalvalue: %d\n", digitalvalue);
        double value1 = digitalvalue / 22801.0;
        double value2 = -1.12612;
        //printf("value1: %f\n", value1);
       // printf("value2: %f\n", value2);
        double result = pow(value1 ,value2);
       // printf("result: %f\n", result);
        //distance = 2665.1 * exponential;
        //printf("%d\n", digitalvalue);
        //printf("%f\n", distance);
        char toPrint[20];
        sprintf(toPrint,"%d, %f", digitalvalue, result);
        if(interval == 500){
            lcd_clear();
            lcd_printf(toPrint);
            interval = 0;
        }
        interval++;

    }

}
