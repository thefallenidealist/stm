#include "nRF_low.h"

/****************************************************************************/
//static inline void nRF1_cs(volatile bool state)
static inline void cs(volatile bool state)
{
	//GPIO_WriteBit(NRF1_CSN_PORT, NRF1_CSN_PIN, state);
	delay_us(15);	// 10+
}

//static inline void nRF1_ce(volatile bool state)
static inline void ce(volatile bool state)
{
	//GPIO_WriteBit(NRF1_CE_PORT, NRF1_CE_PIN, state);
	delay_us(15);	// 10+
}

//static inline void nRF_ce_toggle()
static inline void ce_toggle()
{
	//GPIO_WriteBit(NRF1_CE_PORT, NRF1_CE_PIN, 1);
	delay_us(15);	// 10+
	//GPIO_WriteBit(NRF1_CE_PORT, NRF1_CE_PIN, 0);
	delay_us(15);	// 10+
}

/****************************************************************************/
/****************************************************************************/
static uint8_t write_reg(uint8_t reg, uint8_t arg)
//static uint8_t write_reg(nRF_t nRF, uint8_t reg, uint8_t arg)
{
	printf("write reg: reg: 0x%X, value: %d\n", reg, arg);

	uint8_t status;
	cs(0);
	//cs(nRF, 0);
	status = spi1_send_receive(reg + CMD_W_REGISTER);
	spi1_send_receive(arg);
	cs(1);
	return status;
}

/****************************************************************************/
/****************************************************************************/
static uint8_t read_reg(uint8_t reg)
{
	uint8_t status;
	cs(0);
	spi1_send_receive(CMD_R_REGISTER + reg);	// ako citanje REG_STATUS bude zajebavalo ovo zakomentirat samo u tom slucaju
	status = spi1_send_receive(0x00);	// dummy write
	cs(1);
	return status;
}

/****************************************************************************/
/****************************************************************************/
static void print_reg(uint8_t reg)
{
	uint8_t status = read_reg(reg);
	printf("reading reg: 0x%X: %d\n", reg, status);	
	for (int i=0; i<8; i++)
	{
		printf("reg bit %d: %d\n", i, ((status >> i) & 1));
	}
	printf("\n");
}
/****************************************************************************/
/****************************************************************************/
void nRF1_main()
{
	//nRF1_io_init();
	//nRF1_spi_init();






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
