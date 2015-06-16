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


#ifdef UID_H
	uid_example();
#endif
#ifdef RTC_H
	rtc_main();
#endif

#ifdef EXTI_H
	exti1_init();
#endif

#ifdef BLINKY_H
#if defined STM32F4 || defined STM32F4XX
	blinky_blinky_init(BLINKY_LED_ALL, 0);
#endif
#if defined STM32F1 || defined STM32F10X_MD
	gpio_init(BLINKY_F1, OUT);
#endif
#endif

#ifdef GLCD_H
	glcd_init();
	glcd_set_orientation(L1);
#endif
#ifdef OLED_H
	oled_example();
#endif

	// mora se promijenit i u nRF.c
#ifdef NRF_H
	#if defined STM32F4 || defined STM32F4XX
		#define NRF_RX
	#endif
	#if defined STM32F1 || defined STM32F10X_MD
		#define NRF_TX
	#endif
	nRF_main();
#endif
#ifdef COMPASS_H
	printf("Idemo pozvat compass_main()\n");
	compass_main();
	//compass_main_burgi();
#endif

#if defined BARO_H && defined STM32F4
	bmp180_init();
	//bmp180_example();
#endif

	printf("sad ide while\n");
	while (1)
	{
		/*
#ifdef BLINKY_H
	#if defined STM32F4 || defined STM32F4XX
		blinky_blinky(50);
	#endif
	#if defined STM32F1 || defined STM32F10X_MD
		blinky(BLINKY_F1);
	#endif
#endif
		*/

#ifdef EXTI_H
		//printf("EXTI flag: %d\n", exti1_flag);
		if (exti1_flag == 1)
		{
			//printf("EXTI1 flag je aktivan, resetiram.\n");
			exti1_flag = 0;
			// TODO ovdje stavit nRF read
		}
#endif

#if defined BARO_H && defined STM32F4
		//bmp180_print();
#endif

#ifdef RTC_H
		//RTC_data_t *time = rtc_get_time();
		//printf("RTC: %d:%d:%d\n", time->hours, time->minutes, time->seconds);
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



#ifdef NRF_TX
		char tx_buffer[NRF_FIFO_SIZE] = {};

//#if defined BARO_H && defined STM32F4
#if defined BARO_H 
		float temperature = bmp180_get_temperature();
		static uint8_t counter = 1;
		snprintf(tx_buffer, NRF_FIFO_SIZE, "t: %.1f C, cnt: %d, us: %u", temperature, counter++, get_uptime_us());

		nRF_write_status_t status = nRF_write(grf, tx_buffer, strlen(tx_buffer));
		if (status == NRF_SEND_SUCCESS)
		{
			printf("%s(): nRF TX uspjesno poslao: \"%s\"\n", __func__, tx_buffer);
		}
		//else if (status == NRF_SEND_IN_PROGRESS)
		if (status == NRF_SEND_IN_PROGRESS)
		{
			printf("%s(): nRF TX still sending, retransmit count: %d\n", __func__, nRF_get_retransmit_count(grf));
		}
		//else if (status == NRF_SEND_FAILED)
		if (status == NRF_SEND_FAILED)
		{
			printf("%s(): nRF TX send failed\n", __func__);
		}
		//else if (status == NRF_SEND_TIMEOUT)
		if (status == NRF_SEND_TIMEOUT)
		{
			printf("%s(): nRF TX software timeout\n", __func__);
		}
#else
		// ovo je mali TX 
#endif	// BARO_H STM32F4
#endif	// NRF_TX
	}
}
