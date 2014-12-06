// GLCD uC specifican dio

// *************************************** sys includes *******************************************
#include "stm32f10x_spi.h"
#include "stm32f10x_spi.c"
// *************************************** local includes *****************************************
//#include "glcd.c"
// *************************************** defines ************************************************
#define SPI1_PORT	GPIOA
#define SPI1_SCK	GPIO_Pin_5	// PA5
#define SPI1_MISO	GPIO_Pin_6	// PA6
#define SPI1_MOSI	GPIO_Pin_7	// PA7

#define GLCD_CS_PORT	GPIOB
#define GLCD_CS_PIN	GPIO_Pin_10	// PB10

// *************************************** variables **********************************************

// *************************************** function prototypes ************************************

void spi_init()
{
	// prvo GPIO za CS
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// TODO stavit *GPIOB kao varijablu

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GLCD_CS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);




	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);	// pokreni clock za sve sto treba

	//GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

	GPIO_InitStructure.GPIO_Pin = SPI1_SCK | SPI1_MOSI;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(SPI1_PORT, &GPIO_InitStructure);

	// the LCD requires the illustrated mode (commonly referred to as CPOL=0,CPHA=0).
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;				// NSS pin has to be always high
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	// separate MOSI and MISO
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;				// clock polarity, clock is low when idle
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;				// clock phase, data sampled at first edge		// SPI_CPHA_{1,2}Edge
	//SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;				// XXX ne radi sa ovime
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;				// moze i hard
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;	// SPI frequency is APB2 frequency / Prescaler
					// XXX ne radi kad je vece od 16, kad je manje jednako je spor
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;			// ILI9341 ocekuje MSB first
	//SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Cmd(SPI1, ENABLE);
	SPI_Init(SPI1, &SPI_InitStructure);
}

uint8_t SPI1_send(uint8_t byte)
{
	/*
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, byte);
	// znatno sporiji	3803 ms vs 2228 ms
	//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	//return SPI_I2S_ReceiveData(SPI1);
	return 0;
	*/

	// stari
	SPI1->DR = byte; // write data to be transmitted to the SPI data register
	while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
	//return SPI1->DR;
	return 0;
}

uint16_t SPI1_send16(uint16_t HalfWord)
{
	/*
	   // znatno sporiji
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, HalfWord);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI1);
	*/

	// stari
	SPI1->DR = HalfWord; // write data to be transmitted to the SPI data register
	while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
	return SPI1->DR;
	//return 0;
}

void spi_send(uint8_t byte)
{
	// CS low
	SPI1_send(byte);
	// CS high
}


