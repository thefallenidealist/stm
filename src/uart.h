#ifndef UART_H
#define UART_H

// *************************************** sys includes *******************************************
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// *************************************** local includes *****************************************
#if defined STM32F10X_MD || defined STM32F1
	#include "stm32f10x_rcc.h"
	#include "stm32f10x_gpio.h"
	#include "stm32f10x_usart.h"
	#include "misc.h" 		// NVIC_Init()
#endif
#if defined STM32F4XX || defined STM32F4
	#include "stm32f4xx_rcc.h"
	#include "stm32f4xx_gpio.h"
	#include "stm32f4xx_usart.h"
	#include "misc.h" 		// NVIC_Init()
#endif

#include "debug.h"
#include "delay.h"
#include "cmd.h"

// *************************************** defines ************************************************
#if defined STM32F10X_MD || defined STM32F1
	// STM32F103C8T6
	// UART1
	#define UART1_GPIO_RCC		RCC_APB2Periph_GPIOA
	#define UART1_RCC			RCC_APB2Periph_USART1
	#define UART1_GPIO			GPIOA
	#define UART1_TX_Pin		GPIO_Pin_9	// PA9
	#define UART1_RX_Pin		GPIO_Pin_10	// PA10
	// UART2
	#define UART2_GPIO_RCC		RCC_APB2Periph_GPIOA
	#define UART2_RCC			RCC_APB1Periph_USART2
	#define UART2_GPIO			GPIOA
	#define UART2_TX_Pin		GPIO_Pin_2	// PA2
	#define UART2_RX_Pin		GPIO_Pin_3	// PA3
	// UART3
	#define UART3_GPIO_RCC		RCC_APB2Periph_GPIOB
	#define UART3_RCC			RCC_APB1Periph_USART3
	#define UART3_GPIO			GPIOB
	#define UART3_TX_Pin		GPIO_Pin_10	// PB10
	#define UART3_RX_Pin		GPIO_Pin_11	// PB11
#endif

#if defined STM32F4XX || defined STM32F4
	// STM32F407VGT6
	// UART1
	#define UART1_GPIO_RCC		RCC_AHB1Periph_GPIOB
	#define UART1_GPIO			GPIOB
	#define UART1_TX_Pin		GPIO_Pin_6
	#define UART1_RX_Pin		GPIO_Pin_7
	#define UART1_TX_AF			GPIO_PinSource6
	#define UART1_RX_AF			GPIO_PinSource7

// TODO
    #define UART2_RCC_GPIO      RCC_AHB1Periph_GPIOD
    #define UART2_RCC           RCC_APB1Periph_USART2
    #define UART2_TX            GPIO_Pin_5
    #define UART2_RX            GPIO_Pin_6
#endif

// 
#define UART_MAX_LENGTH	100
#define MAX_WLAN_BUFFER 1000

// *************************************** function prototypes ************************************
void uart1_init(uint32_t speed);
void uart2_init(uint32_t speed);
void uart1_parse(void);
void uart_clear(uint8_t uart);
void USART1_IRQHandler(void);    // javno zbog debugiranja/igranja
void USART2_IRQHandler(void);    // javno zbog debugiranja/igranja
void uart_write_string(uint8_t uart, char *arg);
void uart_init(uint8_t uart_number, uint32_t speed);

// *************************************** variables **********************************************
typedef enum
{
	RX_IN_PROGRESS = 0,
	RX_DONE,
	RX_PRINTED,
    RX_OVERFLOW
} rx_event_t;

extern volatile rx_event_t uart1_rx_event;
extern volatile rx_event_t uart2_rx_event;
extern volatile char uart1_rx_string_arr[UART_MAX_LENGTH];
///extern volatile char uart2_rx_string_arr[UART_MAX_LENGTH];
extern volatile char uart2_rx_string_arr[MAX_WLAN_BUFFER];

void uart_clear(uint8_t uart);

extern uint16_t uart2_rx_position;

#endif
