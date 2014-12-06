// jednostavni ADC
#ifndef ADC1_H
#define ADC1_H

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_adc.h"
#include "delay.h"

void ADC_example();
void ADC_init();
uint16_t ADC_read(uint8_t channel);

#endif
