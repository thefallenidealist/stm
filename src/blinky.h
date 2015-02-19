// created 150112
#ifndef	BLINKY_H
#define BLINKY_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

//#include "stm32f4xx_rcc.h"
//#include "stm32f4xx_gpio.h"
#include "delay.h"
//#include "led.h"
#include "gpio.h"

/*
//#define LED_GREEN	PD12
#define LED_ORANGE	PD13
#define LED_RED		PD14
#define LED_BLUE	PD15
*/

enum
{
	BLINKY_LED_ALL = 0,
	BLINKY_LED_GREEN,
	BLINKY_LED_ORANGE,
	BLINKY_LED_RED,
	BLINKY_LED_BLUE
};

void blinky_blinky_init(uint8_t leds, bool arg);
void blinky_blinky(uint8_t arg);

#endif
