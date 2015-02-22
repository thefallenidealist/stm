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
#include "src/nRF/nRF_channel.c"
#include "src/nRF/nRF_set_data_rate.c"
#include "src/nRF/nRF_get_data_rate.c"
#include "src/nRF/nRF_set_output_power.c"
// INFO neimplementirano, 0x06: LNA gain
#include "src/nRF/nRF_is_RX_data_ready.c"
#include "src/nRF/nRF_clear_RX_data_ready.c" 	// XXX
#include "src/nRF/nRF_is_TX_data_sent.c"
#include "src/nRF/nRF_clear_TX_data_sent.c" 	// XXX
// INFO neimplementirano: provjera MAX_RT (REG_STATUS, b4)
#include "src/nRF/nRF_pipe_available.c"
#include "src/nRF/nRF_is_TX_full.c"
#include "src/nRF/nRF_hw_init.c"
#include "src/nRF/nRF_gpio.c"
#include "src/nRF/nRF_reg.c"
#include "src/nRF/nRF_get_status.c"
#include "src/nRF/nRF_get_RX_address.c"
#include "src/nRF/nRF_set_RX_address.c" 	// mora se rucno pazit da je adresa ispravne sirine
#include "src/nRF/nRF_set_TX_address.c" 	// isto
#include "src/nRF/nRF_get_TX_address.c"
// TODO preimenovat u samo set/get payload size
#include "src/nRF/nRF_set_RX_payload_size.c"
#include "src/nRF/nRF_get_RX_payload_size.c"
#include "src/nRF/nRF_flush.c"
#include "src/nRF/nRF_observe_tx.c"
#include "src/nRF/nRF_crc.c"
#include "src/nRF/nRF_power.c"
#include "src/nRF/nRF_enable_pipe.c"
#include "src/nRF/nRF_mode.c"
#include "src/nRF/nRF_crc_length.c"

/*************************************************************************************************
				nRF_main()
*************************************************************************************************/
void nRF_main()
{
	DEBUG_START;

	delay_ms(12);

	nRF_hw_t davac;
	nRF_hw_t primac;

	davac.spi_port = 1;
	primac.spi_port = 2;
	davac.spi_prescaler = 32;
	primac.spi_prescaler = 32;
	davac.cs = "PB0";
	primac.cs = "PB5";
	davac.ce = "PB2";
	primac.ce = "PB4";
	//davac.irq = "";	// NC
	//primac.irq = "PB3";	// NC

	delay_ms(11);	// 10.3 ms		// power on delay
	if (nRF_hw_init(&davac) != 0)
	{
		printf("Davac is not initialized\n");
		// return -1;
	}

	delay_ms(11);	// 10.3 ms		// power on delay
	if (nRF_hw_init(&primac) != 0)
	{
		printf("Primac is not initialized\n");
		// return -1;
	}

	nRF_set_mode(&davac, TX);
	nRF_set_mode(&primac, RX);
	nRF_power_on(&davac);
	nRF_power_on(&primac);
	nRF_set_retransmit_count(&davac, 15);
	nRF_set_retransmit_count(&primac, 15);
	nRF_set_retransmit_delay(&davac, DELAY_1ms);
	nRF_set_retransmit_delay(&primac, DELAY_1ms);
	nRF_set_address_width(&davac, 5);
	nRF_set_address_width(&primac, 5);
	nRF_set_channel(&davac, 0);
	nRF_set_channel(&primac, 0);
	nRF_set_output_power(&davac, power_0dBm);
	nRF_set_output_power(&primac, power_0dBm);
	nRF_set_data_rate(&davac, datarate_1Mbps);
	nRF_set_data_rate(&primac, datarate_1Mbps);
	nRF_set_RX_payload_size(&davac, P0, 32);
	nRF_set_RX_payload_size(&primac, P0, 32);
	nRF_enable_pipe(&davac, P0);
	nRF_enable_pipe(&primac, P0);
	nRF_enable_CRC(&davac);
	nRF_enable_CRC(&primac);
	nRF_set_CRC_length(&davac, CRC_LENGTH_2BTYE);
	nRF_set_CRC_length(&primac, CRC_LENGTH_2BTYE);

	nRF_set_RX_address(&primac, "test");
	printf("Primac address: %s\n", nRF_get_RX_address(&primac));
	nRF_set_TX_address(&davac, "test");
	printf("Davac address: %s\n", nRF_get_TX_address(&davac));

	printf("\n");
	printf("Davac registri:\n");
	print_reg(&davac, 0x00);
	print_reg(&davac, 0x01);
	print_reg(&davac, 0x02);
	print_reg(&davac, 0x03);
	print_reg(&davac, 0x04);
	print_reg(&davac, 0x05);
	print_reg(&davac, 0x06);
	print_reg(&davac, 0x07);
	print_reg(&davac, 0x08);
	print_reg(&davac, 0x11);
	print_reg(&davac, 0x12);
	print_reg(&davac, 0x0A);
	printf("\n");
	printf("\n");
	printf("Primac registri:\n");
	print_reg(&primac, 0x00);
	print_reg(&primac, 0x01);
	print_reg(&primac, 0x02);
	print_reg(&primac, 0x03);
	print_reg(&primac, 0x04);
	print_reg(&primac, 0x05);
	print_reg(&primac, 0x06);
	print_reg(&primac, 0x07);
	print_reg(&primac, 0x08);
	print_reg(&primac, 0x11);
	print_reg(&primac, 0x12);
	print_reg(&primac, 0x0A);



	/*
	nRF_hw_t primac;

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

	nRF_set_mode(&primac, RX);						// set mode to RX, napravi to automatski
	nRF_power_on(&primac);							// power up

	print_reg(&primac, REG_CONFIG);

	nRF_set_retransmit_count(&primac, 15); 			// retransmit count = 15
	nRF_set_retransmit_delay(&primac, DELAY_1ms); 	// 1ms Retransmit Delay
	nRF_set_address_width(&primac, 5);				// 5 bytes address width
	nRF_set_channel(&primac, 0);					// set channel
	*/


	// CRC enable, 1 byte length

	// max payload length = 32
	// set channel
	// set 

	// full powa
	//nRF_set_output_power(&primac, power_0dBm);


	/*
	printf("RX data ready: %d\n", nRF_is_RX_data_ready(&primac));
	printf("TX data sent: %d\n", nRF_is_TX_data_sent(&primac));
	//nRF_data_pipe_avaible(&primac);	// TODO provjerit detaljnije
	printf("TX full: %d\n", nRF_is_TX_full(&primac));


	nRF_set_data_rate(&primac, datarate_1Mbps);		// set data rate to 1Mbps
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
	*/


	/*
	nRF_get_RX_address(&primac);	// zapise u objekt

	printf("address: \n");
	for (uint8_t i=0; i<primac.address_width; i++)
	{
		printf("[%d]: 0x%X\n", i, primac.address[0][i]);
	}
	*/
	
	// set RX address	
	// INFO kod postavljanja RX/TX addresa treba rucno pazit da se podudara, inace se skratit ili nesto gore
	/*
	nRF_set_address_width(&primac, 5);
	uint8_t rx_address[5] = {'a','b','c','d','e'};
	if (nRF_set_RX_address(&primac, rx_address))
	{
		printf("nRF set RX address error\n");
	}
	printf("nRF_get_RX_address return: %s\n", nRF_get_RX_address(&primac)); // nacin 2
	*/

	/*
	// set TX address
	uint8_t tx_address[5] = {'t','x','T','X','1'};
	if (nRF_set_TX_address(&primac, tx_address))
	{
		printf("nRF set TX address error\n");
	}
	printf("nRF_get_TX_address return: %s\n", nRF_get_TX_address(&primac)); // nacin 2
	*/

	/*

	// set payload size
	if (nRF_set_RX_payload_size(&primac, P0, 32))
	{
		printf("nRF_set_RX_payload_size error\n");
	}
	printf("nRF_get_RX_payload_size return: %d\n", nRF_get_RX_payload_size(&primac, P0));

	printf("Lost packets: %d\n", nRF_get_lost_packets(&primac));
	printf("Retransmitted packets: %d\n", nRF_get_retransmitted_packets(&primac));

	printf("Enabling pipe0\n");
	//nRF_enable_pipe(&primac, (P2 | P1 | P0));
	nRF_enable_pipe(&primac, P0);

	nRF_enable_CRC(&primac);

	printf("\n");
	print_reg(&primac, 0x00);
	print_reg(&primac, 0x01);
	print_reg(&primac, 0x02);
	print_reg(&primac, 0x03);
	print_reg(&primac, 0x04);
	print_reg(&primac, 0x05);
	print_reg(&primac, 0x06);
	print_reg(&primac, 0x07);
	print_reg(&primac, 0x08);
	print_reg(&primac, 0x11);
	print_reg(&primac, 0x12);

	printf("nRF primac mode [0 TX, 1 RX]: %d\n", nRF_get_mode(&primac));
	printf("nRF ch: %d\n", nRF_get_channel(&primac));

	nRF_set_CRC_length(&primac, CRC_LENGTH_2BTYE);
	printf("Primac CRC length [0 - 1byte, 1 - 2bytes]: %d\n", nRF_get_CRC_length(&primac));
	*/

	/*
	printf("Citam payload\n");
	if (nRF_read_payload(&primac, 32) != NULL)
	{
		printf("Read payload gotov\n");
		printf("Printam buffer:\n");
		for (uint16_t i=0; i<256; i++)
		{
			printf("RX[%d]: 0x%02X\n", i, nRF_RX_buffer[i]);
		}
	}
	*/

	DEBUG_END;
}






// TODO svaka funkcija provjerava jel dobila NULL adresu


/*
   TODO
   enable_auto_ACK(pipe_t pipe)		// po defaultu upaljeno za sve

   write_payload		
   */


uint8_t nRF_TX_buffer[256];
/*************************************************************************************************
				nRF_write_payload()
*************************************************************************************************/
//void nRF_write_payload(nRF_hw_t *nRF0, uint8_t *buffer, uint8_t length)
void nRF_write_payload(nRF_hw_t *nRF0, uint8_t length)
{
	uint8_t spi_port = nRF0->spi_port;

	uint8_t *buffer = &nRF_TX_buffer[0];

	cs(nRF0, 0);

	spi_rw(spi_port, CMD_W_TX_PAYLOAD);
	while (length --)
	{
		spi_rw(spi_port, *buffer++);
	}

	cs(nRF0, 1);
}


/*************************************************************************************************
				nRF_read_payload()
*************************************************************************************************/
uint8_t nRF_RX_buffer[256];

uint8_t *nRF_read_payload(nRF_hw_t *nRF0, uint8_t howmany)
{
	if ( (howmany < 0) || (howmany > 32) )
	{
		ERROR("Wrong number of bytes to read\n");
		printf("Wrong number of bytes to read\n");

		return NULL;
	}
	uint8_t spi_port = nRF0->spi_port;

	cs(nRF0, 0);
	spi_rw(spi_port, CMD_R_RX_PAYLOAD);

	for (uint8_t i=0; i<howmany; i++)
	{
		nRF_RX_buffer[i] = spi_rw(spi_port, CMD_NOP);
	}
	cs(nRF0, 1);

	return nRF_RX_buffer;
}

