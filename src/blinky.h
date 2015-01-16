// created 150112
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "delay.h"
#include "led.h"

//#define LED_GREEN	PD12
#define LED_ORANGE	PD13
#define LED_RED		PD14
#define LED_BLUE	PD15

static const char	LED_GREEN[] = "PD12";
// jer funkcije ocekuju pointere na strings pa bude warninga ako se posalje array
//static const char	*pLEDg = LED_GREEN;
//static char	*LEDG = LED_GREEN;

void blinky_blinky_setup(void);
void blinky_blinky(uint8_t arg);
