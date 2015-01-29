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
#include "cmd.h"
//#include "joystick.h"
//#include "nRF_struct.h"

#include "colors_ansi.h"
#include "tipka.h"
#include "wii.h"

uint8_t read_rot(uint8_t pin)
{
	if (pin == 1)
		//uint8_t rotA = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8);
		return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8);
	if (pin == 2)
		//uint8_t rotB = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9);
		return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9);
}

void main(void)
{

	delay_init();
	//blinky_blinky_init(BLINKY_LED_ALL, 0);
	blinky_blinky_init(BLINKY_LED_ALL, 0);
	//blinky_blinky_init(BLINKY_LED_BLUE, 0);
	led_init("PA1");

	USART1_init(115200);
	USART2_init(115200);

	printf("\033c");	// clear
	usart_puts(2, "\033c");	// clear
	printf("\t\t\t\tSTM32 pocetak\n");
	printf("Na pocetku bješe štos.\n");
	printf("________________________________________________________________________________\n");

	//rtc_main();
	//rtc_set_time(12, 30, 0);

	//eeprom_example();	
	//clock_print();

	//bmp180_example();

	//glcd_init();
	//glcd_test();
	//glcd_speedtest();
	//glcd_img_test();


	//mem_info();
	//malloc_test();

	//printf("DEBUG: function: %s in file: %s at line: %d\n", __func__, __FILE__, __LINE__);
	mem_info();

	usart_puts(2, "USART2: neki tekst\n");


	/*
	printf("serijski dobio: %c\n", USART_ReceiveData(USART1));
	USART_ClearITPendingBit(USART1, USART_IT_ERR);
	USART_ClearITPendingBit(USART1, USART_IT_TXE);
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	USART_ClearITPendingBit(USART1, USART_IT_TC);
	USART_ClearITPendingBit(USART1, USART_IT_IDLE);
	USART_ClearITPendingBit(USART1, USART_IT_CTS);
	USART_ClearITPendingBit(USART1, USART_IT_LBD);
	USART_ClearITPendingBit(USART1, USART_IT_NE);
	USART_ClearITPendingBit(USART1, USART_IT_FE);
	USART_ClearITPendingBit(USART1, USART_IT_PE);
	USART_ClearITPendingBit(USART1, USART_IT_ORE);
	*/

	/*
	led_init("PB0");
	led_init("PB1");
	led_init("PB2");
	led_init("PB3");
	led_init("PB4");
	*/
	//led_init("PB5");
	/*
	led_init("PB6");
	led_init("PB7");
	led_init("PB8");
	led_init("PB9");
	led_init("PB10");
	led_init("PB11");
	led_init("PB12");
	led_init("PB13");
	led_init("PB14");
	led_init("PB15");
	*/

	/*
	led("PB0", 1);
	led("PB1", 1);
	led("PB2", 1);
	led("PB3", 1);
	led("PB4", 1);
	*/
	//led("PB5", 1);
	/*
	led("PB6", 1);
	led("PB7", 1);
	led("PB8", 1);
	led("PB9", 1);
	led("PB10", 1);
	led("PB11", 1);
	led("PB12", 1);
	led("PB13", 1);
	led("PB14", 1);
	led("PB15", 1);
	*/


	wii_init();

	printf("sad ide while\n");
	while (1)
	{
		//printf("javlja se masni ARM\n");
		blinky_blinky(50);
		usart_clear(2);
		wii_read();

		/*
		uint8_t tipka = tipka_read();
		if(tipka == 1)
		{
			glcd_test();
		}
		*/

		//uint8_t rot1_old = read_rot(1);
		//uint8_t rot2_old = read_rot(2);

		//if ( ((uint8_t rot1_new = read_rot(1)) != rot1_old) || ((uint8_t rot2_new =read_rot(2)) != rot2_old))
		/*
		if ((read_rot(1) != rot1_old) || (read_rot(2) != rot2_old))
		{
			//printf("rotacijski: %d %d\n", read_rot(1), read_rot(2));
			if ( (read_rot(1) == 0) && (read_rot(2) == 1) )			// 01
				if ( (read_rot(1) == 0) && (read_rot(2) == 0) )		// 00
					if ( (read_rot(1) == 1) && (read_rot(2) == 0) )		// 00
						printf("R\n");
		}
		*/

			/*
			   po defaultu je 11
			clockwise	11, 01, 00, 10
			anticlockwise	11, 10, 00, 01
			   */
			//printf("rotacijski: %d %d\n", rotA, rotB);


		//bmp180_print();

		//delay_ms(1000);

		//rtc_get_time();
		//printf("main RTC: %d:%d:%d\n", RTC_data.hours, RTC_data.minutes, RTC_data.seconds);

		//printf("\t\t\t\t\tuptime s: %d\n", get_uptime_s());
		//printf("main RTC: %02d:%02d:%02d \tuptime: %02d:%02d_%03d s\n", RTC_data.hours, RTC_data.minutes, RTC_data.seconds, get_uptime_s()/60, get_uptime_s(), get_uptime_ms()%1000);
		//printf("uptime_us: %d\n", get_uptime_us());
		//printf("uptime_us: %d\n", uptime_us);

		//usart1_parse();

		//printf("uptime: %d\n", get_uptime_ms());
	}
}
