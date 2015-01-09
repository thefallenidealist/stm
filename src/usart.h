#ifndef USART_H
#define USART_H

// *************************************** sys includes *******************************************
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// *************************************** local includes *****************************************
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

// *************************************** defines ************************************************
// USART1
#define USART1_GPIO_RCC		RCC_APB2Periph_GPIOA
#define USART1_RCC		RCC_APB2Periph_USART1
#define USART1_GPIO		GPIOA
#define USART1_TX_Pin		GPIO_Pin_9	// PA9
#define USART1_RX_Pin		GPIO_Pin_10	// PA10
// USART2
#define USART2_GPIO_RCC		RCC_APB2Periph_GPIOA
#define USART2_RCC		RCC_APB1Periph_USART2
#define USART2_GPIO		GPIOA
#define USART2_TX_Pin		GPIO_Pin_2	// PA2
#define USART2_RX_Pin		GPIO_Pin_3	// PA3
// USART3
#define USART3_GPIO_RCC		RCC_APB2Periph_GPIOB
#define USART3_RCC		RCC_APB1Periph_USART3
#define USART3_GPIO		GPIOB
#define USART3_TX_Pin		GPIO_Pin_10	// PB10
#define USART3_RX_Pin		GPIO_Pin_11	// PB11
// 
#define USART_MAX_LENGTH	100

// *************************************** function prototypes ************************************
void USART1_init(uint32_t speed);
void USART2_init(uint32_t speed);
void USART3_init(uint32_t speed);
void usart1_parse(void);
void usart_puts(uint8_t usart, char *string);


// *************************************** variables **********************************************
typedef enum
{
	RX_IN_PROGRESS,		// 0
	RX_DONE,		// 1
	RX_PRINTED		// 2
} rx_event_t;
extern volatile rx_event_t usart1_rx_event;
extern volatile rx_event_t usart2_rx_event;
extern volatile rx_event_t usart3_rx_event;
extern volatile char usart1_rx_string_arr[USART_MAX_LENGTH];
extern volatile char usart2_rx_string_arr[USART_MAX_LENGTH];
extern volatile char usart3_rx_string_arr[USART_MAX_LENGTH];

#endif
