/*
 * movement.h
 *
 *  Created on: Jan 28, 2020
 *      Author: kylusp
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_
#include "open_interface.h"

double move_forward(oi_t *sensor_data, double distance_mm);


double turn_right(oi_t*sensor, double degrees);
double turn_left(oi_t*sensor, double degrees);

#endif /* MOVEMENT_H_ */
