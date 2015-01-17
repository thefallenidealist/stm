#ifndef DELAY_H
#define DELAY_H

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
#ifdef STM32F10X_MD
	#include "stm32f10x.h" 		// includa core_cm3 koji treba za SystemCoreClock, ima i system_stm32f10x.h
#endif
#ifdef STM32F4XX
	#include "stm32f4xx.h"
#endif

void delay_init(void);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
void delay_s(uint32_t s);
uint32_t get_uptime_us(void);
uint32_t get_uptime_ms(void);
uint32_t get_uptime_s(void);
const char *get_uptime(void);
void SysTick_Handler(void);

#endif
