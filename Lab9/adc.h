/*
 * adc.h
 *
 *  Created on: Feb 25, 2020
 *      Author: beny258
 */

#ifndef ADC_H_
#define ADC_H_
#include <stdbool.h>
#include <stdint.h>
#include <inc/tm4c123gh6pm.h>

void adc_init(void);
int adc_read(void);

#endif /* ADC_H_ */
