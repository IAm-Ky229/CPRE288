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
#include "movement.h"
#include "open_interface.h"


int main (void) {

oi_t *sensor_data = oi_alloc();
oi_init(sensor_data);

move_forward(sensor_data, 2000);


oi_free(sensor_data);
}
