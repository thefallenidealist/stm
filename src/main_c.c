// vim: set tw=80:sw=4:ts=4:
#include <stdio.h>
#include <stdbool.h>
#include "newlib_stubs.h"
#include "clang_patch.h"
#include "usart.h"
#include "led.h"
#include "delay.h"
#include "blinky.h"
//#include "rtc2.h"
//#include "eeprom.h"
//#include "eeprom_stari.h"
//#include "baro.h" 	// XXX ne radi, mozda zbog amputiranih otpornika
//#include "oled.h"
#include "clock_print.h"
//#include "glcd_low.h"
#include "glcd_high.h"

void main(void)
{

	delay_init();
	//led_init("PA0");
	//led_init("PA1");

	blinky_blinky_setup();

	USART1_init(115200);

	printf("\033c");	// clear
	printf("\t\t\t\tSTM32 pocetak\n");
	printf("________________________________________________________________________________\n");


	//rtc_main();
	//rtc_set_time(12, 30, 0);

	//eeprom_example();	
	//clock_print();

	//bmp180_init();
	//bmp180_calibration();


	glcd_test();
	glcd_speedtest();



	printf("sad ide while\n");
	while (1)
	{

		//bmp180_example();
		//uint16_t temperature = bmp180_temperature();
		//printf("temperatura: %d\n", temperature);

		//bmp180_print();

		blinky_blinky(50);
		//printf("main RTC: %d %d %d\n", global_time[0], global_time[1], global_time[2]);
		//rtc_get_time();
		//printf("main RTC: %d %d %d\n", RTC_data.hours, RTC_data.minutes, RTC_data.seconds);

		//printf("javlja se masni ARM\n");

		//printf("uptime: %d\n", get_uptime_ms());
	}
}
