#ifndef MEM_H
#define MEM_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> 	// malloc
//#include "core_cmFunc.h" 	// __get_MSP()	ne smije se rucno ukljucit
//#include "core_cm4.h" 	// isto
#include "stm32f4xx.h"


#include "debug.h"

void mem_info();
void malloc_test();

#endif
