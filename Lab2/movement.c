/*
 * movement.c
 *
 *  Created on: Jan 28, 2020
 *      Author: kylusp
 */
#include "open_interface.h"
#include "movement.h"


double move_forward(oi_t *sensor_data, double distance_mm) {
    double sum = 0;
    oi_setWheels(500,500);
        while(sum < distance_mm){
            if(sensor_data->bumpLeft){
                double sum2 = 0;
                oi_setWheels(-500,-500);

                while(sum2 > -150){
                    oi_update(sensor_data);
                    sum2 += sensor_data -> distance;
                }
                oi_setWheels(0,0);
                turn_right(sensor_data, 75.0);
                move_forward(sensor_data, 250);
                turn_left(sensor_data, 75.0);
                oi_setWheels(500,500);
            }
            if(sensor_data-> bumpRight){
                double sum2 = 0;
                                oi_setWheels(-500,-500);

                                while(sum2 > -150){
                                    oi_update(sensor_data);
                                    sum2 += sensor_data -> distance;
                                }
                                oi_setWheels(0,0);
                                turn_left(sensor_data, 75);
                                                move_forward(sensor_data, 250);
                                                turn_right(sensor_data, 75);
                                                oi_setWheels(500,500);
            }

            if((sensor_data-> bumpRight) && (sensor_data-> bumpLeft)){
                double sum2 = 0;
                               oi_setWheels(-500,-500);

                               while(sum2 > -150){
                                   oi_update(sensor_data);
                                   sum2 += sensor_data -> distance;
                               }
                               oi_setWheels(0,0);
                               turn_right(sensor_data, 75.0);
                               move_forward(sensor_data, 250);
                               turn_left(sensor_data, 75.0);
                               oi_setWheels(500,500);
            }
            oi_update(sensor_data);
            sum += sensor_data -> distance;
        }
        oi_setWheels(0,0);

        return 0;
        }


double turn_left(oi_t *sensor_data, double degrees){
    double sum = 0;
    oi_setWheels(300, -300);
    while(sum < degrees){
        oi_update(sensor_data);
        sum += sensor_data -> angle;
    }
    oi_setWheels(0,0);

    return 0;
}

double turn_right(oi_t *sensor_data, double degrees){
    double sum = 0;
        oi_setWheels(-300, 300);
        while(sum > -degrees){
            oi_update(sensor_data);
            sum += sensor_data -> angle;
        }
        oi_setWheels(0,0);

        return 0;
}

