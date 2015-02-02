// vim: set tw=80:sw=4:ts=4:
#include <stdio.h>
#include <stdbool.h>
#include "newlib_stubs.h"
#include "clang_patch.h"
#include "uart.h"
#include "led.h"
#include "delay.h"
#include "blinky.h"
#include "rtc2.h"
//#include "eeprom.h" 	// 3.3V
//#include "eeprom_stari.h"
//#include "baro.h" 	// 5V
//#include "oled.h" 	// 5V
//#include "clock_print.h"
#include "glcd.h"
//#include "mem.h"
//#include "cmd.h"
//#include "joystick.h"
//#include "nRF_struct.h"

#include "colors_ansi.h"
#include "tipka.h"
//#include "wii.h"
#include "debug.h"
#include "wlan.h"

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
	//blinky_blinky_init(BLINKY_LED_ALL, 0);
	blinky_blinky_init(BLINKY_LED_BLUE, 0);
	led_init("PA1");

	uart1_init(115200);
	//uart2_init(9600);
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
	glcd_init();
	glcd_set_orientation(L1);

	//glcd_test();
	//glcd_speedtest();
	//glcd_img_test();

	//wii_init();

	wlan_init();
	delay_ms(1000);
	wlan_scan();
	//delay_ms(8000);
	printf("wlan event: %d\n", wlan_event);


    verbosity_level=0;

	//glcd_orientation_test();

	//glcd_set_orientation(L1);
	//glcd_string(glcd_get_orientation_string(), 50,50,2,white);

	//while ( (wlan_is_scan_done() != 1));

	/*
	wlan_t wlan = wlan_get(0);
	printf("Najjaci WLAN\n");
	printf("SSID: %s\n", wlan.SSID);
	printf("strength: %d\n", wlan.strength);
	printf("encription: %s\n", wlan.encription);
	*/

	/*
	glcd_hline(0, 0, glcd_get_width()-1, red);
	glcd_hline(0, 2, glcd_get_width(), red);
	glcd_hline(0, 4, glcd_get_width()+1, red);
	//glcd_hline(0, 6, glcd_get_width()+2, red);

	glcd_vline(0, 0, glcd_get_height()-1, blue);
	glcd_vline(2, 0, glcd_get_height(), blue);
	glcd_vline(4, 0, glcd_get_height()+1, blue);
	//glcd_vline(6, 0, glcd_get_height()+2, blue);


	//glcd_fillRectangle(10,10, 50, 20, blue);

	glcd_vline(0, 0, glcd_get_height(), yellow);
	glcd_vline(10, 0, glcd_get_height(), white);
	glcd_hline(0, 10, 320, yellow);
	//glcd_hline(0, 11, glcd_get_width(), blue);
	*/

	printf("sad ide while\n");
	while (1)
	{
		//printf("javlja se masni ARM\n");
		blinky_blinky(50);
		//wii_read();

		if ( (strstr((char *)uart2_rx_string_arr, "OK") != 0) && (wlan_event == WLAN_SCAN_IN_PROGRESS) )
		{
			wlan_event = WLAN_SCAN_DONE;
			printf("%s(): WLAN scan done\n", __func__);
		}

		if (wlan_event == WLAN_SCAN_IN_PROGRESS)
		{
			glcd_bg(black);	// obrisi ispis starih WLANova
			glcd_string("WLAN:", 0, 0, 4, white);
			printf("skeniranje u tijeku\n");
			glcd_string("skeniranje u tijeku", 0, 40, 2, red);
		}

		if (wlan_event == WLAN_SCAN_DONE)
		{

			wlan_parse();

			printf("WLAN:\n");
			glcd_string("                    ", 0, 40, 2, red);	// obrisi "skeniranje u tijeku"

			for (uint8_t i=0; i<7; i++)	// ispisat samo N najjacih mreza
			{
				wlan_t wlan = wlan_get(i);

				//wlan_print();
				printf("%s \t strength: %d\n", wlan.SSID, wlan.strength);

				// zapisi i na GLCD
				//glcd_string("                ", 0, i+40, 2, glcd_get_bgcolor());	// obrisi ispod
				glcd_string(wlan.SSID, 20, 40+(i*20), 2, white);	// 40 jer je gore WLAN size 4, 20 pixela za svaki iduci velicine 2
				glcd_number(wlan.strength, 0, 40+(i*20), 2, cyan);
			}
			wlan_event = WLAN_PRINTED;
		}

		uint8_t tipka = tipka_read();
		if(tipka == 1)
		{
			wlan_scan();
		}

		//bmp180_print();

		//rtc_get_time();
		//printf("main RTC: %02d:%02d:%02d \tuptime: %s\n", RTC_data.hours, RTC_data.minutes, RTC_data.seconds, get_uptime());
	}
}
