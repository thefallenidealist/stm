#include "rtc_ext.h"

// global variables
rtc_time_t rtc_time;

/*************************************************************************************************
			rtc_ext_init()
*************************************************************************************************/
void rtc_ext_init(void)
{
	i2c_init(RTC_I2C_PORT, 100000);
	//delay_ms(100);
}

/*************************************************************************************************
			rtc_ext_read()
*************************************************************************************************/
//time_t *rtc_ext_read(void)
rtc_time_t *rtc_ext_read(void)
{
	i2c_start(RTC_I2C_PORT);
	i2c_sendAddr_tx(RTC_I2C_PORT, RTC_ADDR_W);
	i2c_write(RTC_I2C_PORT, 0x00);
	i2c_stop(RTC_I2C_PORT);

	i2c_start(RTC_I2C_PORT);
	i2c_sendAddr_rx(RTC_I2C_PORT, RTC_ADDR_R);

	uint8_t r0 = 0xFF, r1 = 0xFF, r2 = 0xFF, r3 = 0xFF, r4 = 0xFF, r5 = 0xFF, r6 = 0xFF;

	// BCD format
	r0 = i2c_read_ack(RTC_I2C_PORT);
	r1 = i2c_read_ack(RTC_I2C_PORT);
	r2 = i2c_read_ack(RTC_I2C_PORT);
	r3 = i2c_read_ack(RTC_I2C_PORT);
	r4 = i2c_read_ack(RTC_I2C_PORT);
	r5 = i2c_read_ack(RTC_I2C_PORT);
	r6 = i2c_read_nack(RTC_I2C_PORT);
	i2c_stop(RTC_I2C_PORT);
	delay_ms(1);

	uint8_t secondsH = (r0 >> 4) & 0b111;
	uint8_t secondsL =  r0       & 0b1111;

	uint8_t minutesH = (r1 >> 4) & 0b111;
	uint8_t minutesL =  r1       & 0b1111;

	uint8_t hoursL =  r2 & 0b1111;
	//uint8_t hoursH = (r2 >> 4) & 1;
	uint8_t hoursH = (r2 >> 4) & 0b11;	// 24h mode

	//uint8_t day = r3 & 0b111;	// day in week		// INFO unused
	
	uint8_t dateH = (r4 >> 4) & 0b11;
	uint8_t dateL =  r4       & 0b1111;

	uint8_t monthH = (r5 >> 4) & 1;
	uint8_t monthL =  r5       & 0b1111;

	uint8_t yearH = (r6 >> 4) & 0b1111;
	uint8_t yearL =  r6       & 0b1111;

	uint8_t hours 	= hoursH*10 + hoursL;
	uint8_t minutes = minutesH*10 + minutesL;
	uint8_t seconds = secondsH*10 + secondsL;
	uint8_t date 	= dateH*10 + dateL;
	uint8_t month 	= monthH*10 + monthL;
	uint8_t year 	= yearH*10 + yearL;

	rtc_time.seconds = seconds;
	rtc_time.minutes = minutes;
	rtc_time.hours 	 = hours;
	rtc_time.day 	 = date;
	rtc_time.month 	 = month;
	rtc_time.year 	 = year;

	return (&rtc_time);

	//printf("Time: %02d:%02d:%02d\n", hours, minutes, seconds);
	//printf("Date: %d %02d.%02d.%02d\n", day, date, month, year);
}


/*************************************************************************************************
			rtc_ext_set_time()
*************************************************************************************************/
void rtc_ext_set_time(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
	//printf("%s(): zapisujem %02d:%02d:%02d \n", __func__, hours, minutes, seconds);

	i2c_start(RTC_I2C_PORT);
	i2c_sendAddr_tx(RTC_I2C_PORT, RTC_ADDR_W);
	i2c_write(RTC_I2C_PORT, 0x00);

	i2c_write(RTC_I2C_PORT, dec2bcd(seconds));
	i2c_write(RTC_I2C_PORT, dec2bcd(minutes));
	i2c_write(RTC_I2C_PORT, dec2bcd(hours));

	i2c_stop(RTC_I2C_PORT);
	delay_ms(1);

	rtc_ext_read();	// da ponovo zapise u struct
}

/*************************************************************************************************
			rtc_ext_set_date()
*************************************************************************************************/
//void rtc_ext_set_date(uint8_t day, uint8_t month, uint8_t year)
void rtc_ext_set_date(uint8_t day, uint8_t month, uint16_t year)
{
	//printf("%s(): zapisujem %02d.%02d.%02d\n", __func__, day, month, year);

	i2c_start(RTC_I2C_PORT);
	i2c_sendAddr_tx(RTC_I2C_PORT, RTC_ADDR_W);
	i2c_write(RTC_I2C_PORT, 0x04);

	i2c_write(RTC_I2C_PORT, dec2bcd(day));
	i2c_write(RTC_I2C_PORT, dec2bcd(month));
	i2c_write(RTC_I2C_PORT, dec2bcd(year));

	i2c_stop(RTC_I2C_PORT);
	delay_ms(1);

	rtc_ext_read();	// da ponovo zapise u struct
}

/*************************************************************************************************
			rtc_read()
*************************************************************************************************/
void rtc_set_day(uint8_t day)
{
	if ( (day < 1) || (day > 7) )
	{
		printf("%s(): Error: wrong day: %d\n", __func__, day);
		// TODO
		// return -1;
	}

	i2c_start(RTC_I2C_PORT);
	i2c_sendAddr_tx(RTC_I2C_PORT, RTC_ADDR_W);
	i2c_write(RTC_I2C_PORT, 0x03);

	i2c_write(RTC_I2C_PORT, dec2bcd(day));

	i2c_stop(RTC_I2C_PORT);
	delay_ms(1);

	rtc_ext_read();	// da ponovo zapise u struct
}

/*************************************************************************************************
			rtc_ext_start()
*************************************************************************************************/
/*
   skoro pa beskorisna funkcija
   Nakon pravog RTC reseta (istekan iz struje, nema baterije) sluzi da RTC krene brojat (od 00:00:00)
   XXX moguce i sjebana funkcija
*/
void rtc_ext_start(void)
{
	i2c_start(RTC_I2C_PORT);
	i2c_sendAddr_tx(RTC_I2C_PORT, RTC_ADDR_W);
	i2c_write(RTC_I2C_PORT, 0x00);	// register 0
	i2c_write(RTC_I2C_PORT, 0x00);	// CH=0

	i2c_stop(RTC_I2C_PORT);
	delay_ms(1);
}

/*************************************************************************************************
			rtc_ext_example()
*************************************************************************************************/
void rtc_ext_example(void)
{
	rtc_ext_init();
	//rtc_ext_start();

	/*
	uint8_t hours 	= 12;
	uint8_t minutes = 30;
	uint8_t seconds = 0;
	uint8_t day 	= 13;
	uint8_t month 	= 2;
	uint8_t year 	= 15;

	printf("Setting RTC time to: %02d:%02d:%02d \t %02d.%02d.%02d\n", hours, minutes, seconds, day, month, year);
	rtc_ext_set_time(hours, minutes, seconds);
	rtc_ext_set_date(day, month, year);
	*/

	//time_t *time0 = rtc_ext_read();
	rtc_time_t *time0 = rtc_ext_read();
	printf("Current time: %02d:%02d:%02d", time0->hours, time0->minutes, time0->seconds);
	printf("\tCurrent date: %02d.%02d.%02d\n", time0->day, time0->month, time0->year);
}
