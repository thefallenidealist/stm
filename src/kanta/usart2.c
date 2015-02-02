#include "usart2.h"

// *************************************** variables **********************************************

void USART2_init(uint32_t speed)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// 1 RCC init
	RCC_APB2PeriphClockCmd(USART2_GPIO_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(USART2_RCC, ENABLE);
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	// DMA clock
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		// moguce da i ne treba

	// 3 GPIO
	// Configure USART2 Tx (PA9) as alternate function push-pull
	GPIO_InitStructure.GPIO_Pin = USART2_TX_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(USART2_GPIO, &GPIO_InitStructure);
	// Configure USART2 Rx (PA10) as input floating
	GPIO_InitStructure.GPIO_Pin = USART2_RX_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// moze i IPD/IPU
	GPIO_Init(USART2_GPIO, &GPIO_InitStructure);

	// 9600 8N1 noHW
	//USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_BaudRate = speed;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);
	USART_Cmd(USART2, ENABLE);				// Enable USART1
}
