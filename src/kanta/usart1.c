#include "usart1.h"

// *************************************** variables **********************************************
/*
volatile uint8_t RXbuffer[USART_MAX_CHARS];	// temp
volatile uint8_t RXcounter = 0;			// koliko charova je u bufferu
volatile uint8_t DMA_RXbuffer[USART_MAX_CHARS];	// temp, ovdje DMA sprema, kad zavrsi kopira ga u RXbuffer
volatile uint8_t usart1_rx_ready = 0;

volatile char buffer[10];
*/

void USART1_init(uint32_t speed)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// 1 RCC init
	RCC_APB2PeriphClockCmd(USART1_GPIO_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(USART1_RCC, ENABLE);
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	// DMA clock
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		// moguce da i ne treba

	// 2 NVIC
	// Enable the USART1 Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	// Enable the USART1 RX DMA Interrupt 
	/*
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	*/

	// 3 GPIO
	// Configure USART1 Tx (PA9) as alternate function push-pull
	GPIO_InitStructure.GPIO_Pin = USART1_TX_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(USART1_GPIO, &GPIO_InitStructure);
	// Configure USART1 Rx (PA10) as input floating
	GPIO_InitStructure.GPIO_Pin = USART1_RX_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// moze i IPD/IPU
	GPIO_Init(USART1_GPIO, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = speed;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);				// Enable USART1
}
