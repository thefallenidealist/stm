#ifndef UART_H
#define UART_H

// *************************************** sys includes *******************************************
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "delay.h"
#include "cmd.h"
#include "wlan.h"

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
// UART1
#define UART1_GPIO_RCC		RCC_APB2Periph_GPIOA
#define UART1_RCC		RCC_APB2Periph_UART1
#define UART1_GPIO		GPIOA
#define UART1_TX_Pin		GPIO_Pin_9	// PA9
#define UART1_RX_Pin		GPIO_Pin_10	// PA10
// UART2
#define UART2_GPIO_RCC		RCC_APB2Periph_GPIOA
#define UART2_RCC		RCC_APB1Periph_UART2
#define UART2_GPIO		GPIOA
#define UART2_TX_Pin		GPIO_Pin_2	// PA2
#define UART2_RX_Pin		GPIO_Pin_3	// PA3
// UART3
#define UART3_GPIO_RCC		RCC_APB2Periph_GPIOB
#define UART3_RCC		RCC_APB1Periph_UART3
#define UART3_GPIO		GPIOB
#define UART3_TX_Pin		GPIO_Pin_10	// PB10
#define UART3_RX_Pin		GPIO_Pin_11	// PB11
#endif

#ifdef STM32F4XX
	// STM32F407VGT6
	// UART1
	#define UART1_GPIO_RCC		RCC_AHB1Periph_GPIOA
	#define UART1_RCC		RCC_APB2Periph_UART1
	#define UART1_GPIO		GPIOA
	//#define UART1_TX_Pin		GPIO_Pin_9	// PA9	// XXX navodno ne radi zbog kondenzatora na tom pinu
	//#define UART1_RX_Pin		GPIO_Pin_10	// PA10

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
void uart_puts(uint8_t uart, char *string);
void uart_clear(uint8_t uart);
void USART1_IRQHandler(void);    // javno zbog debugiranja/igranja
void uart_puts(uint8_t uart, char *string);



// *************************************** variables **********************************************
typedef enum
{
	RX_IN_PROGRESS,		// 0
	RX_DONE,		// 1
	RX_PRINTED,		// 2
    RX_OVERFLOW
} rx_event_t;
extern volatile rx_event_t uart1_rx_event;
extern volatile rx_event_t uart2_rx_event;
extern volatile char uart1_rx_string_arr[UART_MAX_LENGTH];
///extern volatile char uart2_rx_string_arr[UART_MAX_LENGTH];
extern volatile char uart2_rx_string_arr[MAX_WLAN_BUFFER];



extern uint16_t uart2_rx_position;


#endif
