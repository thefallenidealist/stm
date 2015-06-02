// created 150218
#ifndef GPIO_H
#define GPIO_H

/*
   TODO
   gpio_init ANALOG_IN, DIGITAL_IN, IN
   			ANALOG_OUT, DIGITAL_OUT, OUT	// PWM, default 10 kHz

	gpio_write(pin, stanje)
	gpio_write_analog(pin, intenzitet)
	gpio_read(pin)
	gpio_read_analog(pin);

	mozda bi se moglo sve unutar jedne funkcije, stanje uint8_t, ako je veci od 1 onda je to
	intenzitet. PWM ide u postotcima od 1%
	gpio_write(pin, stanje/intenzitet)
	gpio_read(pin);

   */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> 	// atoi
#include <stdbool.h>

#if defined STM32F10X_MD || defined STM32F1
	#include "stm32f10x_rcc.h"
	#include "stm32f10x_gpio.h"
#endif
#if defined STM32F4XX || defined STM32F4
	#include "stm32f4xx_rcc.h"
	#include "stm32f4xx_gpio.h"
#endif

#ifndef AVR
	#include "debug.h"
#endif

#ifdef STM32F1
	#define RCCA	RCC_APB2Periph_GPIOA
	#define RCCB	RCC_APB2Periph_GPIOB
	#define RCCC	RCC_APB2Periph_GPIOC
#endif

#ifdef STM32F4XX
	#define RCCA	RCC_AHB1Periph_GPIOA
	#define RCCB	RCC_AHB1Periph_GPIOB
	#define RCCC	RCC_AHB1Periph_GPIOC
	#define RCCD	RCC_AHB1Periph_GPIOD
	#define RCCE	RCC_AHB1Periph_GPIOE
#endif

#ifdef AVR
	#include <avr/io.h>
	//#include <avr/delay.h>
#endif

/*************************************************************************************************
		new data types
*************************************************************************************************/
/********************		direction_t		********************/
typedef enum
{
	IN 			= 0,
	OUT 		= 1,
	DIGITAL_IN 	= 0,
	DIGITAL_OUT = 1,
	ANALOG_IN 	= 2,
	ANALOG_OUT 	= 3,
	IN_PU,
	IN_PD
} direction_t;

/********************		anonymous		********************/
enum
{
	EXIT_GPIO_WRONG_DIRECTION,
	EXIT_GPIO_SUCCESS = 0
};

/********************		state_t		********************/
typedef enum
{
	OFF = 0,
	ON  = 1,
	TOGGLE = 2
		// TODO
		// OFF = 101, ON = 102, ...
		// ispod 100 su intenzitet PWMa
} state_t;

/********************		gpio_hw_t		********************/
typedef struct
{
#ifndef AVR
	uint32_t 		rcc;
	GPIO_TypeDef 	*port;
#endif
#ifdef AVR
	uint8_t			ddr;
	uint8_t			port;
	//int8_t			port;
#endif
	uint16_t 		pin;
	//direction_t		direction;		// not implemented
	//direction_t		type;		// not implemented
} gpio_hw_t;

/********************		gpio_t		********************/
typedef struct
{
	//direction_t		direction;		// not implemented
} gpio_t;

/*************************************************************************************************
		function prototypes
*************************************************************************************************/
int8_t 	gpio_init	(const char *pin, direction_t direction);
int8_t	gpio_write	(const char *pin, state_t state);
bool 	gpio_read	(const char *pin);

#endif
