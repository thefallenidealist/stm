#include "spi.h"
#include <stdio.h>

// TODO provjerit
    //while (!((SPI_I2S_GetFlagStatus(spi, SPI_I2S_FLAG_TXE) != RESET) ? 1 : 0));
    //SPI_I2S_SendData(spi, (uint16_t)data);

//#define DISP_SCAN_DATA_CNT     (24 * 3 * 2)                                                   //24 bytes per chip, one chip per colour (RGB), two boards
#define DISP_SCAN_DATA_CNT     (16 * 3)
volatile uint8_t dispData0[DISP_SCAN_DATA_CNT];
volatile uint8_t dispData1[DISP_SCAN_DATA_CNT]; 

uint16_t GLCD_buffer[1]; 

void spi_write_fast(uint8_t data8)
{
	// SPI write optimiziran za brzinu
	// ako ceka na RX i jel SPI dostupan onda mu treba 97-100 ms, ovako 54 ms
	SPI1->DR = data8;
	while (!(SPI1->SR & SPI_I2S_FLAG_TXE));		// wait for TX
}

void spi_write16_fast(uint16_t data16)
{

	// tek za 1-2 ms brzi neko 2x pozivanje spi_write();

	//uint8_t dataL = data16 & 0xFF;
	//uint8_t dataH = data16 >> 8;

	//SPI1->DR = dataH;
	SPI1->DR = data16 >> 8;
	while (!(SPI1->SR & SPI_I2S_FLAG_TXE));		// wait for TX
	//SPI1->DR = dataL;
	SPI1->DR = data16 & 0xFF;
	while (!(SPI1->SR & SPI_I2S_FLAG_TXE));		// wait for TX
}

uint16_t spi_rw16(uint16_t data16)
{
	SPI1->DR = data16;
	while (!(SPI1->SR & SPI_I2S_FLAG_TXE));		// wait for TX
	while (!(SPI1->SR & SPI_I2S_FLAG_RXNE));	// wait for RX
	while (SPI1->SR & SPI_I2S_FLAG_BSY);		// wait until SPI is avaible

	return SPI1->DR;
}

uint8_t spi_rw(uint8_t data8)
{
	SPI1->DR = data8;
	while (!(SPI1->SR & SPI_I2S_FLAG_TXE));		// wait for TX
	while (!(SPI1->SR & SPI_I2S_FLAG_RXNE));	// wait for RX
	while (SPI1->SR & SPI_I2S_FLAG_BSY);		// wait until SPI is avaible

	return SPI1->DR;
}

#define SPI_BUFFER_LENGTH		93408	// sizeof(bmp_data)
extern uint8_t bmp_data[SPI_BUFFER_LENGTH];		// TODO u header

#include "glcd_buffer.c"

void spi_init(void)
{
	// TODO doradit i za ostale portove, druge pinove, prescaler/brzinu, ... 		
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	//DMA_InitTypeDef	 DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);		// DMA
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5;
	//GPIO_InitStructure.GPIO_Pin = SPI1_SCK | SPI1_MOSI;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	// F4
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;		// F4
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	// F4
	//GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;	// F4
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;	// F4
	//GPIO_Init(SPI1_PORT, &GPIO_InitStructure);
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);	// F4

	// the LCD requires the illustrated mode (commonly referred to as CPOL=0,CPHA=0).
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	// separate MOSI and MISO
	//SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;	// TODO isprobat
	SPI_InitStructure.SPI_Mode 	= SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize	= SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL 	= SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA 	= SPI_CPHA_1Edge;
	//SPI_InitStructure.SPI_NSS 	= SPI_NSS_Hard;		// XXX ovo ne radi sa GLCDom na F4
	// nesto sa neta:	XXX ovo odblokira SPI na STM32F4, nekako
	//SPI_InitStructure.SPI_NSS 	= SPI_NSS_Soft | SPI_NSSInternalSoft_Set; // set the NSS management to internal and pull internal NSS high
	SPI_InitStructure.SPI_NSS 	= SPI_NSS_Soft;
	// SPI frequency is APB2 frequency / Prescaler
	//SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;	// GLCD
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;	// nRF
	SPI_InitStructure.SPI_FirstBit 	= SPI_FirstBit_MSB;			// ILI9341 ocekuje MSB first
	//SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);

	/*
	// SPI1 TX 			DMA2	CH3, stream3, stream5
#define SPI_PORT_TX_DMA_CHANNEL            DMA_Channel_3
#define SPI_PORT_TX_DMA_STREAM             DMA2_Stream3
#define SPI_PORT_DMA_TX_IRQn               DMA2_Stream3_IRQn
//#define SPI_PORT_DMA_TX_IRQHandler         DMA2_Stream3_IRQHandler

	DMA_DeInit(SPI_PORT_TX_DMA_STREAM);
	while (DMA_GetCmdStatus (SPI_PORT_TX_DMA_STREAM) != DISABLE);

	DMA_StructInit(&DMA_InitStructure);
	DMA_InitStructure.DMA_PeripheralBaseAddr 	= (uint32_t) (&(SPI1->DR));
	DMA_InitStructure.DMA_Channel 				= SPI_PORT_TX_DMA_CHANNEL;
	DMA_InitStructure.DMA_DIR 					= DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_MemoryInc 			= DMA_MemoryInc_Enable;
	//DMA_InitStructure.DMA_MemoryInc 			= DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_PeripheralInc  		= DMA_PeripheralInc_Disable;	// Enable ne radi
	DMA_InitStructure.DMA_PeripheralDataSize	= DMA_PeripheralDataSize_Byte;	// radi sa __REV(16b boja)
	//DMA_InitStructure.DMA_PeripheralDataSize	= DMA_PeripheralDataSize_HalfWord;	// 
	//DMA_InitStructure.DMA_PeripheralDataSize  = DMA_PeripheralDataSize_Word;	// 
	DMA_InitStructure.DMA_MemoryDataSize  		= DMA_MemoryDataSize_Byte;
	//DMA_InitStructure.DMA_MemoryDataSize		= DMA_MemoryDataSize_HalfWord;	// 
	//DMA_InitStructure.DMA_MemoryDataSize		= DMA_MemoryDataSize_Word;	//
	DMA_InitStructure.DMA_Mode  				= DMA_Mode_Normal;
	//DMA_InitStructure.DMA_Mode  				= DMA_Mode_Circular;
	//DMA_InitStructure.DMA_Priority 				= DMA_Priority_High;
	DMA_InitStructure.DMA_Memory0BaseAddr 		= (uint32_t)&test[1];
	//DMA_InitStructure.DMA_Memory0BaseAddr 		= (uint32_t)bmp_data;
	//DMA_InitStructure.DMA_BufferSize 	 		= sizeof(bmp_data);
	//DMA_InitStructure.DMA_BufferSize 	 		= 65535;
	DMA_InitStructure.DMA_BufferSize 	 		= sizeof(test);
	*/

				/*
				//DMA_InitStructure.DMA_FIFOMode 		  		= DMA_FIFOMode_Disable;	// treba mu inace sjebe orijentaciju, ponekad, samo kad je prescaler = 8
				DMA_InitStructure.DMA_FIFOMode 		  		= DMA_FIFOMode_Enable;
				DMA_InitStructure.DMA_FIFOThreshold   		= DMA_FIFOThreshold_Full;
				DMA_InitStructure.DMA_MemoryBurst 	  		= DMA_MemoryBurst_Single;
				DMA_InitStructure.DMA_PeripheralBurst 		= DMA_PeripheralBurst_Single;
				//DMA_InitStructure.DMA_MemoryBurst 	  		= DMA_MemoryBurst_INC4;
				//DMA_InitStructure.DMA_PeripheralBurst 		= DMA_PeripheralBurst_INC4;
				*/

	/*
	DMA_Init(SPI_PORT_TX_DMA_STREAM, &DMA_InitStructure);
	DMA_ITConfig(SPI_PORT_TX_DMA_STREAM, DMA_IT_TC, ENABLE);

	//while (DMA_GetCmdStatus(SPI_PORT_TX_DMA_STREAM) != ENABLE);	// neki kurac

	NVIC_InitTypeDef NVIC_InitStructure;
	// enable the interrupt in the NVIC
	NVIC_InitStructure.NVIC_IRQChannel = SPI_PORT_DMA_TX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	// Enable dma tx request.
	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
	*/
}

/*
//void glcd_cs_high();
#include "glcd_mid.h"

int dma_counter=0;

void DMA2_Stream3_IRQHandler(void)
{
	// Test if DMA Stream Transfer Complete interrupt
	if (DMA_GetITStatus(SPI_PORT_TX_DMA_STREAM, DMA_IT_TCIF3) == SET) 
	{
		DMA_ClearITPendingBit(SPI_PORT_TX_DMA_STREAM, DMA_IT_TCIF3);
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

		// treba da ne podigne CS prije nego je prijenos gotov
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);

		glcd_cs_high();
		//dma_counter++;
	}
}
*/






/*
void spi2_init(void)
{
	// TODO doradit i za ostale portove, druge pinove, prescaler/brzinu, ... 		
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;	// PC{13,14,15}
	//GPIO_InitStructure.GPIO_Pin = SPI1_SCK | SPI1_MOSI;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	// F4
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;		// F4
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	// F4
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;	// F4
	//GPIO_Init(SPI1_PORT, &GPIO_InitStructure);
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource14, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource13, GPIO_AF_SPI2);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);	// F4

	// the LCD requires the illustrated mode (commonly referred to as CPOL=0,CPHA=0).
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	// separate MOSI and MISO
	SPI_InitStructure.SPI_Mode 	= SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize	= SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL 	= SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA 	= SPI_CPHA_1Edge;
	//SPI_InitStructure.SPI_NSS 	= SPI_NSS_Hard;		// XXX ovo ne radi sa GLCDom na F4
	// nesto sa neta:	XXX ovo odblokira SPI na STM32F4, nekako
	//SPI_InitStructure.SPI_NSS 	= SPI_NSS_Soft | SPI_NSSInternalSoft_Set; // set the NSS management to internal and pull internal NSS high
	SPI_InitStructure.SPI_NSS 	= SPI_NSS_Soft;
	// SPI frequency is APB2 frequency / Prescaler
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;	// GLCD
	SPI_InitStructure.SPI_FirstBit 	= SPI_FirstBit_MSB;			// ILI9341 ocekuje MSB first
	SPI_Init(SPI1, &SPI_InitStructure);

	SPI_Cmd(SPI2, ENABLE);
}
*/
