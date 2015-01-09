#ifndef LED_H
#define LED_H

// *************************************** description ********************************************
// KK madjija
// *************************************** sys includes *******************************************
#include <stdio.h>
#include <stdlib.h> 		// NULL
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
// *************************************** defines ************************************************
/*
#define LEDx_RCC	RCC_APB2Periph_GPIOB
#define LEDx_PORT	GPIOB
#define LEDx_PIN	GPIO_Pin_0
*/

#define LED0_PIN	GPIO_Pin_0
#define LED1_PIN	GPIO_Pin_1
#define LED2_PIN	GPIO_Pin_2
#define LED3_PIN	GPIO_Pin_3
#define LED4_PIN	GPIO_Pin_4
#define LED5_PIN	GPIO_Pin_5
#define LED6_PIN	GPIO_Pin_6
#define LED7_PIN	GPIO_Pin_7
#define LED8_PIN	GPIO_Pin_8
#define LED9_PIN	GPIO_Pin_9
#define LED10_PIN	GPIO_Pin_10
#define LED11_PIN	GPIO_Pin_11
#define LED12_PIN	GPIO_Pin_12
#define LED13_PIN	GPIO_Pin_13
#define LED14_PIN	GPIO_Pin_14
#define LED15_PIN	GPIO_Pin_15

#define RCCA		RCC_APB2Periph_GPIOA
#define RCCB		RCC_APB2Periph_GPIOB
#define PORTA		GPIOA
#define PORTB		GPIOB

// *************************************** variables **********************************************
// mora bit ovdje zbog prototipa funkcija
typedef struct 
{
	uint32_t rcc;
	// compiler specific
	//__typeof__ (LEDx_PORT) port;
	//uint32_t port;
	//struct GPIO_TypeDef *port;		// note: expected 'struct GPIO_TypeDef *' but argument is of type 'struct GPIO_TypeDef *'
	GPIO_TypeDef *port;
	uint16_t pin;
} led_structure;

led_structure get_led_structure(char led_port, int led_pin);
void led_init_structure(led_structure structure);
void led_init(char* led);
void led_set(led_structure structure, uint8_t status);
void led(char* led, uint8_t led_state);

#endif
