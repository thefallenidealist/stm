#ifndef NRF_H
#define NRF_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h> 	// atoi
#include <stdbool.h>

#ifdef STM32F10X_MD
	#include "stm32f10x_rcc.h"
	#include "stm32f10x_gpio.h"
	#include "stm32f10x_spi.h"
#endif
#ifdef STM32F4XX
	#include "stm32f4xx_rcc.h"
	#include "stm32f4xx_gpio.h"
	#include "stm32f4xx_spi.h"
#endif
#include "gpio.h"
#include "spi.h"

#define SPI1_PORT	GPIOA
//#define SPI1_RCC	RCC_APB2Periph_GPIOA	// F1
#define SPI1_RCC	RCC_AHB1Periph_GPIOA	// F4
#define SPI1_SCK	GPIO_Pin_5
#define SPI1_MISO	GPIO_Pin_6
#define SPI1_MOSI	GPIO_Pin_7

#define SPI2_PORT	GPIOB
#define SPI2_SCK	GPIO_Pin_13
#define SPI2_MISO	GPIO_Pin_14
#define SPI2_MOSI	GPIO_Pin_15

typedef	struct nRF_hw_t nRF_hw_t;		// prototip structa nRF_t

//typedef struct
// nema typedefa jer ga ima gore, kasnije u kodu se moze pozivat bez "struct" (typedef applied)
struct nRF_hw_t
{
	//nRF_pins_t	pins;	// nasljedjivanje, wheee
	char	*spi;
	char	*cs;
	char	*ce;
	char	*irq;
	char	*name;
};

enum
{
	//EXIT_SUCCESS,	// ima vec u stdlib
	EXIT_FAILED = -99,
	EXIT_WRONG_SPI,
	EXIT_WRONG_SPI_NUMBER,
	EXIT_WRONG_GPIO_PORT,
	EXIT_WRONG_GPIO_PIN,
	EXIT_WRONG_GPIO_DIRECTION
};

nRF_hw_t *nRF_new(const char *name);
void nRF_main();

#endif
