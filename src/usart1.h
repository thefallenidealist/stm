#ifndef USART1_H
#define USART1_H

#include <stdio.h>
#include <stdint.h>
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

#define USART_MAX_CHARS	100
void USART1_init(uint32_t speed);
#define USART1_GPIO_RCC		RCC_APB2Periph_GPIOA
#define USART1_RCC		RCC_APB2Periph_USART1
#define USART1_GPIO		GPIOA
#define USART1_TX_Pin		GPIO_Pin_9	// PA9
#define USART1_RX_Pin		GPIO_Pin_10	// PA10

#endif
