// jednostavni ADC
#ifndef ADC1_H		// pokusat adc1_h
#define ADC1_H

#ifdef STM32F10X_MD
	#include "stm32f10x_rcc.h"
	#include "stm32f10x_gpio.h"
	#include "stm32f10x_adc.h"
#endif
#ifdef STM32F4XX
	#include "stm32f4xx_rcc.h"
	#include "stm32f4xx_gpio.h"
	#include "stm32f4xx_adc.h"
#endif
	#include "delay.h"

void ADC_example(void);
void ADC_init(void);
uint16_t ADC_read(uint8_t channel);

#endif
