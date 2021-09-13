/*
 * main.h
 *
 *  Created on: Apr 21, 2020
 *      Author: Admin
 */

#ifndef MAIN_H_
#define MAIN_H_
#include "Timer.h"
#include "lcd.h"
#include <math.h>
#include "ping.h"
#include <stdio.h>
#include "servo.h"
#include "adc.h"

typedef struct obj {
    int startAngle;
    int endAngle;
    double distance;
    double radialWidth;
} obj;

void OWO(void);
void superInit(void);
void calculateRadialWidth(obj objects[]);


#endif /* MAIN_H_ */
