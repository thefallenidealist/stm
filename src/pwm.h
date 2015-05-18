// created 150312
#ifndef PWM_H
#define PWM_H

#if defined STM32F4 || defined STM32F4XX
	#include "stm32f4xx_rcc.h"
	#include "stm32f4xx_gpio.h"
	#include "stm32f4xx_tim.h"
#endif

void pwm_main(void);


#endif
