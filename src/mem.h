#ifndef MEM_H
#define MEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> 	// malloc
//#include "core_cmFunc.h" 	// __get_MSP()	ne smije se rucno ukljucit
//#include "core_cm4.h" 	// isto

#ifdef STM32F4
	#include "stm32f4xx.h"
#endif
#ifdef STM32F1
	#include "stm32f10x.h"
#endif

#include "debug.h"

void mem_info(void);
void malloc_test(void);
void print_remaining_stack(void);

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif	// MEM_H
