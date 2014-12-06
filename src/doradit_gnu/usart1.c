/*
   ST AN3109
   STM32 ima single RX/TX buffer.
   DMA irq se koriste da se zna pocetak i kraj transmisije


USART1: DMA
ch4	TX
ch5	RX
*/

// *************************************** sys includes *******************************************
//#include "stm32f10x_dma.h"
//#include "stm32f10x_dma.c"
// *************************************** local includes *****************************************
// *************************************** variables **********************************************
#define USART_MAX_CHARS	100
volatile uint8_t RXbuffer[USART_MAX_CHARS];	// temp
volatile uint8_t RXcounter = 0;			// koliko charova je u bufferu
volatile uint8_t DMA_RXbuffer[USART_MAX_CHARS];	// temp, ovdje DMA sprema, kad zavrsi kopira ga u RXbuffer
volatile uint8_t usart1_rx_ready = 0;

volatile char buffer[10];

void USART1_init(uint32_t speed)
{
#define USART1_GPIO_RCC		RCC_APB2Periph_GPIOA
#define USART1_RCC		RCC_APB2Periph_USART1
#define USART1_GPIO		GPIOA
#define USART1_TX_Pin		GPIO_Pin_9	// PA9
#define USART1_RX_Pin		GPIO_Pin_10	// PA10

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//DMA_InitTypeDef DMA_InitStructure;

	// 1 RCC init
	RCC_APB2PeriphClockCmd(USART1_GPIO_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(USART1_RCC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	// DMA clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		// moguce da i ne treba

	// 2 NVIC
	// Enable the USART1 Interrupt
	/*
	// nije potrebno kad se ima DMA
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	*/

	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	// Enable the USART1 RX DMA Interrupt 
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

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

	// 4 DMA
	/*
	   // sluzbeni primjer
	// USARTy_Tx_DMA_Channel (triggered by USARTy Tx event) Config
	DMA_DeInit(USART1_TX_DMA_CH);
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)TxBuffer1;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = TxBufferSize1;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(USARTy_Tx_DMA_Channel, &DMA_InitStructure);
	// USARTz_Tx_DMA_Channel (triggered by USARTz Tx event) Config
	DMA_DeInit(USARTz_Tx_DMA_Channel);
	DMA_InitStructure.DMA_PeripheralBaseAddr = USARTz_DR_Base;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)TxBuffer2;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = TxBufferSize2;
	DMA_Init(USARTz_Tx_DMA_Channel, &DMA_InitStructure);
	*/



	/*
	// USART1 RX DMA
	// mislim da mi nije potreban TX DMA, a i treba znat unaprijed velicinu stringa koji se salje na serijski preko DMA
#define USART1_DMA_RX	DMA1_Channel5
	DMA_DeInit(USART1_DMA_RX);

	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;
	//DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)DMA_RXbuffer;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RXbuffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	//DMA_InitStructure.DMA_BufferSize = sizeof(DMA_RXbuffer) - 1;
	DMA_InitStructure.DMA_BufferSize = sizeof(RXbuffer) - 1;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

	DMA_Init(USART1_DMA_RX, &DMA_InitStructure);

	USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);

	// Enable DMA Stream Transfer Complete interrupt 
	DMA_ITConfig(USART1_DMA_RX, DMA_IT_TC, ENABLE);
	DMA_Cmd(USART1_DMA_RX, ENABLE);
	*/





	/*
	// clive1 USART1 RX DMA
	// USART1_RX DMA1 Channel 5 (See RM0008)
	DMA_DeInit(DMA1_Channel5);

	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)buffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = sizeof(buffer) - 1;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	//DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;			// iz nekog drugog primjera
	//DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;		// iz nekog drugog primjera
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel5, &DMA_InitStructure);

	USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);

	// Enable DMA Stream Transfer Complete interrupt
	//DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);		// clive1
	DMA_ITConfig(DMA1_Channel5, DMA_IT_TC | DMA_IT_TE, ENABLE);

	DMA_Cmd(DMA1_Channel5, ENABLE);
	*/






	// 9600 8N1 noHW
	//USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_BaudRate = speed;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);				// Enable USART1

	/*
	// NVIC stari
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);		// enable the USART1 receive interrupt
	NVIC_Init(&NVIC_InitStructure);				// the properties are passed to the NVIC_Init function which takes care of the low level stuff
	*/

}


/*
void USART1_IRQHandler(void)
{
	usart1_rx_ready = 0;
	// Loop until the USARTz Receive Data Register is not empty
	if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)
	{
		uint8_t RXchar = (USART_ReceiveData(USART1) );
		if((RXchar > 31) && (RXchar < 127))
		{
			RXbuffer[RXcounter++] = RXchar;
		}
	}
}
*/

void DMA1_Channel5_IRQHandler(void) // USART1_RX
{

	// Test on DMA Transfer Complete interrupt
	if (DMA_GetITStatus(DMA1_IT_TC5))
	{
		// Clear DMA Transfer Complete interrupt pending bit
		DMA_ClearITPendingBit(DMA1_IT_TC5);
		// ...
		//printf("buffer: %s", buffer);
		//led('A', 1, 2);	// toggle PA1
		//for(int i=0; i<10; i++)
		//	buffer[i] = '\0';
	}
}
