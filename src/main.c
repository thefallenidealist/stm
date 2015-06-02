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

//#include "rtc2.h"
//#include "eeprom.h" 	// 3.3V
//#include "baro.h" 	// 5V
//#include "oled.h" 	// 5V
//#include "clock_print.h" 		// isprobano F1
//#include "glcd.h"
//#include "mem.h" 				// ne radi na F1 #error
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
//#include "pwm.h"
#include "src/exti.h" 	// XXX ne smije se SPI koristit sa ovime

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

	//nrf_main11();
	nrf_main20();
	//printf("grf: \t0x%X\n", grf);
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
		delay_ms(500);
#ifdef EXTI_H
		//printf("EXTI flag: %d\n", exti1_flag);
		if (exti1_flag == 1)
		{
			printf("EXTI1 flag je aktivan, resetiram.\n");
			exti1_flag = 0;
		}
#endif

#ifdef NRF_RX
		nRF_read_payload(grf);
#endif
#ifdef NRF_TX
		printf("nRF TX salje\n");
		//uint8_t nrf_buffer[10] = {'a', 'b', 'c', 'd'};
		//nRF_write_payload(grf, nrf_buffer, 3);
		nRF_write_payload(grf, nRF_TX_buffer, nRF_get_payload_size(grf, P0));
		//printf("nRF_get_payload_size: %d\n", nRF_get_payload_size(grf, P0));
#endif
	}
}
