//created 150526
#ifndef EXTI_H
#define EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined STM32F4 || defined STM32F4XX
	#include "stm32f4xx_exti.h"
	#include "stm32f4xx_syscfg.h"
#endif
#if defined STM32F1 || defined STM32F10X_MD
	#include "stm32f10x_exti.h"
	//#include "stm32f10x_syscfg.h"
	//#include "stm32f10x_it.h"
#endif
#include "misc.h" 	// NVIC
#include "gpio.h"

extern volatile uint8_t exti1_flag;

void exti1_init(void);
//void EXTI1_IRQHandler(void);

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif	// EXTI_H
