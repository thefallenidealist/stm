// created 141019

#include "stm32f10x_spi.h"
#include "stm32f10x_spi.c"

// SPI1 su uvijek na portu A
#define NRF1_SCK_RCC	RCC_APB2Periph_GPIOA
#define NRF1_SCK_PORT	GPIOA
#define NRF1_SCK_PIN	GPIO_Pin_5
#define NRF1_MOSI_RCC	RCC_APB2Periph_GPIOA
#define NRF1_MOSI_PORT	GPIOA
#define NRF1_MOSI_PIN	GPIO_Pin_7
#define NRF1_MISO_RCC	RCC_APB2Periph_GPIOA
#define NRF1_MISO_PORT	GPIOA
#define NRF1_MISO_PIN	GPIO_Pin_6

#define	NRF1_CSN_RCC	RCC_APB2Periph_GPIOB
#define	NRF1_CSN_PORT	GPIOB
#define	NRF1_CSN_PIN	GPIO_Pin_5	// PB5
#define NRF1_CE_RCC	RCC_APB2Periph_GPIOB
#define NRF1_CE_PORT	GPIOB
#define NRF1_CE_PIN	GPIO_Pin_6	// PB6
#define NRF1_IRQ_RCC	RCC_APB2Periph_GPIOB
#define NRF1_IRQ_PORT	GPIOB
#define NRF1_IRQ_PIN	GPIO_Pin_8	// PB8	// active low

static inline void nRF1_cs_low()
{
	GPIO_WriteBit(NRF1_CSN_PORT, NRF1_CSN_PIN, 0);
}

static inline void nRF1_cs_high()
{
	GPIO_WriteBit(NRF1_CSN_PORT, NRF1_CSN_PIN, 1);
}

static inline void nRF1_ce_low()
{
	GPIO_WriteBit(NRF1_CE_PORT, NRF1_CE_PIN, 0);
}

static inline void nRF1_ce_high()
{
	GPIO_WriteBit(NRF1_CE_PORT, NRF1_CE_PIN, 1);
}

static inline void nRF_ce_toggle()
{
	GPIO_WriteBit(NRF1_CE_PORT, NRF1_CE_PIN, 1);
	delay_us(50);	// 10+
	GPIO_WriteBit(NRF1_CE_PORT, NRF1_CE_PIN, 0);
}

void nRF1_io_init()
{
	RCC_APB2PeriphClockCmd(NRF1_CSN_RCC | NRF1_CE_RCC | NRF1_IRQ_RCC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	// zajednicko za output
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_InitStructure.GPIO_Pin = NRF1_CSN_PIN;
	GPIO_Init(NRF1_CSN_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = NRF1_CE_PIN;
	GPIO_Init(NRF1_CE_PORT, &GPIO_InitStructure);

	// IRQ je input
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

	GPIO_InitStructure.GPIO_Pin = NRF1_IRQ_PIN;
	GPIO_Init(NRF1_IRQ_PORT, &GPIO_InitStructure);

	/*
	GPIO_WriteBit(NRF1_CSN_PORT, NRF1_CSN_PIN, 1);
	GPIO_WriteBit(NRF1_CE_PORT, NRF1_CE_PIN, 1);
	GPIO_WriteBit(NRF1_IRQ_PORT, NRF1_IRQ_PIN, 1);
	*/
}

void nRF1_spi_init()
{
	// SPI1
		// GPIO zajednicki dio za SPI1 i SPI2
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

	// SPI zajednicki dio za SPI1 i SPI2
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	// separate MOSI and MISO
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;				// NSS pin has to be always high
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;				// clock phase, data sampled at first edge		// SPI_CPHA_{1,2}Edge
	SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
	//SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;	// SPI frequency is APB2 frequency / Prescaler
	// NRF max = 8
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;	// zasad 1.125 MHz
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;			// ILI9341 ocekuje MSB first
	//SPI_InitStructure.SPI_CRCPolynomial = 7;

	// SPI1 dio sve do kraja
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);	// pokreni clock za sve sto treba

	GPIO_InitStructure.GPIO_Pin = NRF1_SCK_PIN | NRF1_MISO_PIN | NRF1_MOSI_PIN;
	GPIO_Init(NRF1_SCK_PORT, &GPIO_InitStructure);	// dovoljno je jedan jer su svi SPIx pinovi na istom portu

	SPI_Cmd(SPI1, ENABLE);
	SPI_Init(SPI1, &SPI_InitStructure);
}

uint8_t spi1_send_receive(uint8_t data)
{
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, data);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI1);

}

uint8_t read_reg()
{
	uint8_t reg;
	reg = spi1_send_receive(0x01);	// reg 0x00, CONFIG

	printf("reg: %d\n", reg);
	for(int i=0; i<8; i++)
		printf("reg bit %d: %d\n", i, ((reg>>i) & 1));

	return reg;
}

// registri
#define	CONFIG	0x00

// bitovi na kojem su mjestu
#define	MASK_RX_DR	6
#define MASK_TX_DS	5
#define MASK_MAX_RT	4
#define EN_CRC		3
#define CRCO		2
#define PWR_UP		1
#define PRIM_RX		0

#define EN_AA	0x01
#define ENAA_P5	5
#define ENAA_P4	4
#define ENAA_P3	3
#define ENAA_P2	2
#define ENAA_P1	1
#define ENAA_P0	0

#define EN_RXADDR	0x02
#define ERX_P5	5	// enable data pipe 5
#define ERX_P4	4
#define ERX_P3	3
#define ERX_P2	2
#define ERX_P1	1
#define ERX_P0	0

#define SETUP_AW	0x03	// Setup of Address Widths (common for all data pipes)
				// vise bajtova adrese - sporiji prijenos
#define AW1	1		// 00 - illegal		01 - 3 bytes	
#define AW0	0		// 10 - 4 bytes		11 - 5 bytes

#define SETUP_RETR	0x04	// Setup of Automatic Retransmission
#define ARD3	7	// Auto Retransmit Delay
#define ARD2	6	// 0000 – Wait 250µs
#define ARD1	5	// 0001 - 500 us
#define ARD0	4	// 0010 - 750 us		// 1111 4000 us
#define ARC3	3	 
#define ARC2	2	// Auto Retransmit Count
#define ARC1	1	// 0000 retransmit disabled
#define ARC0	0	// 0001 up to 1 retransmit on fail of AA	... 	1111 up to 15

#define RF_CH		0x05	// RF Channel
#define RF_CH6_0	// Sets the frequency channel nRF24L01 operate on

void nRF1_write_reg(uint8_t reg)
{
	// samo u power down modu ili standbyu
	// format: 0b001AAAAA, 	AAAAA = reg, LSB first
	uint8_t data = 0b00100000;
	data |= reg;

	nRF1_cs_low();
	spi1_send_receive(reg);
	nRF1_cs_low();

}

#define NRF_CH	2
#define mirf_PAYLOAD    16

#define TX_POWERUP mirf_config_register(CONFIG, mirf_CONFIG | ( (1<<PWR_UP) | (0<<PRIM_RX) ) )

// komande
#define R_REGISTER    0x00
//#define W_REGISTER    0x20	// 0b00100000
#define W_REGISTER    0b00100000
#define REGISTER_MASK 0x1F	// 0b00011111	samo zadnjih 5 bita
#define R_RX_PAYLOAD  0x61
#define W_TX_PAYLOAD  0xA0
#define FLUSH_TX      0xE1
#define FLUSH_RX      0xE2
#define REUSE_TX_PL   0xE3
#define NOP           0xFF

#define mirf_CH         2
#define mirf_PAYLOAD    16
#define mirf_CONFIG     ( (1<<MASK_RX_DR) | (1<<EN_CRC) | (0<<CRCO) )

// registri
#define RX_PW_P0    0x11
#define RX_PW_P1    0x12
#define RX_PW_P2    0x13
#define RX_PW_P3    0x14
#define RX_PW_P4    0x15
#define RX_PW_P5    0x16

volatile uint8_t PTX;

void mirf_config_register(uint8_t reg, uint8_t data)
{
	nRF1_cs_low();
	spi1_send_receive(W_REGISTER | (REGISTER_MASK & reg));
	spi1_send_receive(data);
	nRF1_cs_high();
}

// Defines for setting the MiRF registers for transmitting or receiving mode
#define TX_POWERUP mirf_config_register(CONFIG, mirf_CONFIG | ( (1<<PWR_UP) | (0<<PRIM_RX) ) )
#define RX_POWERUP mirf_config_register(CONFIG, mirf_CONFIG | ( (1<<PWR_UP) | (1<<PRIM_RX) ) )

//void nrf_config()
void mirf_config()
{
	// Set RF channel
	mirf_config_register(RF_CH,mirf_CH);

	// Set length of incoming payload 
	mirf_config_register(RX_PW_P0, mirf_PAYLOAD);

	// Start receiver 
	PTX = 0;        // Start in receiving mode
	RX_POWERUP;     // Power up in receiving mode
	nRF1_ce_high();	// listening for pkgs
}

void spi_transmit_sync(uint8_t *data, uint8_t length)
{
	for(int i=0; i<length; i++)
		//spi1_send_receive(*data);
		spi1_send_receive(data[i]);

}

void mirf_send(uint8_t * value, uint8_t len) 
// Sends a data package to the default address. Be sure to send the correct
// amount of bytes as configured as payload on the receiver.
{
	while (PTX) {}                  // Wait until last paket is send

	//mirf_CE_lo;
	nRF1_ce_low();

	PTX = 1;                        // Set to transmitter mode
	TX_POWERUP;                     // Power up

	nRF1_cs_low();
	spi1_send_receive(FLUSH_TX);	// flush TX FIFO
	nRF1_cs_high();

	nRF1_cs_low();
	spi1_send_receive(W_TX_PAYLOAD);	// cmd write payload
	//spi_transmit_sync(value,len);   // Write payload	XXX

	nRF1_cs_high();

	nRF1_ce_high();	// start transmission
}

uint8_t nRF_readRegister(uint8_t reg)
{
	nRF1_cs_low();
	spi1_send_receive(R_REGISTER | (REGISTER_MASK & reg));
	uint8_t result = spi1_send_receive(0xFF);
	nRF1_cs_high();

	return result;
}

//uint8_t nRF_writeRegister(uint8_t reg, uint8_t value)
void nRF_writeRegister(uint8_t reg, uint8_t value)
{
	// procitaj stari
	uint8_t old = nRF_readRegister(reg);
	delay_ms(2);

	nRF1_cs_low();
	//status = spi1_send_receive(W_REGISTER | (REGISTER_MASK & reg));
	spi1_send_receive(W_REGISTER | (REGISTER_MASK & reg));
	spi1_send_receive(value);
	//spi1_send_receive(old + value);	// zapisi stari i novi promijenjeni bit
	nRF1_cs_high();

	//printf("stari reg: %d\n", old);
	//printf("novi reg: %d\n", old + value);
	//printf("novi reg: %d\n", old | value);

	//printf("wReg status: %d\n", status);
	//return status;
}

void bit_print(uint8_t arg)
{
	/*
	for(int i=0; i<8; i++)
		printf("%d. %d\n", i, (arg >> i) & 1);
	*/
	
	for(int i=7; i>=0; i--)
		printf("%d. %d\n", i, (arg >> i) & 1);

}

#define RF_SETUP	0x06

void print_reg(uint8_t reg)
{
	uint8_t status;
	status = nRF_readRegister(CONFIG);
	printf("CONFIG: %d\n", status);
	bit_print(status);
}

void nRF1_main()
{
	nRF1_io_init();
	nRF1_spi_init();

	//nRF1_cs_high();	// neka se nadje

	delay_ms(11);	// 10.3 ms
	// sada je u Power Down modu

	printf("friski:\n");
	print_reg(CONFIG);

	// e sad pravi init

	//PWR_UP=1	bit1, CONFIG
	nRF_writeRegister(CONFIG, 1 << PWR_UP);
	delay_ms(2);	// 1.5 ms
	// sad je u Standby-1 modu

	printf("PWR_UP = 1\n");
	print_reg(CONFIG);

	//nRF_writeRegister(CONFIG, 

	/*
	// TX FIFO not empty
	// PRIM_RX = 0
	nRF_writeRegister(CONFIG, (1 << PRIM_RX));
	delay_ms(2);
	// CE =1 for more than 10us
	nRF1_ce_high();
	delay_ms(1);
	
	// TX settling 130 us
	delay_ms(1);
	// u TX modu je

	// CE = 1, TX FIFO not empty
	nRF1_ce_high();


	// kad je gotovo sa slanjem:
	// CE = 0
	nRF1_ce_low();


	printf("PWR_UP=1, PRIM_RX=0\n");
	print_reg(CONFIG);

	nRF_writeRegister(RF_SETUP, 0b00001110);
	delay_ms(2);

	*/


	/*
	status = nRF_readRegister(RF_CH);
	printf("RF_CH: %d\n", status);
	bit_print(status);


	status = nRF_readRegister(RF_SETUP);
	printf("RF_SETUP: %d\n", status);
	bit_print(status);
	*/





	/*
	// moja implementacija drivera nekog sa neta
	nRF1_ce_low();
	nRF1_cs_high();

	delay_ms(5);	// TODO
	nRF_writeRegister(SETUP_RETR, 0b0100 << 4, 0b1111 << 0);
	//0100 << ARD	-> wait X us
	// 1111 << ARC	-> 15 retransmits of failed AA
	*/

	/*
	// set power level TODO		max = 3
	uint8_t old_status = nRF_readRegister(RF_STATUS);
	...
	*/

	// set datarate




	/*
	mirf_config();

	 // Test communication
	mirf_send(buffer,buffersize);
	while (!mirf_data_ready());
	mirf_get_data(buffer);
	*/

	printf("Dosao do kraja RF main\n");
}
