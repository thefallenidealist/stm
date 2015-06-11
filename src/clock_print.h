#ifndef CLOCK_PRINT_H
#define CLOCK_PRINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#ifdef STM32F4
	#include "stm32f4xx_rcc.h"
#endif
#ifdef STM32F1
	#include "stm32f10x_rcc.h"
#endif

void clock_print(void);

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif	// CLOCK_PRINT_H
