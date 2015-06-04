#ifndef RTC_H
#define RTC_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#if defined STM32F4 || defined STM32F4XX
	#include "stm32f4xx_rcc.h"
	#include "stm32f4xx_pwr.h"
	#include "stm32f4xx_rtc.h"
#endif
#if defined STM32F1 || defined STM32F10X_MD
	#include "stm32f10x_rcc.h"
	#include "stm32f10x_pwr.h"
	#include "stm32f10x_rtc.h"
#endif

typedef struct 
{
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
} RTC_data_t;
RTC_data_t RTC_data;

void 		rtc_set_time (uint8_t h, uint8_t m, uint8_t s);
RTC_data_t *rtc_get_time (void);
void 		rtc_main	 (void);

#endif
