#ifndef RTC_H
#define RTC_H

// Vbat 1.8 - 3.6V	TODO
// XXX RTC_SetCounter nikad ne izadje 
// jebeni RTC

// XXX tocnost	99.2%, kasni ~7 sekundi na 35 minuta

#include <stdio.h>
#include "stm32f10x_rcc.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_bkp.h" 	// treba za RTC, battery backuped registers
#include "stm32f10x_pwr.h" 	// treba za bkp

uint32_t get_uptime();
void RTC_init2();
void time_zapisi();
void RTC_init();
void RTC_update();
void time_print();
uint8_t RTC_get_h();
uint8_t RTC_get_m();
uint8_t RTC_get_s();
void RTC_IRQHandler(void);

#endif
