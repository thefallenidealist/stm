#include <stdio.h>
//#include <stdlib.h> 	// malloc
#include "usart1.h"
#include "led.h"
#include "delay.h"
//#include "adc1.h"
//#include "rtc.h" 	// TODO 
//#include "baro.h" 	
//#include "eeprom.h" 	// TODO provjerit
//#include "glcd_high.h"
//#include "oled.h"
#include "usart1.h"
#include "usart2.h"

//volatile uint16_t cnt = 0;
#define MAX_STRLEN	100
volatile char received_string[MAX_STRLEN];

typedef enum
{
	RX_IN_PROGRESS,		// 0
	RX_DONE,		// 1
	RX_PRINTED		// 2
} rx_event_t;

rx_event_t usart1_rx_event = RX_PRINTED;


int main()
{
	USART1_init(115200);

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
			printf("USART1 received: %s\n", received_string);
			usart1_rx_event = RX_PRINTED;
		}

		/*
		printf("\t\t\tuptime: %u\n", get_uptime());
		printf("time_h: %d\n", RTC_get_h());
		printf("time_m: %d\n", RTC_get_m());
		printf("time_s: %d\n", RTC_get_s());
		*/

	}
	//return 0;
}


//void USART1_IRQHandler()
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		//g_rx_done=0;
		usart1_rx_event = RX_IN_PROGRESS;
		
		static uint8_t cnt = 0; // this counter is used to determine the string length
		char rx_char = USART_ReceiveData(USART1);

		if( (t != '\n') && (cnt < MAX_STRLEN) )
		{
			received_string[cnt] = rx_char;
			cnt++;
		}
		else
		{
			cnt = 0;
			usart1_rx_event = RX_DONE;
		}
	}
	// if esle USART_IT_TXE
	else
	{
		//USART_ClearFlag(USART3, USART_FLAG_CTS);
	}
}
