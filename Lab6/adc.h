/*
 * adc.h
 *
 *  Created on: Feb 25, 2020
 *      Author: kylusp
 */

#ifndef ADC_H_
#define ADC_H_

#include <inc/tm4c123gh6pm.h>
#include <stdbool.h>
#include <stdint.h>

void adc_init(void);
int adc_read(void);

#endif /* ADC_H_ */
