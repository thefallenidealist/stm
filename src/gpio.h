// created 150218
#ifndef GPIO_H
#define GPIO_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> 	// atoi
#include <stdbool.h>

#ifdef STM32F10X_MD
	#include "stm32f10x_rcc.h"
	#include "stm32f10x_gpio.h"
#endif
#ifdef STM32F4XX
	#include "stm32f4xx_rcc.h"
	#include "stm32f4xx_gpio.h"
#endif

#include "debug.h"

#ifdef STM32F4XX
	#define RCCA	RCC_AHB1Periph_GPIOA
	#define RCCB	RCC_AHB1Periph_GPIOB
	#define RCCC	RCC_AHB1Periph_GPIOC
	#define RCCD	RCC_AHB1Periph_GPIOD
	#define RCCE	RCC_AHB1Periph_GPIOE
#endif
// TODO mali ARM

/*************************************************************************************************
		new data types
*************************************************************************************************/
/********************		direction_t		********************/
typedef enum
{
	IN = 0,
	OUT = 1
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
} state_t;

/********************		gpio_hw_t		********************/
typedef struct
{
	uint32_t 		rcc;
	GPIO_TypeDef 	*port;
	uint16_t 		pin;
	//direction_t		direction;		// not implemented
} gpio_hw_t;

/********************		gpio_t		********************/
typedef struct
{
	//direction_t		direction;		// not implemented
} gpio_t;

/*************************************************************************************************
		function prototypes
*************************************************************************************************/
int8_t 	gpio_init	(const char *arg, direction_t direction);
int8_t	gpio		(const char *arg, state_t state);
bool 	gpio_read	(const char *arg);

#endif
