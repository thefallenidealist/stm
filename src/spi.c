#include "spi.h"

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

void spi_init(void)
{
	// TODO doradit i za ostale portove, druge pinove, prescaler/brzinu, ... 		
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5;
	//GPIO_InitStructure.GPIO_Pin = SPI1_SCK | SPI1_MOSI;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	// F4
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;		// F4
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	// F4
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;	// F4
	//GPIO_Init(SPI1_PORT, &GPIO_InitStructure);
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);	// F4

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

	SPI_Cmd(SPI1, ENABLE);
}

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
