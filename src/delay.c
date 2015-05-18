// *************************************** description ********************************************
/*
   140907
   knjiga: 351
   blocking delay
*/
// *************************************** local includes *****************************************
#include "delay.h"
#include <string.h>
#include <math.h>

// XXX na F4 ne radi get_uptime_us kako treba
// TODO get days, hours, minutes

// *************************************** variables **********************************************
// private
_Atomic volatile static uint32_t delay_var;	// timer is 24b countdown
//volatile static uint32_t uptime_us=0;	
volatile uint32_t uptime_us=0;	
static char uptime_str[35] = {};	// 34 je maksimalno za 170 godina
// nije volatile da se ne budi kompajler (kasnije treba bit const)

/**************************************************************************************************
*  					delay_init(void)					  *
**************************************************************************************************/
void delay_init(void)
{
#ifdef STM32F4XX
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq(&RCC_Clocks);
    //SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000); // 1ms
    SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000000);    // 1us
#endif
#ifdef STM32F1
	if(SysTick_Config(SystemCoreClock / 1000000) !=0)	// 1000000 Hz 1000 kHz	1Mhz	1us
	{
		while(1);	// error
	}
#endif
}

/**************************************************************************************************
*  					delay_us()						  *
**************************************************************************************************/
void delay_us(uint32_t us)
{
	delay_var = us;
	while (delay_var != 0);
}

/**************************************************************************************************
*  					delay_ms()						  *
**************************************************************************************************/
void delay_ms(uint32_t ms)
{
	delay_us(1000*ms);
}

/**************************************************************************************************
*  					delay_s()						  *
**************************************************************************************************/
void delay_s(uint32_t s)
{
	delay_us(1000*1000*s);
}

/**************************************************************************************************
*  					get_uptime_us()					  *
**************************************************************************************************/
uint32_t get_uptime_us(void)
{
	/*
	static uint32_t uptime_tmp=0;
	static uint32_t uptime_proslo;
	uptime_proslo = uptime_tmp;

	uptime_tmp = uptime_us;
	if (uptime_proslo/1000/1000 != uptime_tmp/1000/1000)
		printf("e, nije jednako\n");
	*/

	return uptime_us;
	//return uptime_tmp/1000/1000;
}

/**************************************************************************************************
*  					get_uptime_ms(void)					  *
**************************************************************************************************/
uint32_t get_uptime_ms(void)
{
	return uptime_us/1000;
}

/**************************************************************************************************
*  					get_uptime_s(void)					  *
**************************************************************************************************/
uint32_t get_uptime_s(void)
{
	return uptime_us/1000/1000;
}

/**************************************************************************************************
*  					get_uptime(void)					  *
**************************************************************************************************/
const char *get_uptime(void)
{
	volatile static uint16_t uptime_ms = 0;
	volatile static uint8_t  uptime_s  = 0;
	volatile static uint8_t  uptime_m  = 0;
	volatile static uint8_t  uptime_h  = 0;
	volatile static uint16_t uptime_d  = 0;	// 170 godina
	volatile static uint8_t msb_ms = 0;

	//uptime_ms = (floor((uptime_us/1000))) % 60000;
	//uptime_ms = (round((uptime_us/1000))) % 60000;
	uptime_ms = (uint16_t)(round(uptime_us/1000.0)) % 60000;
	//uptime_ms = (uptime_us/20) % 60000;
	//uptime_s  = uptime_ms/1000;

	//printf("DEBUG: h:%d m:%d s:%d ms:%d us:%d\n", uptime_h, uptime_m, uptime_s, uptime_ms, uptime_us);

	// XXX sekunde idu do 64 pa onda ide 3-4x 0 sekundi pa krene isponova od 00
	// XXX ms je 16b (64k) i tek nakon sto se prelije dodje u nulu

	if (uptime_ms >= 1000)
	{
		//uptime_ms = 0;
		//uptime_s++;
		//if (uptime_ms 
		//uptime_ms %= 60000;
		//if (msb_ms != (uptime_ms/1000) % 60)
		if (msb_ms != ((uint16_t)round(((uptime_ms/1000.0))) % 60))
		{
			//msb_ms = ((uptime_ms/1000) % 60);
			msb_ms = ((uint16_t)round(((uptime_ms/1000.0))) % 60);
			//uptime_s++;
			uptime_s++;
			/*
			if (uptime_s >= 60)
			{
				uptime_s = 0;
				uptime_m++;
			}
			if (uptime_m >= 60)
			{
				uptime_m = 0;
				uptime_h++;
			}
			if (uptime_h >= 24)
			{
				uptime_h = 0;
				uptime_d++;
			}
			*/
			//uptime_s += 60;
			//printf("uptime: %d days, %.2d:%.2d:%.2d\0\r\n\n\n\n", uptime_d, uptime_h, uptime_m, uptime_s);
			//sprintf(uptime_str, "uptime: %d days, %.2d:%.2d:%.2d", uptime_d, uptime_h, uptime_m, uptime_s);
			//printf("%s\n", uptime_str);
		}
	}
	if (uptime_s >= 60)
	{
		uptime_s = 0;
		uptime_m++;
	}
	if (uptime_m >= 60)
	{
		uptime_m = 0;
		uptime_h++;
	}
	if (uptime_h >= 24)
	{
		uptime_h = 0;
		uptime_d++;
	}

    // TODO day/days
	sprintf(uptime_str, "%d days, %.2d:%.2d:%.2d.%.3d", uptime_d, uptime_h, uptime_m, uptime_s, uptime_ms%1000);

	return uptime_str;
}

/**************************************************************************************************
*  					SysTick_Handler(void)					  *
**************************************************************************************************/
void SysTick_Handler(void)
{
	// IRQ every 1 us

	uptime_us++;	// za uptime, korisnik je ne mijenja

	if (delay_var != 0)
	{
		delay_var--;	// za delay, korisnik je moze mijenjat
	}


	//uptime_us += 1234;
	//uptime_us %= 4294967000;
	//if (uptime_us / 4294967000 == 1)
	if (uptime_us / 4294960000 == 1)	// 7ms da skuzi da se treba ponistit
	{
		//uptime_us = 7000;
		//tmp_up = uptime_us;
		//set_tmp_up(uptime_us);
		uptime_us %= 10000;
	}
}
