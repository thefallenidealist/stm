#include "uart.h"
// TODO ujedinit uart1_init i uart2_init

// *************************************** variables **********************************************
volatile rx_event_t uart1_rx_event = RX_PRINTED;
volatile rx_event_t uart2_rx_event = RX_PRINTED;
volatile char uart1_rx_string_arr[UART_MAX_LENGTH] = {};
//volatile char uart2_rx_string_arr[UART_MAX_LENGTH] = {};
volatile char uart2_rx_string_arr[MAX_WLAN_BUFFER] = {};	// INFO WLAN module kludge
uint16_t uart2_rx_position = 0;

void uart_init(uint8_t uart_number, uint32_t speed)
{
	switch (uart_number)
	{
		case 1:
			uart1_init(speed);
			break;
		case 2:
			//uart2_init(speed);	TODO F1 
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

#if defined STM32F1 || defined STM32F10X_MD
	RCC_APB2PeriphClockCmd(UART1_GPIO_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(UART1_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;

	GPIO_InitStructure.GPIO_Pin = UART1_TX_Pin;
	GPIO_Init(UART1_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = UART1_RX_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// moze i IPD/IPU

	GPIO_Init(UART1_GPIO, &GPIO_InitStructure);
#endif

#if defined STM32F4XX || defined STM32F4
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_PinAFConfig(UART1_GPIO, UART1_TX_AF, GPIO_AF_USART1);
	GPIO_PinAFConfig(UART1_GPIO, UART1_RX_AF, GPIO_AF_USART1);

	GPIO_InitStructure.GPIO_Pin 	= UART1_RX_Pin | UART1_TX_Pin; 
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;

	GPIO_Init(UART1_GPIO, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
#endif

	USART_InitStructure.USART_BaudRate 		= speed;
	USART_InitStructure.USART_WordLength 	= USART_WordLength_8b;
	USART_InitStructure.USART_StopBits 		= USART_StopBits_1;
	USART_InitStructure.USART_Parity 		= USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode 			= USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);				// Enable USART1

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);	// mora bit ispod USART1 ENABLE

	// Enable the USART1 Interrupt
	NVIC_InitStructure.NVIC_IRQChannel 						= USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/************************************************************************************************
*  				UART2_init()							*
*************************************************************************************************/
/*
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
*/

/************************************************************************************************
*  				USART1_IRQHandler()						*
*************************************************************************************************/
void USART1_IRQHandler(void)
{
	// kopira u glavni buffer sve dok ne dobije \n
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{

		uart1_rx_event = RX_IN_PROGRESS;
		static uint8_t counter = 0; // this counter is used to determine the string length

		char rx_char = USART_ReceiveData(USART1);

		if ((rx_char != '\n') && (counter < UART_MAX_LENGTH-1))
		{
			uart1_rx_string_arr[counter] = rx_char;
			counter++;
		}
		else if (rx_char == '\n')
		{
			// evo nas na kraju, obrisi ostatak buffera
			for (int i=counter; i<UART_MAX_LENGTH-1; i++)
			{
				uart1_rx_string_arr[i] = '\0';
			}
			counter = 0;
			uart1_rx_event = RX_DONE;

			uart_parse();
		}
		else
		{
			// pregazili smo buffer
		}
	}

	USART_ClearITPendingBit(USART1, USART_IT_ERR);
}

/************************************************************************************************
*  					uart_clear()																*
*************************************************************************************************/
void uart_clear(uint8_t uart)
{
	uart_write_string(uart, "\033c");
}

/************************************************************************************************
*  					uart_write_string()
*************************************************************************************************/
//void uart_puts(uint8_t uart, char *string)
void uart_write_string(uint8_t uart, char *arg)
{
	do
	{
		switch (uart)
		{
			case 1:
				while ((USART1->SR & USART_FLAG_TC) == (uint16_t)RESET);
				USART1->DR = (*arg++ & (uint16_t)0x01FF);
				break;
			case 2:
				while ((USART2->SR & USART_FLAG_TC) == (uint16_t)RESET);
				USART2->DR = (*arg++ & (uint16_t)0x01FF);
				break;
			case 3:
				while ((USART3->SR & USART_FLAG_TC) == (uint16_t)RESET);
				USART3->DR = (*arg++ & (uint16_t)0x01FF);
				break;
			default:
				printf("%s(): wrong USART number: %d\n", __func__, uart);
				break;
		}
	} while (*arg != '\0');
}

/*************************************************************************************************
  				USART2 IRQ
*************************************************************************************************/
void USART2_IRQHandler(void)
{
	// ovaj nastiman za WLAN modul
	// samo kopira u globalni buffer
	//static uint16_t uart2_rx_position = 0;

	/*
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		uint16_t rx_char = USART_ReceiveData(USART2);
        {
        	uart2_rx_string_arr[uart2_rx_position++] = rx_char;
        }
	}
	*/
	// TODO isprobat, mozda mrvicu bolja verzija onoga gore:
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
        uart2_rx_string_arr[uart2_rx_position++] = USART_ReceiveData(USART2);
	}
}
