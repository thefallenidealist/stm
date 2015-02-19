#include "nRF_novi.h"
//#include "nRF_reg.c" 		// TODO malo bolje, ne includeat .c
#include "nRF_reg.h"

// TODO
// low: GPIO i SPI
// mid: operacije sa registrima
// high: set i get funkcije

/*************************************************************************************************
				nRF_main()
*************************************************************************************************/
void nRF_main()
{
	DEBUG_START;

	// TODO napravit da je uvijek u RX modu, samo kad salje da se presalta u TX
	nRF_hw_t bezicni;

	bezicni.spi_port = 1;
	//bezicni.spi_speed_MHz = 
	bezicni.spi_prescaler = 32;
	bezicni.cs = "PB5";
	bezicni.ce = "PB4";
	//bezicni.irq = "PB3";	// NC

	if (nRF_hw_init(&bezicni) != 0)
	{
		ERROR("module not initialized\n");
		// return -1;
	}
	delay_ms(11);	// 10.3 ms

	//printf("nRF je odradio hardverski init\n");

//#define	REG_CONFIG	0x00
//#define PWR_UP		1	// 1: POWER UP, 0:POWER DOWN

	// power up
	write_reg(&bezicni, REG_CONFIG, (1 << PWR_UP) | (0 << PRIM_RX));

	delay_ms(2);	// 1.5ms
	// sad je u Standby-1 modu

	printf("status: ");
	dec2bin8(get_status(&bezicni));
	printf("\n");


	// TODO e, sta sad?

	// retransmit count = 15
	nRF_set_retransmit_count(&bezicni, 15);

	// 1ms Retransmit Delay
	nRF_set_retransmit_delay(&bezicni, DELAY_1ms);


	// 5 bytes address width
	nRF_set_address_width(&bezicni, 5);
	// 0000010 default
	write_reg(&bezicni, REG_RF_CH, 0b0000010);	// default ch

	// CRC enable, 1 byte length
	// set data rate to 1Mbps
	nRF_set_data_rate(&bezicni, datarate_1Mbps);	// reg 0x06

	// max payload length = 32
	// set mode to RX, napravi to automatski
	// set channel
	// set 


	nRF_set_output_power(&bezicni, power_0dBm);


	printf("RX data ready: %d\n", nRF_is_RX_data_ready(&bezicni));
	printf("TX data sent: %d\n", nRF_is_TX_data_sent(&bezicni));

	nRF_data_pipe_avaible(&bezicni);

	print_reg(&bezicni, 0x00);
	print_reg(&bezicni, 0x01);
	print_reg(&bezicni, 0x02);
	print_reg(&bezicni, 0x03);
	print_reg(&bezicni, 0x04);
	print_reg(&bezicni, 0x05);
	print_reg(&bezicni, 0x06);
	print_reg(&bezicni, 0x07);

	DEBUG_END;
}

/*************************************************************************************************
				nRF_set_address_width()
*************************************************************************************************/
void nRF_set_address_width(nRF_hw_t *nRF0, uint8_t address)		// reg 0x03
{
	if ( (address < 3) || (address > 5) )
	{
		ERROR("Wrong address width\n");
	}
	else
	{
		// 11 = 5, 10 = 4, 01 = 3 bytes width address
		uint8_t new_address = address - 2;

		bool b1, b0;
		b0 = new_address & 1;
		b1 = (new_address >> 1) & 1;

		//printf("\t\t\t\t%s(): addr: %d, b1: %d, b0: %d\n", __func__, address, b1, b0);

		write_reg(nRF0, REG_SETUP_AW, (b1 << AW1) | (b0 << AW0));	// 5 bytes address width
	}
}
// INFO provjereno

/*************************************************************************************************
				nRF_set_retransmit_delay()
*************************************************************************************************/
void nRF_set_retransmit_delay(nRF_hw_t *nRF0, delay_t delay)		// reg 0x04
{
	if ( (delay > DELAY_4000us) || (delay < DELAY_250us) )
	{
		ERROR("Wrong retransmit delay\n");
		// return -1;
	}
	else
	{
		bool b3, b2, b1, b0;
		b0 = delay & 1;
		b1 = (delay >> 1) & 1;
		b2 = (delay >> 2) & 1;
		b3 = (delay >> 3) & 1;

		//printf("\t\t\t\t%s(): delay: %d, bin: %d%d%d%d\n", __func__, delay, b3, b2, b1, b0);

		write_reg(nRF0, REG_SETUP_RETR, (b3 << ARD3) | (b2 << ARD2) | (b1 << ARD1) | (b0 << ARD0));
	}
}
// INFO provjereno

/*************************************************************************************************
				nRF_set_retransmit_count()
*************************************************************************************************/
void nRF_set_retransmit_count(nRF_hw_t *nRF0, uint8_t count)		// reg 0x04
{
	if ( (count < 0) || (count > 15) )
	{
		ERROR("count must be 0..15\n");
		//printf("count must be 0..15\n");
		// return -1;
	}
	else
	{
		bool b3, b2, b1, b0;
		b0 =  count & 1;
		b1 = (count >> 1) & 1;
		b2 = (count >> 2) & 1;
		b3 = (count >> 3) & 1;

		//printf("\t\t\t\t%s(): count: %d bin:%d%d%d%d\n", __func__, count, b3, b2, b1, b0);

		write_reg(nRF0, REG_SETUP_RETR, (b3 << ARC3) | (b2 << ARC2) | (b1 << ARC1) | (b0 << ARC0));
	}
}
// INFO provjereno

/*************************************************************************************************
				nRF_set_channel
*************************************************************************************************/
void nRF_set_channel(nRF_hw_t *nRF0, uint8_t ch)					// reg 0x05
{
	// 7b, default: 0000010
	// Freq: 2.400GHz to 2.525GHz
		// 125 MHz
	// Freq = 2400 + ch
	// 1Mbps	- kanali razmakniti 1MHz
	// 2Mbps	- kanali razmakniti 2Mhz

	// TODO

}

/*************************************************************************************************
				nRF_set_data_rate()
*************************************************************************************************/
void nRF_set_data_rate(nRF_hw_t *nRF0, datarate_t datarate)			// reg 0x06
{
	//if ( (datarate != 0) && (datarate != 1) )
	if ( (datarate < datarate_1Mbps) || (datarate > datarate_2Mbps) )
	{
		ERROR("Wrong datarate\n");
		//printf("Wrong datarate\n");
		// return -1;
	}
	else
	{
		//printf("\t\t\t\t%s(): datarate: %d\n", __func__, datarate);
		write_reg(nRF0, REG_RF_SETUP, (datarate << RF_DR));
	}
}
// INFO provjereno

/*************************************************************************************************
				nRF_set_output_power()
*************************************************************************************************/
void nRF_set_output_power(nRF_hw_t *nRF0, output_power_t power)		// reg 0x06
{
	if ( (power < power_minus_18dBm) || (power > power_0dBm) )
	{
		ERROR("Wrong output power\n");
		//printf("Wrong output power\n");
	}
	else
	{
		bool b1, b0;
		b0 = power & 1;
		b1 = (power >> 1) & 1;

		//printf("\t\t\t\t%s(): power: %d bin: %d%d\n", __func__, power, b1, b0);
		write_reg(nRF0, REG_RF_SETUP, (b1 << RF_PWR1) | (b0 << RF_PWR0));
	}
}
// INFO provjereno
// INFO neimplementirano, 0x06: LNA gain

/*************************************************************************************************
				nRF_is_RX_data_ready()
*************************************************************************************************/
//bool nRF_get_status_data_ready(nRF_hw_t *nRF0)					// reg 0x06, b6
bool nRF_is_RX_data_ready(nRF_hw_t *nRF0)							// reg 0x06, b6
{
	//Data Ready RX FIFO interrupt. Asserted when
	//new data arrives RX FIFOb.
	//Write 1 to clear bit.

	uint8_t status = read_reg(nRF0, REG_STATUS);

	//return ((status >> 6) & 1);		// after reset: 0
	return ((status >> RX_DR) & 1);		// after reset: 0
}
// INFO provjereno

/*************************************************************************************************
				nRF_clear_RX_data_ready()
*************************************************************************************************/
void nRF_clear_RX_data_ready(nRF_hw_t *nRF0)						// reg 0x06, b6
{
	write_reg(nRF0, REG_STATUS, (1 << RX_DR));
}
// TODO provjerit

/*************************************************************************************************
				nRF_is_TX_data_sent()
*************************************************************************************************/
bool nRF_is_TX_data_sent(nRF_hw_t *nRF0)							// reg 0x06, b5
{
	//Data Sent TX FIFO interrupt. Asserted when 
	//packet transmitted on TX. If AUTO_ACK is acti-
	//vated, this bit is set high only when ACK is 
	//received.
	//Write 1 to clear bit.

	uint8_t status = read_reg(nRF0, REG_STATUS);
	return ((status >> TX_DS) & 1);		// after reset: 0
}
// INFO provjereno

/*************************************************************************************************
				nRF_clear_TX_data_sent()
*************************************************************************************************/
void nRF_clear_TX_data_sent(nRF_hw_t *nRF0)							// reg 0x06, b5
{
	write_reg(nRF0, REG_STATUS, (1 << TX_DS));
}
// TODO provjerit
// INFO neimplementirano: provjera MAX_RT (REG_STATUS, b4)

/*************************************************************************************************
				nRF_data_pipe_avaible()
*************************************************************************************************/
data_pipe_t nRF_data_pipe_avaible(nRF_hw_t *nRF0)						// reg 0x06, b321
{
	//Data pipe number for the payload available for 
	//reading from RX_FIFO
	//000-101: Data Pipe Number
	//110: Not Used
	//111: RX FIFO Empty		default

	uint8_t status = read_reg(nRF0, REG_STATUS);
	data_pipe_t pipe = (status >> 1) & 0b111;	// pretvori u decimalni broj

	printf("%s(): data pipe: %d\n", __func__, pipe);

	if (pipe == RX_FIFO_empty)
	{
		printf("%s(): RX FIFO is empty\n", __func__);
	}
	else if (pipe == pipe_not_used)
	{
		printf("%s(): pipe is not used\n");
	}
	else if ( (pipe <= avaible_pipe5) || (pipe >= avaible_pipe0) )
	{
		printf("%s(): Avaible pipe: %d\n", __func__, pipe);
	}

	return pipe;
}










/*************************************************************************************************
				nRF_hw_init()
*************************************************************************************************/
int8_t nRF_hw_init(nRF_hw_t *nRF0)
{
	DEBUG_START;

	char *cs = nRF0->cs;
	char *ce = nRF0->ce;
	char *irq = nRF0->irq;
	uint16_t prescaler = nRF0->spi_prescaler;

	if (strlen(cs) != 0)
	{
		//printf("%s(): cs: %s\n", __func__, cs);
		gpio_init(cs, OUT);
	}
	else
	{
		ERROR("CS pin not connected\n");
	}

	if (strlen(ce) != 0)
	{
		//printf("%s(): ce: %s\n", __func__, nRF0->ce);
		gpio_init(ce, OUT);
	}
	else
	{
		ERROR("CE pin not connected\n");
	}

	if (strlen(irq) != 0)
	{
		//printf("%s(): irq: %s\n", __func__, nRF0->irq);
		gpio_init(irq, IN);
	}
	else
	{
		DEBUG_INFO("IRQ pin not connected\n");
	}

	if (spi_init(1, prescaler))
	{
		ERROR("SPI not initialized\n");

		DEBUG_END;
		return -1;
	}

	DEBUG_END;
	return 0;
}


/*************************************************************************************************
				ce()
*************************************************************************************************/
static void ce(nRF_hw_t *nRF0, state_t state)
{
	char *ce = nRF0->ce;
	gpio(ce, state);
}

/*************************************************************************************************
				cs()
*************************************************************************************************/
static void cs(nRF_hw_t *nRF0, state_t state)
{
	char *cs = nRF0->cs;
	gpio(cs, state);
}

/*************************************************************************************************
				read_reg()
*************************************************************************************************/
static uint8_t read_reg(nRF_hw_t *nRF0, uint8_t reg)
{
	DEBUG_START;
	uint8_t status;
	uint8_t spi_port = nRF0->spi_port;

	cs(nRF0, 0);
	spi_rw(spi_port, CMD_R_REGISTER + reg);
	status = spi_rw(spi_port, 0x00);	// dummy write
	cs(nRF0, 1);

	DEBUG_END;
	return status;
}
/*************************************************************************************************
				print_reg()
*************************************************************************************************/
static void print_reg(nRF_hw_t *nRF0, uint8_t reg)
{
	DEBUG_START;

	uint8_t status = read_reg(nRF0, reg);

	printf("reading reg: 0x%X: %3d = 0b%s\n", reg, status, dec2bin8_str(status));	

	DEBUG_END;
}

/*************************************************************************************************
				write_reg()
*************************************************************************************************/
static uint8_t write_reg(nRF_hw_t *nRF0, uint8_t reg, uint8_t arg)
{
	DEBUG_START;
	uint8_t old_reg = read_reg(nRF0, reg);

	// TODO
	printf("register: 0x%X, old: %d, new: %d\n", reg, old_reg, arg);

	uint8_t status;
	uint8_t spi_port = nRF0->spi_port;

	//printf("SPI ce zapisat: %d %d\n", reg + CMD_W_REGISTER, (old_reg | arg));

	cs(nRF0, 0);
	status = spi_rw(spi_port, reg + CMD_W_REGISTER);
	spi_rw(spi_port, (old_reg | arg));
	cs(nRF0, 1);

	DEBUG_END;
	return status;
}

/*************************************************************************************************
				get_status()
*************************************************************************************************/
static uint8_t get_status(nRF_hw_t *nRF0)
{
	// ili ovako ili procitat registar STATUS (0x07)
	uint8_t status;
	uint8_t spi_port = nRF0->spi_port;

	cs(nRF0, 0);
	status = spi_rw(spi_port, 0xFF);
	cs(nRF0, 1);

	/*
	   14 = RX FIFO empty
	 */

	return status;
}
