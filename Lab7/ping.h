/*
 * ping.h
 *
 *  Created on: Mar 10, 2020
 *      Author: kylusp
 */

#ifndef PING_H_
#define PING_H_

void ping_init(void);
void ping_trigger(void);
float ping_getDistance(void);
void ping_handler(void);

#endif /* PING_H_ */
