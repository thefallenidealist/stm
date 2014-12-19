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
#include "stm32f10x.h" 		// includa core_cm3 koji treba za SystemCoreClock, ima i system_stm32f10x.h
void delay_init(void);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
uint32_t get_us(void);
void SysTick_Handler(void);

#endif
