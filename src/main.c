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
#if defined STM32F4 || defined STM32F4XX
#include "rtc2.h"
#endif
//#include "eeprom.h" 	// 3.3V
#if defined STM32F4 || defined STM32F4XX
#include "baro.h" 	// 5V
#endif
//#include "oled.h" 	// 5V
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

#ifdef NRF_H
	#if defined STM32F4 || defined STM32F4XX
		#define NRF_TX
	#endif
	#if defined STM32F1 || defined STM32F10X_MD
		#define NRF_RX
	#endif
	nRF_main();
#endif
#ifdef COMPASS_H
	printf("Idemo pozvat compass_main()\n");
	compass_main();
	//compass_main_burgi();
#endif

#if defined BARO_H && defined STM32F4
	bmp180_example();
#endif

	printf("sad ide while\n");
	while (1)
	{
#ifdef BLINKY_H
	#if defined STM32F4 || defined STM32F4XX
		blinky_blinky(50);
	#endif
	#if defined STM32F1 || defined STM32F10X_MD
		blinky(BLINKY_F1);
	#endif
#endif
		//delay_ms(500);

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
		//uint16_t temperature = bmp180_get_temperature();
		//printf("temperature: %d.%d°C\n", temperature/10, temperature%10);

		//bmp180_print();
#endif

#ifdef RTC_H
		RTC_data_t *time = rtc_get_time();
		//printf("RTC: %d:%d:%d\n", time->hours, time->minutes, time->seconds);
#endif

#ifdef NRF_RX
		// INFO moze i preko interrupta TODO
		bool payload_ready = nRF_read_payload(grf);
		if (payload_ready)
		{
			printf("nRF RX je dobio: %s\n", nRF_RX_buffer);
			// obrisi buffer
			for (uint8_t i=0; i<NRF_FIFO_SIZE; i++)
			{
				nRF_RX_buffer[i] = '\0';
			}
		}

		delay_ms(500);
#endif
#ifdef NRF_TX
		char tx_buffer[NRF_FIFO_SIZE] = {};
		//RTC_data_t *time = rtc_get_time();

		snprintf(tx_buffer, NRF_FIFO_SIZE, "RTC:%02d:%02d:%02d:abcdef", time->hours, time->minutes, time->seconds);
		//nRF_write_payload_no_ack(grf, tx_buffer, nRF_get_payload_size(grf, P0));
		//nRF_write_payload(grf, tx_buffer, nRF_get_payload_size(grf, P0));
		//printf("nRF poslao: %s\n", tx_buffer);
#if defined BARO_H && defined STM32F4
		uint16_t temperature = bmp180_get_temperature();
		snprintf(tx_buffer, NRF_FIFO_SIZE, "baro: %d.%d°C", temperature/10, temperature%10);
		//nRF_write_payload_no_ack(grf, tx_buffer, nRF_get_payload_size(grf, P0));
		nRF_write_payload(grf, tx_buffer, nRF_get_payload_size(grf, P0));
		printf("nRF poslao: %s\n", tx_buffer);
#endif
		delay_ms(500);
#endif
	}
}
