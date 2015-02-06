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
//#include "wlan.h"

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


/*
// TODO #define boje promijenit u velika slova
uint16_t rgb565(uint8_t arg_red, uint8_t arg_green, uint8_t arg_blue)
{
	uint8_t r = arg_red   & 0b11111000;
	uint8_t g = arg_green & 0b11111100;
	uint8_t b = arg_blue  & 0b11111000;

	uint16_t rgb565 = (r << 8) | (g << 3) | (b >> 3);
	printf("%s(): R: %d, G: %d, B: %d, RGB565: %d: 0x%04X\n", __func__, r, g, b, rgb565, rgb565);

	return rgb565;
}

uint16_t rgb565_percent(uint8_t arg_red, uint8_t arg_green, uint8_t arg_blue)
{
	// 5b max: 248, 6b max: 252

	uint8_t r = arg_red*2.48; 	// 100 postaje 248
	uint8_t g = arg_green*2.52; 	// 100 postaje 252
	uint8_t b = arg_blue*2.48;

	uint16_t rgb565 = (r << 8) | (g << 3) | (b >> 3);
	printf("%s(): R: %d, G: %d, B: %d, RGB565: %d: 0x%04X\n", __func__, r, g, b, rgb565, rgb565);

	return rgb565;
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
	glcd_init();
	glcd_set_orientation(P1);
	//glcd_bg(white);

	//glcd_test();
	//glcd_speedtest();
	//glcd_orientation_test();

	//wii_init();

	wlan_init();
	//wlan_scan();

	glcd_set_orientation(L1);


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

	printf("sad ide while\n");
	while (1)
	{
		//printf("javlja se masni ARM\n");
		blinky_blinky(50);
		//wii_read();



		   				// WLAN


		/*
		if ( (strstr((char *)uart2_rx_string_arr, "OK") != 0) && (wlan_event == WLAN_SCAN_IN_PROGRESS) )
		{
			wlan_event = WLAN_SCAN_DONE;
			printf("%s(): WLAN scan done\n", __func__);
		}
		*/

		//bool skenira = wlan_is_scan_done();

		/*
		if (wlan_event == WLAN_SCAN_IN_PROGRESS)
		{
			//glcd_bg(black);	// obrisi ispis starih WLANova
			glcd_string("WLAN:", 0, 0, 4, white);
			printf("skeniranje u tijeku\n");
			glcd_string("skeniranje u tijeku", 0, 40, 2, red);
		}
		*/

		if (wlan_event == WLAN_SCAN_DONE)
		{

			wlan_parse();

			printf("WLAN:\n");
			glcd_string("                    ", 0, 40, 2, red);	// obrisi "skeniranje u tijeku"

			for (uint8_t i=0; i<10; i++)	// ispisat samo N najjacih mreza
			{
				//wlan_t wlan = wlan_get(i);
				wlan_list_t wlan = wlan_get_list(i);

				if (strncmp(wlan.SSID, "ERROR", sizeof(wlan.SSID)) != 0)	// nemoj ispisat ako nema WLANa
				{
					printf("%s \t strength: %d\n", wlan.SSID, wlan.strength);

					// zapisi i na GLCD
					//glcd_string("                ", 0, i+40, 2, glcd_get_bgcolor());	// obrisi ispod
					glcd_string(wlan.SSID, 20, 40+(i*20), 2, white);	// 40 jer je gore WLAN size 4, 20 pixela za svaki iduci velicine 2
					glcd_number(wlan.strength, 0, 40+(i*20), 2, cyan);
				}
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
