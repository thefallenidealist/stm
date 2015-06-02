#include "spi.h"
#include <stdio.h>

// TODO provjerit
    //while (!((SPI_I2S_GetFlagStatus(spi, SPI_I2S_FLAG_TXE) != RESET) ? 1 : 0));
    //SPI_I2S_SendData(spi, (uint16_t)data);

// TODO SPI3


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

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

#ifdef STM32F1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
#endif
#ifdef STM32F4
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
#endif

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
#ifdef STM32F1
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);	// pokreni clock za sve sto treba
#endif
#ifdef STM32F4
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

		GPIO_PinAFConfig(SPI1_PORT, SPI1_SCK_AF,  GPIO_AF_SPI1);
		GPIO_PinAFConfig(SPI1_PORT, SPI1_MISO_AF, GPIO_AF_SPI1);
		GPIO_PinAFConfig(SPI1_PORT, SPI1_MOSI_AF, GPIO_AF_SPI1);
#endif

		GPIO_InitStructure.GPIO_Pin = SPI1_SCK | SPI1_MISO | SPI1_MOSI;
		GPIO_Init(SPI1_PORT, &GPIO_InitStructure);

		SPI_Init(SPI1, &SPI_InitStructure);
		SPI_Cmd(SPI1, ENABLE);

		return 0;
	}
	else if (spi_port == 2)
	{
#ifdef STM32F1
		// TODO STM32F1 SPI2
#endif
#ifdef STM32F4
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		// TODO pinove prebacit u header
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

		SPI_Init(SPI2, &SPI_InitStructure);
		SPI_Cmd(SPI2, ENABLE);
#endif


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
