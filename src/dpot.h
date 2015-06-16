
#include <stdio.h>
#include "gpio.h"

typedef enum
{
	P0_0 = 0,
	P0_5,
	P1_0,
	P1_5,
	P2_0,
	P2_5,
	P3_0,
	P3_5,
	P4_0,
	P4_5,
	P5_0,
	P5_5,
	P6_0,
	P6_5,
	P7_0,
	P7_5,
	P8_0,
	P8_5,
	P9_0,
	P9_5,
	P10_0,
	P10_5,
	P11_0,	// 22
	P_INVALID
} pot_state_t;

void dpot_init(void);
//int dpot(uint8_t state);
int dpot(pot_state_t state);
