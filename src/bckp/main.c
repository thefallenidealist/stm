/* TODO

   scanf		zasad zablokira samo,nece se ni pokrenit

   */

//static __INLINE void __enable_irq()               { __ASM volatile ("cpsie i"); }
//static __INLINE void __disable_irq()              { __ASM volatile ("cpsid i"); }

#include <stdio.h>
#include "newlib_stubs.h"
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

//uint8_t debug_level=2;

void main(void)
{
	USART1_init(115200);
	//USART3_init(115200);
	USART3_init(9600);

	//usart_puts(3, "\033c");	// clear USART3
	//usart_puts(3, "USART3:\n");

	printf("\033c");	// clear
	//usart_puts(3, "\033c\n");	// clear USART3
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

	uint32_t t_old = 0;
	uint32_t t_new = 0;

	//printf("sad ide while\n");
	while(1)
	{
		led("PA0", 2);
		delay_ms(20);

		//printf("rx1: %s\n", usart1_rx_string_arr);
		//printf("rx3: %s\n", usart3_rx_string_arr);

		/*
		for (int i=0; i<100; i++)
		{
			if (usart3_rx_string_arr[i] != 0)
				printf("%c %d\n", usart3_rx_string_arr[i], usart3_rx_string_arr[i]);
		}
		*/
	
		//printf("%s\n", get_uptime());
		//delay_s(1);

		if (usart1_rx_event == RX_DONE)
		{
			printf("USART1 received: %s\n", usart1_rx_string_arr);
			//usart1_parse();
			//printf("USART1 to prosljedjuje USART3\n");
			usart_puts(3, (char *)usart1_rx_string_arr);
			//usart_puts(3, '\n');
			//printf("USART1 gotov\n");
			usart1_rx_event = RX_PRINTED;
		}
		if (usart2_rx_event == RX_DONE)
		{
			printf("USART2 received: %s\n", usart2_rx_string_arr);
			usart2_rx_event = RX_PRINTED;
		}
		if (usart3_rx_event == RX_DONE)
		{
			printf("USART3 received: %s\n", usart3_rx_string_arr);
			usart3_rx_event = RX_PRINTED;
		}

		/*
		if (usart3_rx_event == RX_IN_PROGRESS)
			printf("usart3 prima neki kurac\n");
			*/
	}
}
