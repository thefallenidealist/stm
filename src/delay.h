#ifndef DELAY_H
#define DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

// *************************************** description ********************************************
/*
   140907
   knjiga: 351
   blocking delay
*/
// *************************************** sys includes *******************************************
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#if defined STM32F10X_MD || defined STM32F1
	#include "stm32f10x.h" 		// includa core_cm3 koji treba za SystemCoreClock, ima i system_stm32f10x.h
	#include "stm32f10x_rcc.h"
#endif
#if defined STM32F4XX || defined STM32F4
	#include "stm32f4xx.h"
	#include "stm32f4xx_rcc.h"
#endif

#ifdef AVR
	#include <util/delay.h>
#endif

// TODO preimenovat u uptime_get_s i sl
// TODO uptime u novi header
// TODO AVR uptime?

typedef enum
{
	// djelitelji za SysTick_Config()
	TICK_EVERY_NS 		= 1000000000,
	TICK_EVERY_100NS 	= 10000000,
	TICK_EVERY_US 		= 1000000,
	TICK_EVERY_MS 		= 1000
} systick_divider_t;

//void delay_init(void);
uint32_t delay_get_divider(void);
void delay_init(systick_divider_t divider);
void delay_ns(uint32_t ns);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
void delay_s(uint32_t s);

uint32_t get_uptime_us(void);
uint32_t get_uptime_ms(void);
uint32_t get_uptime_s(void);
const char *get_uptime(void);

void SysTick_Handler(void);     // javni samo zbog debuga/igranja

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif	// DELAY_H
