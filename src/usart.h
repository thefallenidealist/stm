#ifndef USART_H
#define USART_H

// *************************************** sys includes *******************************************
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "delay.h"
#include "cmd.h"

// *************************************** local includes *****************************************
#ifdef STM32F10X_MD
	#include "stm32f10x_rcc.h"
	#include "stm32f10x_gpio.h"
	#include "stm32f10x_usart.h"
#endif
#ifdef STM32F4XX
// XXX odjednom je ovo prestalo radit iako radi u drugim fajlovima
	#include "stm32f4xx_rcc.h"
	#include "stm32f4xx_gpio.h"
	#include "stm32f4xx_usart.h"
	#include "misc.h" 		// NVIC_Init()
#endif
	#include "stm32f4xx_usart.h"
	#include "misc.h" 		// NVIC_Init()

// *************************************** defines ************************************************
#ifdef STM32F10X_MD
// STM32F103C8T6
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
#endif

#ifdef STM32F4XX
	// STM32F407VGT6
	// USART1
	#define USART1_GPIO_RCC		RCC_AHB1Periph_GPIOA
	#define USART1_RCC		RCC_APB2Periph_USART1
	#define USART1_GPIO		GPIOA
	//#define USART1_TX_Pin		GPIO_Pin_9	// PA9	// XXX navodno ne radi zbog kondenzatora na tom pinu
	//#define USART1_RX_Pin		GPIO_Pin_10	// PA10
	//#define USART1_TX_Pin		GPIO_Pin_9	// PA9	// XXX navodno ne radi zbog kondenzatora na tom pinu
	//#define USART1_RX_Pin		GPIO_Pin_10	// PA10
#endif

// 
#define USART_MAX_LENGTH	100

// *************************************** function prototypes ************************************
void USART1_init(uint32_t speed);
void USART2_init(uint32_t speed);
void USART3_init(uint32_t speed);
void usart1_parse(void);
void usart_puts(uint8_t usart, char *string);
void usart_clear(uint8_t usart);


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
