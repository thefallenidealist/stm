#ifndef LED_H
#define LED_H

// *************************************** description ********************************************
// KK madjija
// *************************************** sys includes *******************************************
#include <stdio.h>
#include <stdlib.h> 		// NULL
#ifdef STM32F10X_MD
	#include "stm32f10x_rcc.h"
	#include "stm32f10x_gpio.h"
#endif
#ifdef STM32F4XX
	#include "stm32f4xx_rcc.h"
	#include "stm32f4xx_gpio.h"
#endif
// *************************************** defines ************************************************
#define PORTA		GPIOA
#define PORTB		GPIOB
#define PORTC		GPIOC
#define PORTD		GPIOD

#ifdef STM32F10X_MD
	#define RCCA		RCC_APB2Periph_GPIOA
	#define RCCB		RCC_APB2Periph_GPIOB
#endif
#ifdef STM32F4XX
	#define RCCA		RCC_AHB1Periph_GPIOA
	#define RCCB		RCC_AHB1Periph_GPIOB
	#define RCCC		RCC_AHB1Periph_GPIOC
	#define RCCD		RCC_AHB1Periph_GPIOD
#endif

// *************************************** variables **********************************************
// mora bit ovdje zbog prototipa funkcija
typedef struct 
{
	uint32_t rcc;
	GPIO_TypeDef *port;
	uint16_t pin;
} led_structure;

led_structure get_led_structure(char led_port, int led_pin);
void led_init_structure(led_structure structure);
void led_init(char* led);
void led_set(led_structure structure, uint8_t status);
void led(const char* led, uint8_t led_state);

#endif
