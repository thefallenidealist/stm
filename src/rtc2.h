#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rtc.h"

typedef struct 
{
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
} RTC_data_t;
RTC_data_t RTC_data;

void rtc_set_time(uint8_t h, uint8_t m, uint8_t s);
RTC_data_t *rtc_get_time();
void rtc_main(void);
