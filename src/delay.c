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
// private
volatile static uint32_t SysTick_var;	// timer is 24b countdown
volatile static uint32_t uptime_us=0;	
static char uptime_str[35] = {};	// 34 je maksimalno za 170 godina
// nije volatile da se ne budi kompajler (kasnije treba bit const)

/**************************************************************************************************
*  					delay_init(void)					  *
**************************************************************************************************/
void delay_init(void)
{
	if(SysTick_Config(SystemCoreClock / 1000000) !=0)	// 1000000 Hz 1000 kHz	1Mhz	1us
								// mislim da ne ticka bas svaku us
	{
		while(1);	// error
	}
}

/**************************************************************************************************
*  					delay_us()						  *
**************************************************************************************************/
void delay_us(uint32_t us)
{
	SysTick_var = us;
	while(SysTick_var != 0);
}

/**************************************************************************************************
*  					delay_ms()						  *
**************************************************************************************************/
void delay_ms(uint32_t ms)
{
	delay_us(1000*ms);
}

/**************************************************************************************************
*  					delay_ms()						  *
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
const char *get_uptime(void)		// const znaci da ce se return value samo citati izvan funkcije, valjda
{
	volatile static uint16_t uptime_ms = 0;
	volatile static uint8_t  uptime_s  = 0;
	volatile static uint8_t  uptime_m  = 0;
	volatile static uint8_t  uptime_h  = 0;
	volatile static uint16_t uptime_d  = 0;	// 170 godina

	//uptime_ms = uptime_us/1000;
	//uptime_ms = get_uptime_us()/1000;
	uptime_s  = uptime_ms/1000;

	printf("DEBUG: h:%d m:%d s:%d ms:%d us:%d\n", uptime_h, uptime_m, uptime_s, uptime_ms, uptime_us);

	// XXX sekunde idu do 64 pa onda ide 3-4x 0 sekundi pa krene isponova od 00
	// XXX ms je 16b (64k) i tek nakon sto se prelije dodje u nulu

	if (uptime_ms >= 1000)
	{
		uptime_ms = 0;
		uptime_s++;
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

	//sprintf(uptime_str, "uptime: %d days, %.2d:%.2d:%.2d.%.3d", uptime_d, uptime_h, uptime_m, uptime_s, uptime_ms);
	sprintf(uptime_str, "uptime: %d days, %.2d:%.2d:%.2d", uptime_d, uptime_h, uptime_m, uptime_s);

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
		SysTick_var--;	// za delay, korisnik je moze mijenjat
		uptime_us++;	// za uptime, korisnik je ne mijenja
	}
}
