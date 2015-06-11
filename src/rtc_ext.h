// created 150213
// radi na 5V iako se moj ne buni i na 3.3V

#ifndef RTC_EXT_H
#define RTC_EXT_H

#ifdef __cplusplus
extern "C" {
#endif

// local includes
#include "i2c.h"
#include "delay.h"
#include "convert.h"

// defines
#define RTC_ADDR	0x68	// 0b1101000
#define RTC_ADDR_W	(RTC_ADDR << 1) + 0	// 0xD0
#define RTC_ADDR_R	(RTC_ADDR << 1) + 1	// 0xD1

// user defines
#define RTC_I2C_PORT	2	// na kojem I2C portu je ustekan

// new data types
typedef struct
{
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t day;
	uint8_t month;
	uint8_t year;
} rtc_time_t;	// INFO time_t je vec zauzet od /usr/include/time.h

// global variables
extern rtc_time_t rtc_time;	// INFO time je vec zauzet od /usr/include/time.h

// function prototypes
void rtc_ext_init(void);
//time_t *rtc_ext_read(void);
rtc_time_t *rtc_ext_read(void);
void rtc_ext_set_time(uint8_t hours, uint8_t minutes, uint8_t seconds);
//void rtc_ext_set_date(uint8_t day, uint8_t month, uint8_t year);
void rtc_ext_set_date(uint8_t day, uint8_t month, uint16_t year);
void rtc_set_day(uint8_t day);
void rtc_ext_start(void);
void rtc_ext_example(void);

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif	// RTC_EXT_H
