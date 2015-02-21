#include "nRF.h"
#include "src/nRF/nRF_reg.h"

// TODO
// low: GPIO i SPI
// mid: operacije sa registrima
// high: set i get funkcije

#include "src/nRF/nRF_set_address_width.c"
#include "src/nRF/nRF_get_address_width.c"
#include "src/nRF/nRF_set_retransmit_delay.c"
#include "src/nRF/nRF_set_retransmit_count.c"
#include "src/nRF/nRF_set_channel.c"
#include "src/nRF/nRF_set_data_rate.c"
#include "src/nRF/nRF_get_data_rate.c"
#include "src/nRF/nRF_set_output_power.c"
// INFO neimplementirano, 0x06: LNA gain
#include "src/nRF/nRF_is_RX_data_ready.c"
#include "src/nRF/nRF_clear_RX_data_ready.c" 	// XXX
#include "src/nRF/nRF_is_TX_data_sent.c"
#include "src/nRF/nRF_clear_TX_data_sent.c" 	// XXX
// INFO neimplementirano: provjera MAX_RT (REG_STATUS, b4)
#include "src/nRF/nRF_data_pipe_avaible.c"
#include "src/nRF/nRF_is_TX_full.c"
#include "src/nRF/nRF_hw_init.c"
#include "src/nRF/nRF_gpio.c"
#include "src/nRF/nRF_reg.c"
#include "src/nRF/nRF_get_status.c"

/*************************************************************************************************
				nRF_main()
*************************************************************************************************/
void nRF_main()
{
	DEBUG_START;

	// TODO napravit da je uvijek u RX modu, samo kad salje da se presalta u TX
	nRF_hw_t primac;

	//primac.spi_port = 1;
	primac.spi_port = 2;
	//primac.spi_speed_MHz = 
	primac.spi_prescaler = 32;
	primac.cs = "PB5";
	primac.ce = "PB4";
	//primac.irq = "PB3";	// NC

	if (nRF_hw_init(&primac) != 0)
	{
		ERROR("module not initialized\n");
		// return -1;
	}
	delay_ms(11);	// 10.3 ms

	//printf("nRF je odradio hardverski init\n");

	// power up
	//write_reg(&primac, REG_CONFIG, (1 << PWR_UP) | (0 << PRIM_RX));
	write_reg(&primac, REG_CONFIG, (1 << PWR_UP) | (0 << PRIM_RX), 0);
	/*
	write_reg(&primac, REG_CONFIG, (0 << PRIM_RX), PRIM_RX);
	write_reg(&primac, REG_CONFIG, (1 << PWR_UP), PWR_UP);
	*/

	printf("PRIM_RX: %d\n", PRIM_RX);
	printf("PWR_UP: %d\n", PWR_UP);

	print_reg(&primac, REG_CONFIG);

	delay_ms(2);	// 1.5ms
	// sad je u Standby-1 modu

	/*
	printf("status: ");
	dec2bin8(get_status(&primac));
	printf("\n");


	// retransmit count = 15
	nRF_set_retransmit_count(&primac, 15);

	// 1ms Retransmit Delay
	nRF_set_retransmit_delay(&primac, DELAY_1ms);


	// 5 bytes address width
	nRF_set_address_width(&primac, 5);
	// 0000010 default
	//write_reg(&primac, REG_RF_CH, 0b0000010);	// default ch

	// CRC enable, 1 byte length
	// set data rate to 1Mbps
	nRF_set_data_rate(&primac, datarate_1Mbps);	// reg 0x06

	// max payload length = 32
	// set mode to RX, napravi to automatski
	// set channel
	// set 

	// full powa
	nRF_set_output_power(&primac, power_0dBm);


	printf("RX data ready: %d\n", nRF_is_RX_data_ready(&primac));
	printf("TX data sent: %d\n", nRF_is_TX_data_sent(&primac));
	nRF_data_pipe_avaible(&primac);	// TODO provjerit detaljnije
	printf("TX full: %d\n", nRF_is_TX_full(&primac));
	//printf("datarate: %d\n", nRF_get_data_rate(&primac));
	datarate_t datarate = nRF_get_data_rate(&primac);
	if (datarate == datarate_1Mbps)
	{
		printf("datarate is 1Mbps\n");
	}
	else if (datarate == datarate_2Mbps)
	{
		printf("datarate is 2Mbps\n");
	}
	else
	{
		printf("uknown datarate\n");
	}

	nRF_set_channel(&primac, 0);
	*/

	nRF_set_address_width(&primac, 5);
	uint8_t width = nRF_get_address_width(&primac);
	printf("nRF main: address width: %d\n", width);
	printf("address width: %d\n", primac.address_width);
	nRF_get_RX_address(&primac, P0);	// zapise u objekt

	printf("address: \n");
	for (uint8_t i=0; i<primac.address_width; i++)
	{
		//printf("[%d]: 0x%X\n", i, primac.address[i]);
		printf("[%d]: 0x%X\n", i, primac.address[0][i]);
	}
	
	// set address		// TODO mozda ima bolji nacin


	print_reg(&primac, 0x00);
	print_reg(&primac, 0x01);
	print_reg(&primac, 0x02);
	print_reg(&primac, 0x03);
	print_reg(&primac, 0x04);
	print_reg(&primac, 0x05);
	print_reg(&primac, 0x06);
	print_reg(&primac, 0x07);

	DEBUG_END;
}

//#include "src/nRF/nRF_get_RX_address.c"

/*************************************************************************************************
				nRF_get_RX_address()
*************************************************************************************************/
int8_t nRF_get_RX_address(nRF_hw_t *nRF0, pipe_t pipe)				// reg 0x0{A,B,C,D,E,F}
{
#define BASE_PIPE REG_RX_ADDR_P0

	uint8_t tmp_addr[5] = {};

	//printf("\t\t\t\t%s(): pipe: %d\n", __func__, pipe);

	//if ( (pipe > 5) || (pipe < 0) )
	if (pipe > 5) 		// unsigned enum
	{
		ERROR("Wrong pipe\n");
		//printf("Wrong pipe\n");
		return -1;
	}
	else
	{
		uint8_t width = nRF_get_address_width(nRF0);
		uint8_t spi_port = nRF0->spi_port;

		cs(nRF0, 0);
		// 40 bits, 8bit reads

		if (pipe < 2)	// P0, P1
		{
			spi_rw(spi_port, (BASE_PIPE+pipe) + CMD_R_REGISTER);	// 0x0A+pipe

			// procitaj normalno onoliko bajtova kolika je sirina adrese
			for (uint8_t i=0; i<width; i++)
			{
				tmp_addr[i] = spi_rw(spi_port, 0xFF);
			}
		}
		else
		{
			spi_rw(spi_port, (BASE_PIPE) + CMD_R_REGISTER);	

			// procitaj max 4 MSB od P0
			for (uint8_t i=0; i<width-1; i++)
			{
				tmp_addr[i] = spi_rw(spi_port, 0xFF);
			}
			cs(nRF0, 1);
			cs(nRF0, 0);

			// procitaj LSB
			spi_rw(spi_port, (BASE_PIPE+pipe) + CMD_R_REGISTER);	// 0x0A+pipe
			tmp_addr[width-1] = spi_rw(spi_port, 0xFF);
		}
		cs(nRF0, 1);

		printf("width: %d\n", width);
		// zapisimo u objekt
		for (uint8_t i=0; i<width; i++)
		{
			//memmove(&nRF0->address[i], &tmp_addr[i], sizeof(nRF0->address[i]));
			// 2D polje
			memmove(&nRF0->address[pipe][i], &tmp_addr[i], sizeof(nRF0->address[pipe][i]));
		}
		return 0;
	}
}


/*************************************************************************************************
				nRF_set_RX_address()
*************************************************************************************************/
//int8_t nRF_set_RX_address(nRF_hw_t *nRF0, uint8_t pipe, char *address)	// reg 0x0A
int8_t nRF_set_RX_address(nRF_hw_t *nRF0, pipe_t pipe, uint8_t address[])	// reg 0x0A
{
	// LSB se prvi zapisuje
	uint8_t width = nRF_get_address_width(nRF0);

	printf("\t\t\t\t%s(): pipe: %d, address: %s\n", __func__, pipe, address);

	//if ( (pipe > 5) || (pipe < 0) )
	if (pipe > 5)		// unsigned enum
	{
		ERROR("Wrong pipe\n");
		printf("Wrong pipe\n");
		return -1;
	}
	else if ( (width < 3) || (width > 5) )
	{
		ERROR("Wrong address width\n");
		printf("Wrong address width\n");
		return -1;
	}
	else
	{
		cs(nRF0, 0);
		// 40 bits, 8bit reads
		spi_rw(nRF0->spi_port, 0x0A + CMD_W_REGISTER);

		for (uint8_t i=0; i<width; i++)
		{

		}
		cs(nRF0, 1);

		return 0;
	}
}
