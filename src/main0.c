// vim: set tw=80:sw=4:ts=4:
#include <stdio.h>
#include <stdbool.h>

//#include "debug.h"
#include "newlib_stubs.h"
#include "clang_patch.h"
#include "uart.h"
#include "gpio.h"
#include "delay.h"
#include "blinky.h"

void main(void);

//#include "rtc2.h"
//#include "eeprom.h" 	// 3.3V
//#include "baro.h" 	// 5V
//#include "oled.h" 	// 5V
//#include "clock_print.h"
//#include "glcd.h"
//#include "mem.h"
//#include "cmd.h"
//#include "joystick.h"
//#include "nRF_struct.h"
//#include "colors_ansi.h"
//#include "wii.h"
//#include "wlan_hw.h"
//#include "wlan_list.h"
//#include "wlan.h"
//#include "rtc_ext.h"
//#include "rom.h"
#include "nRF.h"
//#include "flash.h"
//#include "cpu_id.h"
//#include "pwm.h"

void main(void)
{
    //TODO enum npr TICK_EVERY_US i TICK_EVERY_MS da se moze definirat (i da delayevi rade kako treba bez rekonfiguracije)

	delay_init();

	uart_init(1, 115200);
	uart_clear(1);

	printf("\t\t\t\tSTM32 masni ARM\n");
	printf("Na pocetku bješe štos.\n");
	printf("________________________________________________________________________________\n");

#ifdef RTC_H
	rtc_main();
	//rtc_set_time(12, 30, 0);
#endif

	//eeprom_example();	
	//bmp180_example();

	//clock_print();
	//mem_info();
	//malloc_test();

	gpio_init("PA0", IN);	// tipka

#ifdef BLINKY_H
#if defined STM32F4 || defined STM32F4XX
	blinky_blinky_init(BLINKY_LED_ALL, 0);
	//blinky_blinky_init(BLINKY_LED_BLUE, 0);
#endif
#if defined STM32F1 || defined STM32F10X_MD
	//blinky
#endif
#endif

#ifdef GLCD_H
	glcd_init();
	glcd_set_orientation(L1);
#endif

#ifdef MEM_H
	mem_info();
#endif

	//eeprom_example();
	//rom_example();


	//rtc_ext_example();

#ifdef RTC_H
		rtc_get_time();
#endif
#ifdef NRF_H
	if (nRF_main() != 0)
	//if (nRF_main2() != 0)
	{
		printf("%s(): nRF_main has failed\n", __func__);
	}
#endif

#ifdef FLASH_H
	flash_main();
#endif

	gpio_init("PA1", OUT);
	gpio_write("PA1", 1);

#ifdef CPU_ID_H
	print_cpu_id();
#endif


#ifdef PWM_H
	pwm_main();
#endif 


	printf("sad ide while\n");
	while (1)
	{
		//printf("javlja se masni ARM\n");
#ifdef BLINKY_H
		blinky_blinky(50);
#endif

		//wii_read();

		//printf("GPIO read: %d\n", gpio_read("PA0"));

		/*
		static uint8_t tipka_counter;
		uint8_t tipka = tipka_read();
		if(tipka == 1)
		{
			printf("Tipka stisnita: %d\n", tipka_counter);
		}
		*/


		//bmp180_print();

#ifdef RTC_H
		rtc_get_time();
		//printf("main RTC: %02d:%02d:%02d \tuptime: %s\n", RTC_data.hours, RTC_data.minutes, RTC_data.seconds, get_uptime());
		//printf("RTC seconds: %02d\n", RTC_data.seconds);
#endif
	}
}
