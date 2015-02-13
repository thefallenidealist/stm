// vim: set tw=80:sw=4:ts=4:
#include <stdio.h>
#include <stdbool.h>

#include "debug.h"
#include "newlib_stubs.h"
#include "clang_patch.h"
#include "uart.h"
#include "led.h"
#include "delay.h"
#include "blinky.h"
//#include "rtc2.h"
//#include "eeprom.h" 	// 3.3V
//#include "eeprom_stari.h"
//#include "baro.h" 	// 5V
//#include "oled.h" 	// 5V
//#include "clock_print.h"
//#include "glcd.h"
//#include "mem.h"
//#include "cmd.h"
//#include "joystick.h"
//#include "nRF_struct.h"
//#include "colors_ansi.h"
#include "tipka.h"
//#include "wii.h"
#include "wlan_hw.h"
#include "wlan_list.h"
//#include "wlan.h"
#include "rtc_ext.h"
//#include "rtc_burgi.h"

/*
uint8_t read_rot(uint8_t pin)
{
	if (pin == 1)
		//uint8_t rotA = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8);
		return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8);
	if (pin == 2)
		//uint8_t rotB = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9);
		return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9);

	return 255;
}
*/

void main(void)
{
	//printf("DEBUG: function: %s in file: %s at line: %d\n", __func__, __FILE__, __LINE__);

    //TODO enum npr TICK_EVERY_US i TICK_EVERY_MS da se moze definirat (i da delayevi rade kako treba bez rekonfiguracije)

	delay_init();
	blinky_blinky_init(BLINKY_LED_ALL, 0);
	//blinky_blinky_init(BLINKY_LED_BLUE, 0);
	led_init("PA1");

	uart1_init(115200);
	uart_clear(1);

	printf("\t\t\t\tSTM32 pocetak\n");
	printf("Na pocetku bješe štos.\n");
	printf("________________________________________________________________________________\n");

	//rtc_main();
	//rtc_set_time(12, 30, 0);

	//eeprom_example();	
	//bmp180_example();

	//clock_print();
	//mem_info();
	//malloc_test();

    tipka_init();
	//glcd_init();
	//glcd_set_orientation(P1);
	//glcd_bg(white);

	//glcd_test();
	//glcd_speedtest();
	//glcd_orientation_test();

	//wii_init();

	//wlan_init();
	//wlan_scan();

	//glcd_set_orientation(L1);


    verbosity_level=0;

	/*
	glcd_string(glcd_get_orientation_string(), 50,50,5, white);

	glcd_fillRectangle(0,  0, 50,50, white);
	glcd_fillRectangle(50, 0, 50,50, black);
	glcd_fillRectangle(0, 50, 50,50, red);
	glcd_fillRectangle(50, 50, 50,50, green);
	glcd_fillRectangle(100,50, 50,50, blue);

	glcd_string("red text",     50,   0, 2, red);
	glcd_string("green text",   50,  20, 2, green);
	glcd_string("blue text",    50,  40, 2, blue);
	glcd_string("yellow text",  50,  60, 2, yellow);
	glcd_string("cyan text",    50,  80, 2, cyan);
	glcd_string("magenta text", 50, 100, 2, magenta);


	printf("REV test: 0xFF00 -> 0x%04X\n", __REV16(0xFF00));
	printf("REV test: 0xFF00F1F1 -> 0x%08X\n", __REV(0xFF00F1F1));
	//glcd_img_test();
	*/

	//dpot(0);

	//ERROR("test\n");



	wlan_list_init();
	wlan_modul_t *wifi1 = wlan_new(2, 9600);
	if (wifi1 == NULL)
	{
		printf("Doslo je do greske prilikom kreiranja novog WLAN modul objekta\n");
	}
	else
	{
		wifi1->scan(wifi1);
		wifi1->scan_done(wifi1);
	}


	rtc_ext_main();

	/*
	// Burgijev RTC
	i2c_init(2, 100000);
	delay_us(100);

	TimeStamp time;

	time=RTC_GetTimekeeper();
	*/

	/*
	time.hours = 12;
	time.minutes = 30;
	time.seconds = 0;
	RTC_SetTimekeeper(time);
	*/

	/*
	printf("hour: %d\n", time.hours);
	printf("minutes: %d\n", time.minutes);
	printf("seconds: %d\n", time.seconds);
	*/

	printf("sad ide while\n");
	while (1)
	{
		//printf("javlja se masni ARM\n");
		blinky_blinky(50);
		//wii_read();

		//printf("wlan_print return: %d\n", wlan_print(wifi1));
		wlan_print(wifi1);

		static uint8_t tipka_counter;
		uint8_t tipka = tipka_read();
		if(tipka == 1)
		{
			//wlan_scan();
			//dpot(++tipka_counter);
			printf("Tipka stisnita: %d\n", tipka_counter);
		}


		//bmp180_print();

		//rtc_get_time();
		//printf("main RTC: %02d:%02d:%02d \tuptime: %s\n", RTC_data.hours, RTC_data.minutes, RTC_data.seconds, get_uptime());
	}
}
