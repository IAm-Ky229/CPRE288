/*
 * main.c
 *
 *  Created on: Apr 21, 2020
 *      Author: Admin
 */

#include "Timer.h"
#include "lcd.h"
#include <math.h>
#include "ping.h"
#include <stdio.h>
#include "servo.h"
#include "adc.h"
#include "main.h"

int IRdigitalValue;
float IRdistance;
float LastIRdistance;
float PINGdistance;
int objectCounter = 0;
float degreeIncrement = 2.0; //this controls how precise the measurements are

obj objects[5]; // were assuming no more than 6 objects but you can change this without the program breaking

main(void) {

    superInit();
    OWO();
    calculateRadialWidth(objects);

}


//Look at the README for a logic tree
void OWO(void) {
    LastIRdistance = 0;
    float degrees;
    for (degrees = 0; degrees < 180; degrees += degreeIncrement) { //loops through 180 degrees looking for objects
        servo_move(degrees); //should move by 2

        //IR sensor stuff
        IRdigitalValue = adc_read();
        IRdistance = pow((IRdigitalValue/11363.0),(1/-0.629)); //this is the equation configuration for the sensor on the bot, to get accurate data change the equation
        //IRdistance is in cm

        //Ping sensor stuff
        PINGdistance = ping_getDistance(); //changes the the pingDistance know as "delta"

        //Data check
        if (IRdistance > 15 && IRdistance < 80) { //values in cm. If this check is true it means we found the start of a new object
            if (LastIRdistance == 0) {
                //Start of a new object
                objects[objectCounter].startAngle = degrees; // we know this has to be the first object since LastIRdistance is 0 so we don't increment objectCounter
                //since were starting an object get its distance
                objects[objectCounter].distance = PINGdistance;
            } else {
                if (LastIRdistance > 15 && LastIRdistance < 80) { // checks if its within our tolerance for the same object
                    if ((IRdistance > (LastIRdistance - 10)) && (IRdistance < (LastIRdistance + 10))) {
                        //do nothing
                    } else {
                        //end the last object and start a new one
                        objects[objectCounter].endAngle = (degrees - degreeIncrement);
                        objectCounter++;
                        objects[objectCounter].startAngle = degrees;
                        //since were starting an object get its distance
                        objects[objectCounter].distance = PINGdistance;
                    }
                }
                else {
                    // we make a new object
                    objectCounter++;
                    objects[objectCounter].startAngle = degrees;
                    //since were starting an object get its distance
                    objects[objectCounter].distance = PINGdistance;
                }
            }

        } else {
            if (LastIRdistance > 15 && LastIRdistance < 80) {
                //end the object
                objects[objectCounter].endAngle = (degrees - degreeIncrement);
            } else {
                //do nothing
            }
        }

        LastIRdistance = IRdistance;
    }
}

void superInit(void) {
    servo_init();
    adc_init();
    ping_init();
    timer_init();
    lcd_init();
}

void calculateRadialWidth(obj objects[]) {
    int length = sizeof(objects);
    int counter = 0;
    while (counter < length) {

            float theta = (objects[counter].endAngle - objects[counter].startAngle);
            objects[counter].radialWidth = objects[counter].distance * (2*(22/7)*theta); //arclength formula
    }
}



