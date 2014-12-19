// GLCD uC specifican dio

// *************************************** sys includes *******************************************
#include <stdio.h>
#include "glcd_low.h"
// *************************************** local includes *****************************************
// *************************************** defines ************************************************
// *************************************** variables **********************************************
// *************************************** function prototypes ************************************

void glcd_io_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// TODO stavit *GPIOB kao varijablu

	// TODO ovo je samo za slucaj da su svi na istom portu
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GLCD_LED_PIN | GLCD_DC_PIN | GLCD_RESET_PIN | GLCD_CS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void glcd_spi_init(void)
{
	// GPIO zajednicki dio za SPI1 i SPI2
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

	// SPI zajednicki dio za SPI1 i SPI2
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

//#ifdef GLCD_SPI1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);	// pokreni clock za sve sto treba

	GPIO_InitStructure.GPIO_Pin = SPI1_SCK | SPI1_MOSI;
	GPIO_Init(SPI1_PORT, &GPIO_InitStructure);

	SPI_Cmd(SPI1, ENABLE);
	SPI_Init(SPI1, &SPI_InitStructure);
	/*
#elif GLCD_SPI2
	// sa O3 razjebe boje, bez optimizacija radi (jebeno sporo)	XXX
	// PB15,14,13
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 | RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStructure.GPIO_Pin = SPI2_SCK | SPI2_MOSI;
	GPIO_Init(SPI2_PORT, &GPIO_InitStructure);

	SPI_Cmd(SPI2, ENABLE);
	SPI_Init(SPI2, &SPI_InitStructure);
#else
  #pragma GCC error "Please define GLCD_SPI1 or SPI2"
#endif
*/
}

uint8_t glcd_spi_send(uint8_t byte)
{
//#ifdef GLCD_SPI1
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, byte);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	//return SPI_I2S_ReceiveData(SPI1);
	//uint16_t returned = SPI_I2S_ReceiveData(SPI1);
	//if(returned != 0)
	//	printf("0x%x ", returned);
	return 0;
	/*
#elif GLCD_SPI2
	// SPI2
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI2, byte);
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	return 0;
#else
  #pragma GCC error "Please define GLCD_SPI1 or SPI2"
#endif
*/

	return 99;
}


uint16_t glcd_spi_send16(uint16_t HalfWord)
{
//#ifdef GLCD_SPI1
	// XXX magija: ovo ce radit samo ako u glcd.h max_x/y i color nisu volatile, jes!
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, HalfWord);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	//return SPI_I2S_ReceiveData(SPI1);
	return 0;

	/*
	// XXX jebena magija, mora bit ovako, a ne preko funkcija jer razjebe ispis
	// stari
	SPI1->DR = HalfWord; // write data to be transmitted to the SPI data register
	while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
	//return SPI1->DR;
	return 0;
	*/
	/*
#elif defined GLCD_SPI2
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI2, HalfWord);
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	//return SPI_I2S_ReceiveData(SPI2);
	return 0;
#else
  #pragma GCC error "Please define GLCD_SPI1 or SPI2"
#endif
*/
	return 99;
}

/*
//inline static void glcd_cs_low(void)
void glcd_cs_low(void)
{
	GPIO_WriteBit(GLCD_CS_PORT, GLCD_CS_PIN, 0);
}

//inline static void glcd_cs_high(void)
void glcd_cs_high(void)
{
	GPIO_WriteBit(GLCD_CS_PORT, GLCD_CS_PIN, 1);
}

//inline static void glcd_dc_low(void)
void glcd_dc_low(void)
{
	GPIO_WriteBit(GLCD_DC_PORT, GLCD_DC_PIN, 0);
}

//inline static void glcd_dc_high(void)
void glcd_dc_high(void)
{
	GPIO_WriteBit(GLCD_DC_PORT, GLCD_DC_PIN, 1);
}
void glcd_led_off(void)
{
	GPIO_WriteBit(GLCD_LED_PORT, GLCD_LED_PIN, 0);
}
void glcd_led_on(void)
{
	GPIO_WriteBit(GLCD_LED_PORT, GLCD_LED_PIN, 1);
}
void glcd_rst_off(void)
{
	GPIO_WriteBit(GLCD_RESET_PORT, GLCD_RESET_PIN, 1);
}
void glcd_rst_on(void)
{
	GPIO_WriteBit(GLCD_RESET_PORT, GLCD_RESET_PIN, 0);
}
*/
