// created 150213
// radi na 5V iako se moj ne buni i na 3.3V

#ifndef RTC_EXT_H
#define RTC_EXT_H

#include "i2c.h"

// 0x68 0b1101000 + RW bit
#define RTC_ADDR	0x68
#define RTC_ADDR_W	(RTC_ADDR << 1) + 0	// 0xD0
#define RTC_ADDR_R	(RTC_ADDR << 1) + 1	// 0xD1

//#define RTC_ADDR_W	0b11010000	// 0xD0
//#define RTC_ADDR_R	0b11010001	// 0xD1

void rtc_ext_init();
void rtc_ext_main();


#endif
