#include <stdio.h>
//#include <stdlib.h> 	// malloc
#include <string.h>
#include "usart.h"
#include "led.h"
#include "delay.h"
//#include "adc1.h"
//#include "rtc.h" 	// TODO 
//#include "baro.h" 	
//#include "eeprom.h" 	// TODO provjerit
//#include "glcd_high.h"
//#include "oled.h"
#include "clang_patch.h"

void main(void)
{
	USART1_init(115200);
	//USART2_init(115200);
	USART2_init(9600);

	printf("\033c");	// clear
	printf("\t\t\t\tSTM32 pocetak\n");
	printf("________________________________________________________________________________\n");

	delay_init();
	led_init("PA0");
	//RTC_init();

	//ADC_init();

	/*
	glcd_io_init();
	glcd_spi_init();

	glcd_led_on();
	glcd_ili9341_init();
	glcd_setOrientation(P2);
	glcd_bg(black);

	uint32_t t1 = get_uptime();
	glcd_bg(black);
	uint32_t t2 = get_uptime();
	printf("t1: %u\n", t1);
	printf("t2: %u\n", t2);

	printf("glcd stoperica: %u\n", t2-t1);

	glcd_setOrientation(L2);
	glcd_string("Fuck you world", 0, 0, 2, green);
	glcd_setOrientation(L1);
	glcd_string("Fuck you world", 0, 0, 2, green);
	glcd_setOrientation(P1);
	glcd_string("Fuck you world", 0, 0, 2, red);
	glcd_setOrientation(P2);
	glcd_string("Fuck you world", 0, 0, 2, red);
	*/

	//glcd_string("ovo je jako dugacki string i zanima me kako ce se ispisat na ekranu\nNovi string ide wheeee",0,0, 2, green);

	   // postavljanje RTC-a iz sluzbenog primjera, ne radi XXX

	/*
	PWR_BackupAccessCmd(ENABLE);
	RTC_WaitForLastTask();				// Wait until last write operation on RTC registers has finished
	RTC_SetCounter(8888);
	RTC_WaitForLastTask();				// Wait until last write operation on RTC registers has finished
        PWR_BackupAccessCmd(DISABLE);
	*/

	//Write 0xCA into the RTC_WPR register.
	//RTC->WPR = 0xCA;


	printf("sad ide while\n");
	while (1)
	{
		led("PA0", 2);
		delay_ms(20);

		if (usart1_rx_event == RX_DONE)
		{
			printf("USART1 received: %s\n", usart1_rx_string_arr);
			//usart1_parse();
			//printf("USART1 to prosljedjuje USART2\n");
			//usart2_puts(usart1_rx_string_arr);
			//printf("USART1 gotov\n");
			usart1_rx_event = RX_PRINTED;
		}
		if (usart2_rx_event == RX_DONE)
		{
			printf("USART2 received: %s\n", usart2_rx_string_arr);
			usart2_rx_event = RX_PRINTED;
		}
		//usart2_puts("abcd");
		//USART2->DR = 'a';
	}
}
