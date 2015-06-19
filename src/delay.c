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
//_Atomic volatile static uint32_t delay_var;	// timer is 24b countdown
volatile static uint32_t delay_var;	// timer is 24b countdown

//volatile static uint32_t uptime_us=0;	
volatile uint32_t		uptime_us=0;	
static volatile char	uptime_str_arr[35] = {};	// 34 je maksimalno za 170 godina
static volatile char	*uptime_str = uptime_str_arr;
static volatile uint32_t gsystick_divider = 0;

/**************************************************************************************************
*  					delay_get divider
**************************************************************************************************/
uint32_t delay_get_divider(void)
{
	return gsystick_divider;
}

/**************************************************************************************************
*  					delay_init(void)					  *
**************************************************************************************************/
void delay_init(systick_divider_t divider)
{
	// zapisi u globalnu varijablu, treba za stimanje delay_ funkcija
	gsystick_divider = divider;

#ifdef STM32F4XX
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq(&RCC_Clocks);
    //SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000); // 1ms
    //SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000000);    // 1us
    SysTick_Config(RCC_Clocks.HCLK_Frequency / divider); 
#endif
#ifdef STM32F1
	//if(SysTick_Config(SystemCoreClock / 1000000) !=0)	// 1000000 Hz 1000 kHz	1Mhz	1us
	if(SysTick_Config(SystemCoreClock / divider) != 0)
	{
		while(1);	// error
	}
#endif
}

/**************************************************************************************************
*  					delay_us()						  *
**************************************************************************************************/
void delay_us(volatile uint32_t us)
{
	//printf("%s(): divider: %d\n", __func__, gsystick_divider);
	//printf("%s(): arg: %d\n", __func__, us);
	//if (gsystick_divider == TICK_EVERY_US)
	{
		delay_var = us;
		do
		{
			printf("%s(): delay_var: %d\n", __func__, delay_var);
		}
		while (delay_var != 0);	// delay_var se smanjuje svake 1us
	}
}

/**************************************************************************************************
*  					delay_ms()						  *
**************************************************************************************************/
void delay_ms(uint32_t ms)
{
	if (gsystick_divider == TICK_EVERY_US)
	{
		delay_us(1000*ms);
	}
}

/**************************************************************************************************
*  					delay_s()						  *
**************************************************************************************************/
void delay_s(uint32_t s)
{
	if (gsystick_divider == TICK_EVERY_US)
	{
		delay_us(1000*1000*s);	// max 4294 s
	}
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
const char *get_uptime(void)
{
	volatile static uint16_t uptime_ms = 0;
	volatile static uint8_t  uptime_s  = 0;
	volatile static uint8_t  uptime_m  = 0;
	volatile static uint8_t  uptime_h  = 0;
	volatile static uint16_t uptime_d  = 0;	// 170 godina
	volatile static uint8_t  msb_ms	= 0;

	uptime_ms = (uint16_t)(round(uptime_us/1000.0)) % 60000;

	if (uptime_ms >= 1000)
	{
		if (msb_ms != ((uint16_t)round(((uptime_ms/1000.0))) % 60))
		{
			msb_ms = ((uint16_t)round(((uptime_ms/1000.0))) % 60);
			uptime_s++;
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
	sprintf((char*)uptime_str, "%d days, %.2d:%.2d:%.2d.%.3d", uptime_d, uptime_h, uptime_m, uptime_s, uptime_ms%1000);

	return (char *)uptime_str;
}

/**************************************************************************************************
*  					SysTick_Handler(void)					  *
**************************************************************************************************/
void SysTick_Handler(void)
{
	// IRQ every 1 us

	uptime_us++;	// za uptime, korisnik je ne mijenja	TODO popravit da radi i za druge (zasad samo radi sa 1 us tick)

	if (delay_var != 0)
	{
		delay_var--;	// za delay, korisnik je moze mijenjat
	}
}
