#include "rtc_ext.h"
#include "delay.h"
#include <stdbool.h>

void rtc_ext_init()
{
	i2c_init(2, 100000);
	//delay_ms(100);
}

void dec2bin8(uint8_t arg)
{
	uint8_t i=8;

	printf("%d = 0b", arg);
	while (i-- > 0)
	{
		printf("%d", (arg >> i) & 1);
	}
	printf("\n");
}

typedef struct
{
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t day;
	uint8_t month;
	uint8_t year;
} time_t;

void rtc_read()
{
	i2c_start(2);
	i2c_sendAddr_tx(2, RTC_ADDR_W);
	i2c_write(2, 0x00);
	i2c_stop(2);
	//delay_ms(1);

	//i2c_restart(2);
	i2c_start(2);
	i2c_sendAddr_rx(2, RTC_ADDR_R);

	uint8_t r0 = 0xFF, r1 = 0xFF, r2 = 0xFF, r3 = 0xFF, r4 = 0xFF, r5 = 0xFF, r6 = 0xFF;

	// BCD format
	r0 = i2c_read_ack(2);
	r1 = i2c_read_ack(2);
	r2 = i2c_read_ack(2);
	r3 = i2c_read_ack(2);
	r4 = i2c_read_ack(2);
	r5 = i2c_read_ack(2);
	r6 = i2c_read_nack(2);
	i2c_stop(2);
	delay_ms(1);

	uint8_t secondsH = (r0 >> 4) & 0b00000111;
	uint8_t secondsL =  r0       & 0b00001111;

	uint8_t minutesH = (r1 >> 4) & 0b00000111;
	uint8_t minutesL =  r1       & 0b1111;

	uint8_t hoursL =  r2 & 0b1111;
	//uint8_t hoursH = (r2 >> 4) & 1;
	uint8_t hoursH = (r2 >> 4) & 0b11;	// 24h mode

	uint8_t day = r3 & 0b111;	// dan u tjednu
	
	uint8_t dateH = (r4 >> 4) & 0b11;
	uint8_t dateL =  r4       & 0b1111;

	uint8_t monthH = (r5 >> 4) & 1;
	uint8_t monthL =  r5       & 0b1111;

	uint8_t yearH = (r6 >> 4) & 0b1111;
	uint8_t yearL =  r6       & 0b1111;

	uint8_t hours = hoursH*10 + hoursL;
	uint8_t minutes = minutesH*10 + minutesL;
	uint8_t seconds = secondsH*10 + secondsL;

	uint8_t date = dateH*10 + dateL;
	uint8_t month = monthH*10 + monthL;
	uint8_t year = yearH*10 + yearL;

	printf("Time: %02d:%02d:%02d\n", hours, minutes, seconds);
	printf("Date: %d %02d.%02d.%02d\n", day, date, month, year);
}

uint8_t dec2bcd(uint8_t dec)
{
	if (dec > 99)	// veci nece stat u 8b
	{
		return 0;
	}
	uint8_t bcd, bcdH, bcdL;

	// razlomi na single digit
	bcdH = dec/10;
	bcdL = dec%10;

	// pretvori nazad u 8b BCD
	bcd = bcdH<<4 | bcdL;

	return bcd;
}

void rtc_set_time(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
	printf("%s(): zapisujem %02d:%02d:%02d \n", __func__, hours, minutes, seconds);

	i2c_start(2);
	i2c_sendAddr_tx(2, RTC_ADDR_W);
	i2c_write(2, 0x00);

	i2c_write(2, dec2bcd(seconds));
	i2c_write(2, dec2bcd(minutes));
	i2c_write(2, dec2bcd(hours));

	i2c_stop(2);
	delay_ms(1);
}

void rtc_set_date(uint8_t day, uint8_t month, uint8_t year)
{
	printf("%s(): zapisujem %02d.%02d.%02d\n", __func__, day, month, year);

	i2c_start(2);
	i2c_sendAddr_tx(2, RTC_ADDR_W);
	i2c_write(2, 0x04);

	i2c_write(2, dec2bcd(day));
	i2c_write(2, dec2bcd(month));
	i2c_write(2, dec2bcd(year));

	i2c_stop(2);
	delay_ms(1);
}

void rtc_set_day(uint8_t day)
{
	if ( (day < 1) || (day > 7) )
	{
		printf("%s(): Error: wrong day: %d\n", __func__, day);
		// return -1;
	}

	i2c_start(2);
	i2c_sendAddr_tx(2, RTC_ADDR_W);
	i2c_write(2, 0x03);

	i2c_write(2, dec2bcd(day));

	i2c_stop(2);
	delay_ms(1);

}

/*
void rtc_set(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t day, uint8_t month, uint8_t year)
{
	printf("%s(): zapisujem %02d:%02d:%02d \t %02d.%02d.%02d\n", __func__, hours, minutes, seconds, day, month, year);

	i2c_start(2);
	i2c_sendAddr_tx(2, RTC_ADDR_W);
	i2c_write(2, 0x00);

	i2c_write(2, dec2bcd(seconds));
	i2c_write(2, dec2bcd(minutes));
	i2c_write(2, 64+dec2bcd(hours));	// hours	// 2^6 = 64 -> 24h mode
	//i2c_write(2, 5);	// dan u tjednu
	i2c_write(2, dec2bcd(day));
	i2c_write(2, dec2bcd(month));
	i2c_write(2, dec2bcd(year));
	*/

	/*
#define OUT		7
#define SQWE	4
#define RS1		1
#define RS0		0

	//i2c_write(2, 0b00010011);	// 
	uint8_t control_value = (0 << OUT) | (1 << SQWE) | (1 << RS1) | (1 << RS0);
	printf("u contorl register ce se zapisat: %d\n", control_value);
	i2c_write(2, control_value);
	*/

	//i2c_write(2, 0x00);

/*
	i2c_stop(2);
	delay_ms(1);
}
*/

void rtc_start()
{
	i2c_start(2);
	i2c_sendAddr_tx(2, RTC_ADDR_W);
	i2c_write(2, 0x00);	// register 0
	i2c_write(2, 0x00);	// CH=0

#define OUT		7
#define SQWE	4
#define RS1		1
#define RS0		0
	//i2c_write(2, 0x07);	// CONTROL register
	//uint8_t control_value = (0 << OUT) | (1 << SQWE) | (1 << RS1) | (1 << RS0);
	//printf("%s() u contorl register ce se zapisat: %d\n", __func__, control_value);
	//i2c_write(2, control_value);

	i2c_stop(2);
	delay_ms(1);
}

void rtc_ext_main()
{
	rtc_ext_init();
	//rtc_start();

	//rtc_set_time(12, 30, 0);
	//rtc_set_day(5);
	//rtc_set_date(14, 2, 15);

	//rtc_set(12, 30, 0, 13, 2, 15);
	//rtc_set(23, 59, 0, 31, 12, 15);

	rtc_set_time(23, 59, 0);
	rtc_set_date(31, 12, 15);

	rtc_read();


}
