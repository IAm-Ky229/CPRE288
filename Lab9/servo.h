/*
 * servo.h
 *
 *  Created on: Apr 7, 2020
 *      Author: Admin
 */

#ifndef SERVO_H_
#define SERVO_H_
#include <stdbool.h>
#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#define startTime 9000

void servo_init(void);
int servo_move(float degrees);


#endif /* SERVO_H_ */
