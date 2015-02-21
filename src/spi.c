#include "spi.h"
#include <stdio.h>

// TODO provjerit
    //while (!((SPI_I2S_GetFlagStatus(spi, SPI_I2S_FLAG_TXE) != RESET) ? 1 : 0));
    //SPI_I2S_SendData(spi, (uint16_t)data);

// TODO SPI3

//#define DISP_SCAN_DATA_CNT     (24 * 3 * 2)                                                   //24 bytes per chip, one chip per colour (RGB), two boards
#define DISP_SCAN_DATA_CNT     (16 * 3)
volatile uint8_t dispData0[DISP_SCAN_DATA_CNT];
volatile uint8_t dispData1[DISP_SCAN_DATA_CNT]; 

uint16_t GLCD_buffer[1]; 


/*************************************************************************************************
				spi_write_fast()
*************************************************************************************************/
void spi_write_fast(uint8_t spi_port, uint8_t data8)
{
	// SPI write optimiziran za brzinu
	// ako ceka na RX i jel SPI dostupan onda mu treba 97-100 ms, ovako 54 ms
	if (spi_port == 1)
	{
		SPI1->DR = data8;
		while (!(SPI1->SR & SPI_I2S_FLAG_TXE));		// wait for TX
	}
	else if (spi_port == 2)
	{
		SPI2->DR = data8;
		while (!(SPI2->SR & SPI_I2S_FLAG_TXE));		// wait for TX
	}
	else
	{
		ERROR("Wrong SPI port\n");
	}
}

/*************************************************************************************************
				spi_write16_fast()
*************************************************************************************************/
void spi_write16_fast(uint8_t spi_port, uint16_t data16)
{
	// tek za 1-2 ms brzi neko 2x pozivanje spi_write();

	if (spi_port == 1)
	{
		SPI1->DR = data16 >> 8;
		while (!(SPI1->SR & SPI_I2S_FLAG_TXE));		// wait for TX
		SPI1->DR = data16 & 0xFF;
		while (!(SPI1->SR & SPI_I2S_FLAG_TXE));		// wait for TX
	}
	else if (spi_port == 2)
	{
		SPI2->DR = data16 >> 8;
		while (!(SPI2->SR & SPI_I2S_FLAG_TXE));		// wait for TX
		SPI2->DR = data16 & 0xFF;
		while (!(SPI2->SR & SPI_I2S_FLAG_TXE));		// wait for TX
	}
	else
	{
		ERROR("Wrong SPI port\n");
	}
}

/*************************************************************************************************
				spi_rw16()
*************************************************************************************************/
uint16_t spi_rw16(uint8_t spi_port, uint16_t data16)
{
	if (spi_port == 1)
	{
		SPI1->DR = data16;
		while (!(SPI1->SR & SPI_I2S_FLAG_TXE));		// wait for TX
		while (!(SPI1->SR & SPI_I2S_FLAG_RXNE));	// wait for RX
		while (SPI1->SR & SPI_I2S_FLAG_BSY);		// wait until SPI is avaible

		return SPI1->DR;
	}
	else if (spi_port == 2)
	{
		SPI2->DR = data16;
		while (!(SPI2->SR & SPI_I2S_FLAG_TXE));		// wait for TX
		while (!(SPI2->SR & SPI_I2S_FLAG_RXNE));	// wait for RX
		while (SPI2->SR & SPI_I2S_FLAG_BSY);		// wait until SPI is avaible

		return SPI2->DR;
	}
	else
	{
		ERROR("Wrong SPI port\n");
		return 0xFFFF;
	};
}

/*************************************************************************************************
				spi_rw()
*************************************************************************************************/
uint8_t spi_rw(uint8_t spi_port, uint8_t data8)
{
	if (spi_port == 1)
	{
		SPI1->DR = data8;
		while (!(SPI1->SR & SPI_I2S_FLAG_TXE));		// wait for TX
		while (!(SPI1->SR & SPI_I2S_FLAG_RXNE));	// wait for RX
		while (SPI1->SR & SPI_I2S_FLAG_BSY);		// wait until SPI is avaible

		return SPI1->DR;
	}
	else if (spi_port == 2)
	{
		SPI2->DR = data8;
		while (!(SPI2->SR & SPI_I2S_FLAG_TXE));		// wait for TX
		while (!(SPI2->SR & SPI_I2S_FLAG_RXNE));	// wait for RX
		while (SPI2->SR & SPI_I2S_FLAG_BSY);		// wait until SPI is avaible

		return SPI2->DR;
	}
	else
	{
		ERROR("Wrong SPI port\n");
		return 0xFF;
	};
}

/*************************************************************************************************
*************************************************************************************************/
#define SPI_BUFFER_LENGTH		93408	// sizeof(bmp_data)
extern uint8_t bmp_data[SPI_BUFFER_LENGTH];		// TODO u header

//#include "glcd_buffer.c"

	/*
//void spi_init(void)
{
	// TODO doradit i za ostale portove, druge pinove, prescaler/brzinu, ... 		
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	//DMA_InitTypeDef	 DMA_InitStructure;
//	SPI_Cmd(SPI1, ENABLE);

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
}
	*/

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

int8_t spi_init(uint8_t spi_port, uint16_t spi_prescaler)
{
	// obicni SPI, doradit za DMA TODO
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	switch (spi_prescaler)
	{
		// SPI frequency is APB2 frequency / Prescaler
		case 2:
			SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
			break;
		case 4:
			SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
			break;
		case 8:
			SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
			break;
		case 16:
			SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
			break;
		case 32:
			SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
			break;
		case 64:
			SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
			break;
		case 128:
			SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
			break;
		case 256:
			SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
			break;
	}

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	// F4
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;		// F4
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	// F4
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;	// F4

	// INFO pretpostavka da se CPOL i CPHA nece mijenjat
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode		= SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize	= SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL 		= SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA 		= SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS 		= SPI_NSS_Soft;	// mora bit inace GLCD nece radit
	SPI_InitStructure.SPI_FirstBit 	= SPI_FirstBit_MSB;			// ILI9341 ocekuje MSB first
	//SPI_InitStructure.SPI_CRCPolynomial = 7;

	if (spi_port == 1)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);	// F4

		SPI_Init(SPI1, &SPI_InitStructure);
		SPI_Cmd(SPI1, ENABLE);

		return 0;
	}
	else if (spi_port == 2)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);	// F4

		SPI_Init(SPI2, &SPI_InitStructure);
		SPI_Cmd(SPI2, ENABLE);

		return 0;
	}
	else if (spi_port == 3)
	{
		// TODO
		ERROR("SPI3 is not implemented\n");
		return -1;
	}
	else
	{
		printf("%s(): wrong SPI: %d\n", __func__, spi_port);
		return -1;
	}
}
