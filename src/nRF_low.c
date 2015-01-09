#include "nRF.h"
//#include "nRF_struct.c"

/****************************************************************************/

static inline void nRF1_cs(volatile bool state)
{
	GPIO_WriteBit(NRF1_CSN_PORT, NRF1_CSN_PIN, state);
	delay_us(15);	// 10+
}

static inline void nRF1_ce(volatile bool state)
{
	GPIO_WriteBit(NRF1_CE_PORT, NRF1_CE_PIN, state);
	delay_us(15);	// 10+
}

static inline void nRF_ce_toggle()
{
	GPIO_WriteBit(NRF1_CE_PORT, NRF1_CE_PIN, 1);
	delay_us(15);	// 10+
	GPIO_WriteBit(NRF1_CE_PORT, NRF1_CE_PIN, 0);
	delay_us(15);	// 10+
}

/****************************************************************************/
/****************************************************************************/
void nRF1_io_init()
{
	//RCC_APB2PeriphClockCmd(NRF1_CSN_RCC | NRF1_CE_RCC | NRF1_IRQ_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(NRF1_CSN_RCC | NRF1_CE_RCC, ENABLE);	// RCC_APB2Periph_GPIOB enable

	GPIO_InitTypeDef GPIO_InitStructure;
	// zajednicko za output
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_InitStructure.GPIO_Pin = NRF1_CSN_PIN;
	GPIO_Init(NRF1_CSN_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = NRF1_CE_PIN;
	GPIO_Init(NRF1_CE_PORT, &GPIO_InitStructure);

	// IRQ je input
	/*
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

	GPIO_InitStructure.GPIO_Pin = NRF1_IRQ_PIN;
	GPIO_Init(NRF1_IRQ_PORT, &GPIO_InitStructure);
	*/

	GPIO_WriteBit(NRF1_CSN_PORT, NRF1_CSN_PIN, 1);
}

/****************************************************************************/
/****************************************************************************/
void nRF1_spi_init()
{
	// nRF24L01 CHPA=0, CPOL=0
	// SPI1
		// GPIO zajednicki dio za SPI1 i SPI2
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

	// SPI zajednicki dio za SPI1 i SPI2
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	// separate MOSI and MISO
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	// NRF max = 8
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;	// zasad 1.125 MHz
	//SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;	// SPI2
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);	// SPI1
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);	// SPI2
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 | RCC_APB2Periph_AFIO, ENABLE);	// SPI2	radilo za GLCD
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);	// SPI2	


	GPIO_InitStructure.GPIO_Pin = NRF1_SCK_PIN | NRF1_MISO_PIN | NRF1_MOSI_PIN;
	GPIO_Init(NRF1_SCK_PORT, &GPIO_InitStructure);	// dovoljno je jedan jer su svi SPIx pinovi na istom portu

	SPI_Cmd(SPI1, ENABLE);
	SPI_Init(SPI1, &SPI_InitStructure);
	//SPI_Cmd(SPI2, ENABLE);			// SPI2
	//SPI_Init(SPI2, &SPI_InitStructure);	// SPI2
}

/****************************************************************************/
/****************************************************************************/
//		XXX neki registri vracaju 39b, a ne 8b TODO
/****************************************************************************/
/****************************************************************************/
static uint8_t write_reg(uint8_t reg, uint8_t arg)
{
	printf("write reg: reg: 0x%X, value: %d\n", reg, arg);

	uint8_t status;
	nRF1_cs(0);
	status = spi1_send_receive(reg + CMD_W_REGISTER);
	spi1_send_receive(arg);
	nRF1_cs(1);
	return status;
}

/****************************************************************************/
/****************************************************************************/
static uint8_t read_reg(uint8_t reg)
{
	uint8_t status;
	nRF1_cs(0);
	spi1_send_receive(CMD_R_REGISTER + reg);	// ako citanje REG_STATUS bude zajebavalo ovo zakomentirat samo u tom slucaju
	status = spi1_send_receive(0x00);	// dummy write
	nRF1_cs(1);
	return status;
}

/****************************************************************************/
/****************************************************************************/
static void print_reg(uint8_t reg)
{
	uint8_t status = read_reg(reg);
	printf("reading reg: 0x%X: %d\n", reg, status);	
	for(int i=0; i<8; i++)
	{
		printf("reg bit %d: %d\n", i, ((status >> i) & 1));
	}
	printf("\n");
}
/****************************************************************************/
/****************************************************************************/
void nRF1_main()
{
	nRF1_io_init();
	nRF1_spi_init();
	delay_ms(11);	// 10.3 ms
	// sada je u Power Down modu

	/*
	   RX
	   	CE = 1	to monitor the air and receive packets
		CE = 0	standby
	   TX
	   	CE = 1	always except when the user wants to transmit a packet
	   */

	// power up
	write_reg(REG_CONFIG, (1 << PWR_UP));
	delay_ms(2);	// 1.5ms
	// sad je u Standby-1 modu

	print_reg(REG_CONFIG);
	print_reg(REG_TX_ADDR);
	print_reg(REG_RF_SETUP);
	print_reg(REG_STATUS);

}
