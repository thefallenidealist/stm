// *************************************** description ********************************************
/*
   140907
   knjiga: 351
   blocking delay
*/
// *************************************** local includes *****************************************
#include "delay.h"
#include <string.h>
// *************************************** variables **********************************************
volatile static uint32_t SysTick_var;	// timer is 24b countdown
volatile static uint32_t uptime_us=0;	
//volatile uint64_t uptime_us=0;	// uint64_t now working
static char uptime_str[35] = {};	// 34 je maksimalno za 170 godina

/**************************************************************************************************
*  					delay_init(void)						  *
**************************************************************************************************/
void delay_init(void)
{
	if(SysTick_Config(SystemCoreClock / 1000000) !=0)	// tick is 1 us
		while(1);	// error
}

/**************************************************************************************************
*  					delay_us(void)						  *
**************************************************************************************************/
void delay_us(uint32_t us)
{
	SysTick_var = us;
	while(SysTick_var != 0);
}

/**************************************************************************************************
*  					delay_ms(void)						  *
**************************************************************************************************/
void delay_ms(uint32_t ms)
{
	delay_us(1000*ms);
}

/**************************************************************************************************
*  					delay_ms(void)						  *
**************************************************************************************************/
void delay_s(uint32_t s)
{
	delay_us(1000*1000*s);
}

/**************************************************************************************************
*  					get_uptime_us(void)					  *
**************************************************************************************************/
uint32_t get_uptime_us(void)
{
	return uptime_us;
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
//uint32_t get_uptime(void)
const char *get_uptime(void)		// const znaci da ce se return value samo citati izvan funkcije, valjda
//char *get_uptime(void)
{
	uint16_t uptime_ms = 0;
	uint8_t  uptime_s  = 0;
	uint8_t  uptime_m  = 0;
	uint8_t  uptime_h  = 0;
	uint16_t uptime_d  = 0;	// 170 godina

	uptime_ms = uptime_us/1000;
	uptime_s  = uptime_ms/1000;

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

	sprintf(uptime_str, "uptime: %d days, %.2d:%.2d:%.2d.%.3d", uptime_d, uptime_h, uptime_m, uptime_s, uptime_ms);

	/*
	printf("uptime: %d days, %.2d:%.2d:%.2d.%.3d\n", uptime_d, uptime_h, uptime_m, uptime_s, uptime_ms);

	printf("duzina: %lu\n", strlen(uptime_str));	// nema zu
	printf("\t\t\t\t string uptime: %s\n", uptime_str);
	*/

	return uptime_str;
}

/**************************************************************************************************
*  					SysTick_Handler(void)					  *
**************************************************************************************************/
void SysTick_Handler(void)
{
	// IRQ every 1 us
	if(SysTick_var != 0)
	{
		SysTick_var--;
		uptime_us++;
	}
}
