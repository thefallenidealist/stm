// created 150530
// WS2812 driver
#ifndef LED_ARRAY_H
#define LED_ARRAY_H

//#include "gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_dma.h"

#define T0H	0.35	// us
#define T0L	0.8
#define T1H	0.7
#define T1L	0.6
#define TRES	50	// 50+ us

//#define SIG0	T0H + T0L
//#define SIG1	T1H + T1L
// define SIG_RESET	TRES low

void led_array_init(void);
void stopwatch_delay(uint32_t ticks);

int led_main(void);


#endif
