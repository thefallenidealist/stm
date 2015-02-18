#include "nRF_low.h"

static void cs_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	//RCC_APB2PeriphClockCmd(NRF1_CSN_RCC | NRF1_CE_RCC | NRF1_IRQ_RCC, ENABLE);
	RCC_AHB1PeriphClockCmd(NRF1_CSN_RCC, ENABLE);	// F4
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	// F4

	// zajednicko za output
	//GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;	// F1
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;	// F4
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;	
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStruct.GPIO_Pin = NRF1_CSN_PIN;
	GPIO_Init(NRF1_CSN_PORT, &GPIO_InitStruct);
}

static void ce_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	// F4
	RCC_AHB1PeriphClockCmd(NRF1_CE_RCC, ENABLE);	// F4

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;	// F4
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;	

	GPIO_InitStruct.GPIO_Pin = NRF1_CE_PIN;
	GPIO_Init(NRF1_CE_PORT, &GPIO_InitStruct);
}

/*
static void irq_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd(NRF1_IRQ_RCC, ENABLE);	// F4

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;	

	GPIO_InitStruct.GPIO_Pin = NRF1_IRQ_PIN;
	GPIO_Init(NRF1_IRQ_PORT, &GPIO_InitStruct);
}
*/

void nRF1_io_init()
{
	DEBUG_START;

	ce_init();
	cs_init();
	//irq_init();


	/*
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(NRF1_CSN_RCC | NRF1_CE_RCC | NRF1_IRQ_RCC, ENABLE);

	// zajednicko za output
	//GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;	// F1
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;	// F4
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;	
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStruct.GPIO_Pin = NRF1_CSN_PIN;
	GPIO_Init(NRF1_CSN_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = NRF1_CE_PIN;
	GPIO_Init(NRF1_CE_PORT, &GPIO_InitStruct);

	// input
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;	

	GPIO_InitStruct.GPIO_Pin = NRF1_IRQ_PIN;
	GPIO_Init(NRF1_IRQ_PORT, &GPIO_InitStruct);
	*/

	GPIO_WriteBit(NRF1_CSN_PORT, NRF1_CSN_PIN, 1);
	GPIO_WriteBit(NRF1_CE_PORT, NRF1_CE_PIN, 1);
	//GPIO_WriteBit(NRF1_IRQ_PORT, NRF1_IRQ_PIN, 1);

	DEBUG_END;
}

void nRF1_spi_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	// F4
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;		// F4
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	// F4
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;	// F4
	//GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;	// F4
	//GPIO_Init(SPI1_PORT, &GPIO_InitStructure);
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);	// F4

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	// separate MOSI and MISO
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;				// NSS pin has to be always high
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL 	= SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;				// clock phase, data sampled at first edge		// SPI_CPHA_{1,2}Edge
	SPI_InitStructure.SPI_NSS 	= SPI_NSS_Soft;
	//SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
	// NRF max = 8
	// F4: SPI = 84 MHz / prescaler
	// 2 = 24	4 = 12		8 = 10
	// 16 = 5	32 = 2.6	64 = 1.3
	// nRF datasheet kaze da je SPI max SCK: 5-8, ovisi o kapacitivnosti
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;	// F4 nRF: 32, 64 
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;			// ILI9341 ocekuje MSB first
	//SPI_InitStructure.SPI_CRCPolynomial = 7;

	SPI_Cmd(SPI1, ENABLE);
	SPI_Init(SPI1, &SPI_InitStructure);
}

/****************************************************************************/
//static inline void nRF1_cs(volatile bool state)
static inline void cs(volatile bool state)
{
	GPIO_WriteBit(NRF1_CSN_PORT, NRF1_CSN_PIN, state);
	delay_us(15);	// 10+
}

/*
//static inline void nRF1_ce(volatile bool state)
static inline void ce(volatile bool state)
{
	GPIO_WriteBit(NRF1_CE_PORT, NRF1_CE_PIN, state);
	delay_us(15);	// 10+
}

//static inline void nRF_ce_toggle()
static inline void ce_toggle()
{
	GPIO_WriteBit(NRF1_CE_PORT, NRF1_CE_PIN, 1);
	delay_us(15);	// 10+
	GPIO_WriteBit(NRF1_CE_PORT, NRF1_CE_PIN, 0);
	delay_us(15);	// 10+
}
*/

/****************************************************************************/
/****************************************************************************/
static uint8_t write_reg(uint8_t reg, uint8_t arg)
//static uint8_t write_reg(nRF_t nRF, uint8_t reg, uint8_t arg)
{
	DEBUG_START;
	printf("write reg: reg: 0x%X, value: %d\n", reg, arg);

	uint8_t status;
	cs(0);
	//cs(nRF, 0);
	//status = spi_rw(reg + CMD_W_REGISTER);
	status = spi_rw(reg + CMD_W_REGISTER);
	spi_rw(arg);
	//spi_write_fast(arg);
	delay_ms(1);	// bezveze
	cs(1);

	DEBUG_END;
	return status;
}

/****************************************************************************/
/****************************************************************************/
static uint8_t read_reg(uint8_t reg)
{
	DEBUG_START;
	uint8_t status;
	cs(0);
	spi_rw(CMD_R_REGISTER + reg);	// ako citanje REG_STATUS bude zajebavalo ovo zakomentirat samo u tom slucaju
	status = spi_rw(0x00);	// dummy write
	cs(1);

	DEBUG_END;
	return status;
}

/****************************************************************************/
/****************************************************************************/
static void print_reg(uint8_t reg)
{
	DEBUG_START;

	uint8_t status = read_reg(reg);
	printf("reading reg: 0x%X: %d\n", reg, status);	
	for (int i=0; i<8; i++)
	{
		printf("reg bit %d: %d\n", i, ((status >> i) & 1));
	}

	DEBUG_END;
	printf("\n");
}
/****************************************************************************/
/****************************************************************************/
void nRF1_main()
{
	DEBUG_START;
	nRF1_io_init();
	//spi_init();
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

	DEBUG_END;
}
