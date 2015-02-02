// vim: set tw=80:sw=4:ts=4:

#include <stdio.h>
#include <stdbool.h>
#include "newlib_stubs.h"
#include "clang_patch.h"
#include "usart.h"
#include "led.h"
#include "delay.h"
#include "blinky.h"
#include "rtc2.h"
//#include "eeprom.h" 	// 3.3V
//#include "eeprom_stari.h"
//#include "baro.h" 	// 5V
//#include "oled.h" 	// 5V

#include "clock_print.h"
#include "glcd.h"
#include "mem.h"
//#include "cmd.h"
//#include "joystick.h"
//#include "nRF_struct.h"

#include "colors_ansi.h"


#define DELAY 1000000
float prosjek = 0.0;
//float delay = DELAY;
int32_t delay = DELAY;
uint32_t count = 0;

void main(void)
{

	delay_init();
	//blinky_blinky_init(BLINKY_LED_ALL, 0);
	blinky_blinky_init(BLINKY_LED_ALL, 0);
	//blinky_blinky_init(BLINKY_LED_BLUE, 0);
	led_init("PA1");

	USART1_init(115200);

	printf("\033c");	// clear
	printf("\t\t\t\tSTM32 pocetak\n");
	printf("Na pocetku bješe štos.\n");
	printf("________________________________________________________________________________\n");


	rtc_main();
	//rtc_set_time(12, 30, 0);

	//eeprom_example();	
	//clock_print();

	//bmp180_example();

	//glcd_test();
	//glcd_speedtest();


	//mem_info();
	//malloc_test();

	//printf("DEBUG: function: %s in file: %s at line: %d\n", __func__, __FILE__, __LINE__);
	//mem_info();

	printf("sad ide while\n");
	while (1)
	{
		uint32_t up1 = get_uptime_us();

		//printf("javlja se masni ARM\n");
		blinky_blinky(20);
		//bmp180_print();

		//delay_ms(1000);
		delay_us(delay-80);	// -blinky_blinky delay * 4, because there are four LEDice

		rtc_get_time();
		//printf("main RTC: %d:%d:%d\n", RTC_data.hours, RTC_data.minutes, RTC_data.seconds);
		//printf("\t\t\t\t\tuptime s: %d\n", get_uptime_s());
		//printf("main RTC: %02d:%02d:%02d \tuptime: %02d:%02d_%03d s\n", RTC_data.hours, RTC_data.minutes, RTC_data.seconds, get_uptime_s()/60, get_uptime_s(), get_uptime_ms()%1000);
		//printf("uptime_us: %d\n", get_uptime_us());
		//printf("uptime_us: %d\n", uptime_us);

		//usart1_parse();

		//printf("uptime: %d\n", get_uptime_ms());


		uint32_t up2 = get_uptime_us();
		count++;

		//float stari = prosjek*((float)(count-1)/count);
		//float novi = (float)(up2 - up1)/count;

		//prosjek = stari + novi;
		int32_t up_razlika = up2 - up1;
		delay = delay + DELAY - up_razlika;

		//printf("stari: %1.f novi: %1.f \n", stari, novi);
		//printf("delay: %7.0f\t\tprosjek: %7.0f\trazlika: %d\n", delay, prosjek, up_razlika);
		//printf("delay: %7.0f\t\tprosjek: %7.0f\trazlika: %d\n", delay, stari+novi, up_razlika);
	}
}
