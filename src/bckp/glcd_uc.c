// GLCD uC specifican dio

// *************************************** sys includes *******************************************
#include "stm32f10x_spi.h"
#include "stm32f10x_spi.c"
// *************************************** local includes *****************************************
//#include "glcd.c"
// *************************************** defines ************************************************
#ifdef GLCD_SPI1
  #define SPI1_PORT	GPIOA
  #define SPI1_SCK	GPIO_Pin_5	// PA5
  #define SPI1_MOSI	GPIO_Pin_7	// PA7
#endif

#ifdef GLCD_SPI2
  // GLCD SPI2
  #define SPI2_PORT	GPIOB
  #define SPI2_SCK	GPIO_Pin_13
  #define SPI2_MOSI	GPIO_Pin_15
#endif

#define GLCD_LED_PORT	GPIOB
#define GLCD_LED_PIN	GPIO_Pin_0	// PB0
#define GLCD_DC_PORT	GPIOB
#define GLCD_DC_PIN	GPIO_Pin_1	// PB1
#define GLCD_RESET_PORT GPIOB
#define GLCD_RESET_PIN	GPIO_Pin_2	// PB2
#define GLCD_CS_PORT	GPIOB
#define GLCD_CS_PIN	GPIO_Pin_10	// PB10
// *************************************** variables **********************************************

// *************************************** function prototypes ************************************

void glcd_io_init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// TODO stavit *GPIOB kao varijablu

	// TODO ovo je samo za slucaj da su svi na istom portu
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GLCD_LED_PIN | GLCD_DC_PIN | GLCD_RESET_PIN | GLCD_CS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void glcd_spi_init()
{
#ifdef GLCD_SPI1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);	// pokreni clock za sve sto treba
#endif
#ifdef GLCD_SPI2
	// SPI2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
#endif

	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

#ifdef GLCD_SPI1
	// SPI1
	GPIO_InitStructure.GPIO_Pin = SPI1_SCK | SPI1_MOSI;
#endif
#ifdef GLCD_SPI2
	// SPI2
	GPIO_InitStructure.GPIO_Pin = SPI2_SCK | SPI2_MOSI;
#endif
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

#ifdef GLCD_SPI1
	GPIO_Init(SPI1_PORT, &GPIO_InitStructure);
#endif
#ifdef GLCD_SPI2
	GPIO_Init(SPI2_PORT, &GPIO_InitStructure);
#endif

	// the LCD requires the illustrated mode (commonly referred to as CPOL=0,CPHA=0).
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	// separate MOSI and MISO
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;				// NSS pin has to be always high
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	//SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;				// clock polarity, clock is low when idle
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;				// clock phase, data sampled at first edge		// SPI_CPHA_{1,2}Edge
	SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;	// SPI frequency is APB2 frequency / Prescaler
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;			// ILI9341 ocekuje MSB first
	//SPI_InitStructure.SPI_CRCPolynomial = 7;


#ifdef GLCD_SPI1
	SPI_Cmd(SPI1, ENABLE);
	SPI_Init(SPI1, &SPI_InitStructure);
#endif
#ifdef GLCD_SPI2
	SPI_Cmd(SPI2, ENABLE);
	SPI_Init(SPI2, &SPI_InitStructure);
#endif
}

#define SPI_PORT_DR_ADDRESS SPI_PORT->DR 
#define SPI_PORT_DMA DMA1 
#define SPI_PORT_DMAx_CLK RCC_AHB1Periph_DMA1 
#define SPI_PORT_TX_DMA_CHANNEL DMA_Channel_0 
#define SPI_PORT_TX_DMA_STREAM DMA1_Stream4 
#define SPI_PORT_TX_DMA_FLAG_FEIF DMA_FLAG_FEIF4 
#define SPI_PORT_TX_DMA_FLAG_DMEIF DMA_FLAG_DMEIF4 
#define SPI_PORT_TX_DMA_FLAG_TEIF DMA_FLAG_TEIF4 
#define SPI_PORT_TX_DMA_FLAG_HTIF DMA_FLAG_HTIF4 
#define SPI_PORT_TX_DMA_FLAG_TCIF DMA_FLAG_TCIF4 
#define SPI_PORT_DMA_TX_IRQn DMA1_Stream4_IRQn 
#define SPI_PORT_DMA_TX_IRQHandler DMA1_Stream4_IRQHandler

#define BufferSize         32
#define CRCPolynomial      7
uint8_t SPI_MASTER_Buffer_Rx[BufferSize], SPI_SLAVE_Buffer_Rx[BufferSize];
uint8_t SPI_MASTER_Buffer_Tx[BufferSize] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
                                            0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,
                                            0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,
                                            0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20};



uint16_t DACData[1];
void glcd_dma_init()
{
	/*
	DMA_InitTypeDef DMA_InitStructure; // Set up the DMA // first enable the clock 
	//RCC_AHB1PeriphClockCmd(SPI_PORT_DMAx_CLK, ENABLE); // start with a blank DMA configuration just to be sure 
	RCC_AHB1PeriphClockCmd(SPI_PORT_DMAx_CLK, ENABLE); // start with a blank DMA configuration just to be sure 
	DMA_DeInit(SPI_PORT_TX_DMA_STREAM); // Configure DMA controller to manage TX DMA requests // first make sure we are using the default values 
	DMA_StructInit(&DMA_InitStructure); // these are the only parameters that change from the defaults 
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (SPI_PORT->DR); 
	DMA_InitStructure.DMA_Channel = SPI_PORT_TX_DMA_CHANNEL; 
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral; 
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; // It is not possible to call DMA_Init without values for the source * address and non-zero size even though a transfer is not done here. * These are checked only when the assert macro are active though.
	DMA_InitStructure.DMA_Memory0BaseAddr = 0; 
	DMA_InitStructure.DMA_BufferSize = 1; 
	DMA_Init(SPI_PORT_TX_DMA_STREAM, &DMA_InitStructure); // Enable the DMA transfer complete interrupt 
	DMA_ITConfig(SPI_PORT_TX_DMA_STREAM, DMA_IT_TC, ENABLE);
	*/


	//--Enable DMA1 clock--
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

//--Enable ADC1 and GPIOC--
RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);

	DMA_InitTypeDef DMA_InitStructure; 

	// sluzbeni primjer
	//DMA_DeInit(SPI_MASTER_Rx_DMA_Channel);
	DMA_DeInit(DMA1_Channel3);
	//DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SPI_MASTER_DR_Base;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (SPI1->DR);
	//DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SPI_MASTER_Buffer_Rx;
	DMA_InitStructure.DMA_MemoryBaseAddr  = (uint32_t)&DACData;       //Set the memory location
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	//DMA_InitStructure.DMA_DIR  = DMA_DIR_MemoryToPeripheral;           //
	//DMA_InitStructure.DMA_BufferSize = BufferSize;
	DMA_InitStructure.DMA_BufferSize  = 1;            //Define the number of bytes to send
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	//DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;				// ST
	DMA_InitStructure.DMA_MemoryInc  = DMA_MemoryInc_Disable;
	//DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;		// ST
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	//DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			// ST
	DMA_InitStructure.DMA_MemoryDataSize  = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;						// ST
	//DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	//DMA_InitStructure.DMA_FIFOMode  = DMA_FIFOMode_Disable;  //Operate in 'direct mode'		// izgleda da nema na mojem
	//DMA_InitStructure.DMA_MemoryBurst =DMA_MemoryBurst_Single;				// nema ST	izgleda da nema na mojem
	    //DMA_InitStructure.DMA_PeripheralBurst =DMA_PeripheralBurst_Single;		// izgleda da nema na mojem
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	//DMA_Init(SPI_MASTER_Rx_DMA_Channel, &DMA_InitStructure);
	DMA_Init(DMA1_Channel3, &DMA_InitStructure);

	//Enable the transfer complete interrupt for DMA2 Stream5
	DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);

	//DMA_Cmd(DMA1_Channel1, ENABLE); //Enable the DMA1 - Channel1			// nema ST

	/*
	// sluzbeni primjer, TX
	//DMA_DeInit(SPI_MASTER_Tx_DMA_Channel);  
	DMA_DeInit(DMA1_Channel3);
	//DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SPI_MASTER_DR_Base;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (SPI1->DR);
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SPI_MASTER_Buffer_Tx;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
	//DMA_Init(SPI_MASTER_Tx_DMA_Channel, &DMA_InitStructure);
	DMA_Init(DMA1_Channel3, &DMA_InitStructure);
	*/

	/* Enable SPI_MASTER DMA Tx request */
	//SPI_I2S_DMACmd(SPI_MASTER, SPI_I2S_DMAReq_Tx, ENABLE);
	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);

	/* Enable SPI_MASTER CRC calculation */
	//SPI_CalculateCRC(SPI1, ENABLE);

	// Enable SPI
	SPI_Cmd(SPI1, ENABLE);


}

uint8_t glcd_spi_send(uint8_t byte)
{
#ifdef GLCD_SPI1
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, byte);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	//return SPI_I2S_ReceiveData(SPI1);
	return 0;
#endif

#ifdef GLCD_SPI2
	// SPI2
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI2, byte);
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	return 0;
#endif
}


//uint16_t SPI1_send16(uint16_t HalfWord)
uint16_t glcd_spi_send16(uint16_t HalfWord)
{
#ifdef GLCD_SPI1
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, HalfWord);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	//return SPI_I2S_ReceiveData(SPI1);
	return 0;

	/*
	// stari
	SPI1->DR = HalfWord; // write data to be transmitted to the SPI data register
	while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
	//return SPI1->DR;
	return 0;
	*/
#endif

#ifdef GLCD_SPI2
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, HalfWord);
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI2);
#endif
}

void DMA1_Channel3_IRQHandler(void)
{  
	/* Test on DMA Channel1 Transfer Complete interrupt */
  if(DMA_GetITStatus(DMA1_IT_TC3))		//DMA1_IT_TC1: channel 1 transmission complete interrupt
  {
    /* Get Current Data Counter value after complete transfer */
   //CurrDataCounter= DMA_GetCurrDataCounter(DMA1_Channel1); 	//The number of data to return the current DMA channel 1 remaining transmission
    /* Clear DMA Channel1 Half Transfer, Transfer Complete and Global interrupt pending bits */
    DMA_ClearITPendingBit(DMA1_IT_GL3);		//Clear interrupt 1 global interrupt
  }
	
}
