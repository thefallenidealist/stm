// vim: set tw=80:sw=4:ts=4:
#include <stdio.h>
#include <stdbool.h>

//#include "debug.h"
#include "newlib_stubs.h"
#include "clang_patch.h"
#include "gpio.h"
#include "delay.h"
#include "uart.h"
#include "blinky.h"
#include "cpu_id.h" 	// treba da prvi printf da zna jel masni ili mali ARM

void main(void);
//#include "eeprom.h" 	// 3.3V
//#if defined STM32F4 || defined STM32F4XX
#include "baro.h" 	// 5V
//#include "oled_novo.h"
//#include "oled.h"
//#endif

//#include "oled.h" 	// 5V
//#include "src/visak/oled.h" 	// 5V
//#include "clock_print.h" 		// isprobano F1
//#include "glcd.h"
//#include "mem.h" 				// ne radi na F1 #error
//#include "cmd.h"
//#include "joystick.h"
//#include "colors_ansi.h"
//#include "wii.h"
//#include "wlan_hw.h"
//#include "wlan_list.h"
//#include "wlan.h"
//#include "rtc_ext.h"
//#include "rom.h"
#include "nRF.h"
//#include "flash.h"
//#include "pwm.h"
//#include "src/exti.h"
//#include "src/compass.h"
//#include "uid.h"
#if defined STM32F10X_MD || STM32F1
// samo mali ARM zasad glumi sobu
#include "soba.h"
#endif
#if defined STM32F4 || STM32F4XX
// veliki ARM
#endif

#define BLINKY_F1	"PA0"



void main(void)
{
	delay_init(TICK_EVERY_US);

	uart_init(1, 115200);
	uart_clear(1);

#ifdef CPU_ID_H
	uint8_t cpu_id = get_cpu_id();

	if (cpu_id == CORTEX_M4)
	{
		printf("\t\t\t\tSTM32 masni ARM\n");
	}
	else if (cpu_id == CORTEX_M3)
	{
		printf("\t\t\t\tSTM32 mali ARM\n");
	}
#endif
	printf("Na početku bješe štos.\n");
	printf("________________________________________________________________________________\n");


#if (defined STM32F4 || defined STM32F4XX) && defined NRF_H
		nRF_main();	// RX mora rucno pozvat
#endif

	// mora se promijenit i u nRF.c
#ifdef NRF_H
	#if defined STM32F4 || defined STM32F4XX
		#define NRF_RX
	#endif
	#if defined STM32F1 || defined STM32F10X_MD
		#define NRF_TX
	#endif
	//nRF_main();	// soba pozove
#endif

#if defined BARO_H 
	bmp180_init();
	//bmp180_example();
#endif

#if defined STM32F4 || STM32F4XX
// veliki ARM
#define TIPKA "PA0"
	bool tipka;
	gpio_init(TIPKA, IN_PD);
#endif

#if defined LAZY_ROOM_H
	soba_init();
#endif

	printf("sad ide while\n");
	while (1)
	{
#if defined STM32F4 || STM32F4XX
		tipka = gpio_read(TIPKA);
		if (tipka == 1)
		{
			delay_ms(200);
			printf("Tipka je stisnita\n");
		}
#endif
#if defined LAZY_ROOM_H
		soba_main();
		delay_ms(500);
#endif

#ifdef NRF_RX
		//bool data_ready = nRF_read_payload(grf);	// vrati 1 kad payload zapise u polje
		bool data_ready = nRF_read(grf);	// vrati 1 kad payload zapise u polje
		char *buffer = grf->RX_buffer;

		if (data_ready)
		{
			printf("nRF RX je dobio: %s\n", buffer);
			//printf("nRF RX je dobio: %s \t poslat ce nazad: %s\n", buffer);
		}

#endif	// NRF_RX
	}
}
