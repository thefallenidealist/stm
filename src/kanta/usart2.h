#ifndef USART2_H
#define USART2_H

#include <stdio.h>
#include <stdint.h>
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

#define USART_MAX_CHARS	100
void USART2_init(uint32_t speed);
#define USART2_GPIO_RCC		RCC_APB2Periph_GPIOA
#define USART2_RCC		RCC_APB2Periph_USART1
#define USART2_GPIO		GPIOA
#define USART2_TX_Pin		GPIO_Pin_2
#define USART2_RX_Pin		GPIO_Pin_3

#endif
