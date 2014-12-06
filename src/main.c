#include <stdio.h>
#include <stdlib.h> 	// malloc
#include "usart1.h"
#include "led.h"
#include "delay.h"
//#include "adc1.h"
//#include "rtc.h" 	// TODO 
//#include "baro.h" 	
//#include "eeprom.h" 	// TODO provjerit
#include "glcd_high.h"
//#include "oled.h"

#define STDOUT_GLCD

extern int _estack;
extern int RAM;

uint8_t malloc_test()
{
	uint32_t *p_array1;

	for(int i=0; i<100; i++)
	{
		p_array1 = malloc(i*sizeof(int));
		if(p_array1 == NULL)
		{
			printf("malloc failed\n");
			return 1;
		}
		printf("i: %d p_array1 addr: %p\n", i, p_array1);
	}
}

int main()
{
	USART1_init(115200);

	//printf("\033c");	// clear
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
	*/

	/*
	uint32_t t1 = get_uptime();
	glcd_bg(black);
	uint32_t t2 = get_uptime();
	printf("t1: %u\n", t1);
	printf("t2: %u\n", t2);

	printf("glcd stoperica: %u\n", t2-t1);
	*/

	/*
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


	//uint8_t nesto = malloc(sizeof(uint64_t));

	//printf("neki kurac, dugacki string, da vidimo oce zauzet sta stacka\n");

	/*
	uint32_t *pointer = malloc(222*sizeof(uint32_t));
	if(pointer == NULL)
		printf("malloc failed\n");
	printf("pointer je %d\n", pointer);
	printf("pointer je 0x%x\n", pointer);
	*/


	uint32_t stackp = 0;
	stackp = __get_MSP();
	printf("stack pointer = 0x%x\n", stackp);

	uint32_t estack = (int)&_estack;
	printf("_estack = 0x%x\n", estack);
	uint32_t stack_size = estack - stackp;
	printf("stack size: %fkB\n", (float)stack_size/1024);
	printf("stack size: 0x%x\n", stack_size);

	malloc_test();

	uint32_t *p_array2;
	p_array2 = malloc(10*sizeof(int));
	if(p_array2 == NULL)
		printf("malloc2 failed\n");
	printf("p_array2 addr: %p\n", p_array2);


	stackp = __get_MSP();
	printf("stack pointer = 0x%x\n", stackp);

	estack = (int)&_estack;
	printf("_estack = 0x%x\n", estack);
	stack_size = estack - stackp;
	printf("stack size: %fkB\n", (float)stack_size/1024);
	printf("stack size: 0x%x\n", stack_size);

	//printf("RAM pocetak: %d\n", &RAM);

	printf("sad ide while\n");
	while (1)
	{
		led("PA0", 2);
		delay_ms(20);
		/*
		printf("\t\t\tuptime: %u\n", get_uptime());
		printf("time_h: %d\n", RTC_get_h());
		printf("time_m: %d\n", RTC_get_m());
		printf("time_s: %d\n", RTC_get_s());
		*/

	}

	//return 0;
}
