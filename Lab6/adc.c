/*
 * adc.c
 *
 *  Created on: Feb 25, 2020
 *      Author: kylusp
 */

#include "adc.h"


void adc_init(void){
    SYSCTL_RCGCGPIO_R |= 0b00000010;
    while (SYSCTL_PRGPIO_R & 0b00000010 == 0) {};
    GPIO_PORTB_AFSEL_R |= 0b00010000;
    GPIO_PORTB_DIR_R &= 0b11101111;
    GPIO_PORTB_DEN_R |= 0b00010000;
    GPIO_PORTB_AMSEL_R |= 0b00010000;
    GPIO_PORTB_ADCCTL_R &= 0x00;
    SYSCTL_RCGCADC_R |= 0b00000001;
    while(((SYSCTL_PRADC_R) & 0b00000001) == 0) {};
    ADC0_ACTSS_R |= 0b0001;
    ADC0_EMUX_R |= 0x000F;
    ADC0_SSMUX0_R = 0x000A;
    ADC0_SSCTL0_R |= 0x0006;
    ADC0_SAC_R |= 0x6;
}


int adc_read(void){
    int result;
    ADC0_PSSI_R |= 0b0001;
    while((ADC0_RIS_R & 0b0001) == 0) {};

    result = ADC0_SSFIFO0_R & 0xFFFFFFFF;
    ADC0_ISC_R = 0b0001;
    return result;
}
