#ifndef CPU_ID_H
#define CPU_ID_H

#include <stdio.h>
#include <stdint.h>
#include "uart.h"

typedef enum
{
	CORTEX_M0 = 0,
	CORTEX_M0_PLUS,	// ne smije bit CORTEX_M0+
	CORTEX_M1,
	CORTEX_M3,
	CORTEX_M4,
	UNKNOWN_CPU
} cpu_type_t;

void 		print_cpu_id	(void);
cpu_type_t	get_cpu_id		(void);

#endif
