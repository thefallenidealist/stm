// jednostavni ADC
#ifndef ADC1_H		// pokusat adc1_h
#define ADC1_H

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_adc.h"
#include "delay.h"

void ADC_example(void);
void ADC_init(void);
uint16_t ADC_read(uint8_t channel);

#endif
