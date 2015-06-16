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
//#include "eeprom.h" 	// 1.8, 3.3 5V
//#include "eeprom_stari.h"
//#include "baro.h" 	// 5V
//#include "oled.h" 	// 5V

//#include "clock_print.h"
//#include "glcd.h"
//#include "mem.h"
//#include "compass.h"

void main(void)
{

	delay_init();
	blinky_blinky_init(0);

	USART1_init(115200);

	printf("\033c");	// clear
	printf("\t\t\t\tSTM32 pocetak\n");
	printf("Na pocetku bješe štos.\n");
	printf("________________________________________________________________________________\n");


	//rtc_main();
	//rtc_set_time(12, 30, 0);

	//eeprom_example();	
	//clock_print();

	//bmp180_init();
	//bmp180_calibration();
	//bmp180_example();

	//glcd_test();
	//glcd_speedtest();


	//mem_info();
	//malloc_test();

	//printf("DEBUG: function: %s in file: %s at line: %d\n", __func__, __FILE__, __LINE__);
	//compass_main();
	//mem_info();

	printf("sad ide while\n");
	while (1)
	{

		//bmp180_print();

		//blinky_blinky(20);
		//compass_read();
		//compass_read_cont();
		//testis();
		//Receive(0x1E,0x03);
		//stupnjevi();
		delay_ms(50);

		//printf("main RTC: %d %d %d\n", global_time[0], global_time[1], global_time[2]);
		//rtc_get_time();
		//printf("main RTC: %d %d %d\n", RTC_data.hours, RTC_data.minutes, RTC_data.seconds);

		//printf("javlja se masni ARM\n");

		//printf("uptime: %d\n", get_uptime_ms());
	}
}
