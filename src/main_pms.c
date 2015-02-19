// vim: set tw=80:sw=4:ts=4:
#include <stdio.h>
//#include <stdbool.h>

#include "debug.h"
#include "newlib_stubs.h"
#include "clang_patch.h"
#include "uart.h"
#include "led.h"
#include "delay.h"
#include "blinky.h"
#include "tipka.h"
//#include "glcd.h"
#include "wlan_hw.h"
#include "wlan_list.h"
//#include "wlan.h"

void main(void)
{
    //TODO enum npr TICK_EVERY_US i TICK_EVERY_MS da se moze definirat (i da delayevi rade kako treba bez rekonfiguracije)

	delay_init();
	blinky_blinky_init(BLINKY_LED_ALL, 0);

	//uart1_init(115200);
	uart_init(1, 115200);
	uart_clear(1);

	printf("\t\t\t\tPMS WLAN skener\n");
	printf("________________________________________________________________________________\n");

    tipka_init();

#ifdef GLCD_H
	glcd_init();
	glcd_set_orientation(L1);

#endif

	wlan_list_init();
	wlan_modul_t *wifi1 = wlan_new(2, 9600);	// napravi i init

	if (wifi1 == NULL)
	{
		printf("Doslo je do greske prilikom kreiranja novog WLAN modul objekta\n");
	}

	printf("sad ide while\n");
	while (1)
	{
		blinky_blinky(50);

		uint8_t tipka = tipka_read();

		if (tipka == 1)
		{
			//printf("Tipka stisnita.\n");
			//uart2_rx_position = 0;
			wifi1->scan(wifi1);
		}

		/*
		int8_t ret = wlan_list_ready(wifi1);
		//printf("wlan_list_ready return: %d\n", ret);
		printf("UART2 RX: %d\n", uart2_rx_position);

		if (ret)
		{
			// isprintat
			printf("WLAN:\n");
			//glcd_string("WLAN", 0, 0, 4, red);

			for (uint8_t i=0; i<ret; i++)
			{
				wlan_list_t wlan_list0 = wlan_list_get(i);
				printf("%d) signal: %d %s enc: %s\n", i+1, wlan_list0.strength, wlan_list0.SSID, wlan_list0.encription);

				if (i == 0)
				{
					//glcd_clear_line(0, 40, 2);	// obrisi liniju gdje je pisalo da skeniranje jos traje
				}
				//glcd_string(wlan_list0.SSID, 20, 40+(i*20), 2, white);	// 40 jer je gore WLAN size 4, 20 pixela za svaki iduci velicine 2
				//glcd_number(wlan_list0.strength, 0, 40+(i*20), 2, cyan);
			}
			wifi1->event = WLAN_SCAN_PRINTED;
			//printf("wifi-> buffer: %p\n", wifi1->buffer);
		}
		else if (wifi1->event == WLAN_SCAN_IN_PROGRESS)
		{
			printf("%s(): WLAN skeniranje jos traje\n", __func__);
			//glcd_string("Skeniranje jos traje", 0, 40, 2, red);
		}
		*/
		// ovo gore kopirano u ovu funkciju
		wlan_list_print(wifi1);	// isprintaj WLANove koje je pronasao modul wifi1
	}
}
