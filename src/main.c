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
//#include "glcd.h"
#include "mem.h"
//#include "cmd.h"
//#include "joystick.h"
//#include "nRF_struct.h"

#include "colors_ansi.h"
#include "tipka.h"
//#include "wii.h"
#include "debug.h"
#include "wlan.h"
//#include "core_cm4.h"

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


uint8_t EXTI_flag = 0;

void main(void)
{
	//printf("DEBUG: function: %s in file: %s at line: %d\n", __func__, __FILE__, __LINE__);

    //TODO enum npr TICK_EVERY_US i TICK_EVERY_MS da se moze definirat (i da delayevi rade kako treba bez rekonfiguracije)

	delay_init();
	//blinky_blinky_init(BLINKY_LED_ALL, 0);
	blinky_blinky_init(BLINKY_LED_BLUE, 0);
	led_init("PA1");

    led_init("PD12");

	uart1_init(115200);
	//uart2_init(115200);
	uart2_init(9600);
	uart_clear(1);
	//uart_clear(2);

	printf("\t\t\t\tSTM32 pocetak\n");
	printf("Na pocetku bješe štos.\n");
	printf("________________________________________________________________________________\n");

	//rtc_main();
	//rtc_set_time(12, 30, 0);

	//eeprom_example();	
	//bmp180_example();

	//clock_print();
	mem_info();
	//malloc_test();

	//glcd_init();
	//glcd_test();
	//glcd_speedtest();
	//glcd_img_test();

	//wii_init();
	//wlan_main();


    verbosity_level=0;

    //   NVIC_SetPriority(SysTick_IRQn, 0);
	printf("sad ide while\n");
	while (1)
	{
		//printf("javlja se masni ARM\n");
		blinky_blinky(50);
		//wii_read();

        // interrupt postavi da je krenio zapisivat, ovdje se provjera jel ima OK u stringu
        //char *ret = strstr(uart2_rx_string_arr, "OK");
        //printf("str vratio: %s\n", ret);
            if ( (strstr(uart2_rx_string_arr, "OK") != 0) && (uart2_rx_event != RX_DONE) )
            {
                printf("UART2 dobio OK\n");
                uart2_rx_event = RX_DONE;
            }


        //printf("EXTI flag: %d\n", EXTI_flag);

        /*
        if (uart2_rx_event == RX_OVERFLOW)
        {
            printf("\t\t\t\t\tERROR: RX buffer overflow\n");
            uart2_rx_event = RX_DONE;   // bezveze, bilo sta drugo
        }
        */

        /*
		if (uart2_rx_event != RX_PRINTED)
		{
            printf("main printa rx2 buffer:\n");
            for (int i=0; i<UART_MAX_LENGTH; i++)
            {
                printf("%c", uart2_rx_string_arr[i]);
            }
            printf("\n");

            printf("rx gotov\n");
            uart2_rx_event = RX_PRINTED;
        }
        */


        /*
		uint8_t tipka = tipka_read();
		if(tipka == 1)
		{
			//glcd_test();
            printf("tipka\n");
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

		//rtc_get_time();
		//printf("main RTC: %02d:%02d:%02d \tuptime: %s\n", RTC_data.hours, RTC_data.minutes, RTC_data.seconds, get_uptime());
	}
}
