// created 150117
#ifndef COMPASS_H
#define COMPASS_H

#include <stdio.h>
//#include <math.h>
#ifdef STM32F10X_MD
	#include "stm32f10x_rcc.h"
	#include "stm32f10x_gpio.h"
	#include "stm32f10x_i2c.h"
#endif
#ifdef STM32F4XX
	#include "stm32f4xx_rcc.h"
	#include "stm32f4xx_gpio.h"
	#include "stm32f4xx_i2c.h"
#endif
#include "delay.h"
#include "i2c.h"

void compass_main(void);
void compass_read_continuous();
void compass_read_single();

void stupnjevi();
void procitaj();


#endif
