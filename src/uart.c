#include "uart.h"
#include "debug.h"
// TODO ujedinit uart1_init i uart2_init

// *************************************** variables **********************************************
volatile rx_event_t uart1_rx_event = RX_PRINTED;
volatile rx_event_t uart2_rx_event = RX_PRINTED;
//volatile rx_event_t uart3_rx_event = RX_PRINTED;
volatile char uart1_rx_string_arr[UART_MAX_LENGTH] = {};
//volatile char uart2_rx_string_arr[UART_MAX_LENGTH] = {};
volatile char uart2_rx_string_arr[MAX_WLAN_BUFFER] = {};
//volatile char uart3_rx_string_arr[UART_MAX_LENGTH] = {};


void uart_init(uint8_t uart_number, uint32_t speed)
{
	switch (uart_number)
	{
		case 1:
			uart1_init(speed);
			break;
		case 2:
			uart2_init(speed);
			break;
		case 3:
		case 4:
		case 5:
		case 6:
		default:
			printf("ERROR: %s(): Wrong UART: %d\n", __func__, uart_number);
			break;
	}

}

/************************************************************************************************
*  				UART1_init()							*
*************************************************************************************************/
void uart1_init(uint32_t speed)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	// 1 RCC init
	//RCC_APB2PeriphClockCmd(USART1_GPIO_RCC, ENABLE);	// F1	F4


	// GPIO clock
	//RCC_APB2PeriphClockCmd(USART1_RCC, ENABLE);	// F1
	//RCC_AHB1PeriphClockCmd(USART1_RCC, ENABLE);	// F4	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	// 3 GPIO

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
	//GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	//GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // GPIOB
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;	// GPIOA
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// F1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		// F4
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	//GPIO_Init(USART1_GPIO, &GPIO_InitStructure);
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//GPIO_Init(GPIOA, &GPIO_InitStructure);

	//GPIO_InitStructure.GPIO_Pin = USART1_RX_Pin;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// moze i IPD/IPU		// F1
	////GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;						// F4
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		// F4
	//GPIO_Init(USART1_GPIO, &GPIO_InitStructure);


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	USART_InitStructure.USART_BaudRate = speed;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		// CTS and RTS are not used
	USART_Init(USART1, &USART_InitStructure);
	//USART_Cmd(USART1, ENABLE);				// Enable USART1

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);	// mora bit ispod USART1 ENABLE

	// 2 NVIC
	// Enable the USART1 Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//void __enable_irq(void);

	USART_Cmd(USART1, ENABLE);				// Enable USART1
}

/************************************************************************************************
*  				UART2_init()							*
*************************************************************************************************/
void uart2_init(uint32_t speed)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	// 1 RCC init
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(UART2_RCC_GPIO, ENABLE);

	// 3 GPIO
    // TODO prebacit pinove u define
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);

	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Pin = UART2_TX | UART2_RX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		// F4
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);


	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB1PeriphClockCmd(UART2_RCC, ENABLE);

	USART_InitStructure.USART_BaudRate = speed;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		// CTS and RTS are not used
	USART_Init(USART2, &USART_InitStructure);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	//USART_ITConfig(USART2, USART_IT_TXE, ENABLE);	// mora bit ispod USART2 ENABLE

	// 2 NVIC
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART2, ENABLE);
}

/************************************************************************************************
*  				USART1_IRQHandler()						*
*************************************************************************************************/
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		/*
		   // samo proslijedi
		uart1_rx_event = RX_IN_PROGRESS;
		uint16_t rx_char = USART_ReceiveData(USART1);
		printf("UART1 RX: %d\n", rx_char);
			uart1_rx_event = RX_DONE;
			*/


		uart1_rx_event = RX_IN_PROGRESS;
		static uint8_t counter = 0; // this counter is used to determine the string length

		char rx_char = USART_ReceiveData(USART1);

		/*
		   ne isprazni buffer, ali uart_puts ce slat samo dok ne dobije \0
		   uart_puts mora poslat \n da ono cemu salje zna kad je kraj
		   */

		if ((rx_char != '\n') && (counter < UART_MAX_LENGTH-1))
		{
			//printf("counter: %d\n", counter);	// onda ne uspije sve primit
			uart1_rx_string_arr[counter] = rx_char;
			counter++;
			/*
			   // XXX ne radi
			if (counter > UART_MAX_LENGTH-1)
			{
				printf("UART1 RX je dobio previse znakova error\n");
			}
			*/
		}
		else
		{
			//printf("UART1 else: UART1 RX gotov\n");
			// obrisi ostatak buffera
			for (int i=counter; i<UART_MAX_LENGTH-1; i++)
			{
				uart1_rx_string_arr[i] = '\0';
			}
			counter = 0;
			uart1_rx_event = RX_DONE;

			uart_parse();
		}
	}

	/*

	static int counter=0;
	// interrupt treba testirat da zna jel RX ili TX u pitanju
	if (USART_GetITStatus(USART1, USART_IT_TXE) == SET)
	{
		// stalno zaglavi ovdje
		//printf("UART1 TX IRQ\n");	// stalno salje

		   // neat pizdarijica svijetli ko Betlehem, u terminalu nista
		USART_SendData(USART1, testbuffer[counter++]);

		//printf("counter: %d\n", counter);
		if (counter >= (sizeof(testbuffer)-1))
		{
			counter = 0;
			USART_ITConfig(USART1, UART_IT_TXE, DISABLE);
		}
	}
	*/

	USART_ClearITPendingBit(USART1, USART_IT_ERR);
}

/************************************************************************************************
*  					uart_clear()																*
*************************************************************************************************/
void uart_clear(uint8_t uart)
{
	uart_puts(uart, "\033c");	// clear
}

/************************************************************************************************
*  					uart_puts()																	*
*************************************************************************************************/
void uart_puts(uint8_t uart, char *string)
{
	//printf("uart_puts(): string: %s\n", string);

	do
	{
		switch (uart)
		{
			case 1:
				while ((USART1->SR & USART_FLAG_TC) == (uint16_t)RESET);
				//printf("uart_puts() salje %c %d\n", *string, *string);
				USART1->DR = (*string++ & (uint16_t)0x01FF);
				break;
			case 2:
				while ((USART2->SR & USART_FLAG_TC) == (uint16_t)RESET);
				USART2->DR = (*string++ & (uint16_t)0x01FF);
				break;
			case 3:
				while ((USART3->SR & USART_FLAG_TC) == (uint16_t)RESET);
				//printf("uart_puts 3 salje: %c %d\n", *string, *string);
				USART3->DR = (*string++ & (uint16_t)0x01FF);
				break;
			default:
				printf("uart_puts(): wrong USART number\n");
				break;
		}
	} while (*string != '\0');
}
