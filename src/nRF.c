#include "nRF.h"
#include "src/nRF/nRF_reg.h"

// TODO const keyword gdje treba
// TODO svaka funkcija provjerava jel dobila NULL adresu
// TODO enable_auto_ACK(pipe_t pipe)		// po defaultu upaljeno za sve

// low layer
#include "src/nRF/nRF_hw_init.c"
#include "src/nRF/nRF_gpio.c"

// mid layer
#include "src/nRF/nRF_reg.c"

// high layer
#include "src/nRF/nRF_address_width.c"
#include "src/nRF/nRF_retransmit_delay.c"
#include "src/nRF/nRF_retransmit_count.c"
#include "src/nRF/nRF_channel.c"
#include "src/nRF/nRF_datarate.c"
#include "src/nRF/nRF_set_output_power.c"
#include "src/nRF/nRF_clear.c"
#include "src/nRF/nRF_pipe_available.c"
#include "src/nRF/nRF_is_TX_data_sent.c"
#include "src/nRF/nRF_is_TX_full.c"
#include "src/nRF/nRF_is_RX_empty.c"
#include "src/nRF/nRF_is_RX_data_ready.c"

#include "src/nRF/nRF_RX_address.c" 
#include "src/nRF/nRF_TX_address.c"
#include "src/nRF/nRF_payload_size.c"
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
int8_t nRF_main()
{
	DEBUG_START;
	printf("nRF_main() start\n");

	nRF_hw_t rf_tx;
	nRF_hw_t rf_rx;

	//printf("nRF TX: %p\n", &rf_tx);
	//printf("nRF RX: %p\n", &rf_rx);

	rf_tx.spi_port = 1;
	rf_tx.spi_prescaler = 32;
	rf_tx.cs = "PA4";
	rf_tx.ce = "PA3";
	//rf_tx.irq = "";	// NC

	rf_rx.spi_port = 2;
	rf_rx.spi_prescaler = 32;
	rf_rx.cs = "PB5";
	rf_rx.ce = "PB4";
	//rf_rx.irq = "PB3";	// NC

	delay_ms(11);	// 10.3 ms		// power on delay
	delay_ms(11);	// 10.3 ms		// power on delay
	delay_ms(11);	// 10.3 ms		// power on delay

	if (nRF_hw_init(&rf_tx) != 0)
	{
		printf("RF_TX is not initialized\n");
		 return -1;
	}

	if (nRF_hw_init(&rf_rx) != 0)
	{
		printf("RF_RX is not initialized\n");
		 return -1;
	}

	nRF_set_mode(&rf_tx, TX);
	nRF_set_mode(&rf_rx, RX);

	nRF_clear_bits(&rf_tx);
	nRF_clear_bits(&rf_rx);

	nRF_set_retransmit_count(&rf_tx, 15);
	nRF_set_retransmit_count(&rf_rx, 15);
	nRF_set_retransmit_delay(&rf_tx, DELAY_1ms);
	nRF_set_retransmit_delay(&rf_rx, DELAY_1ms);

	nRF_set_channel(&rf_tx, 0);
	nRF_set_channel(&rf_rx, 0);

	nRF_set_output_power(&rf_tx, power_0dBm);
	nRF_set_output_power(&rf_rx, power_0dBm);

	nRF_set_datarate(&rf_tx, datarate_1Mbps);
	nRF_set_datarate(&rf_rx, datarate_1Mbps);

	nRF_enable_pipe(&rf_tx, P0);
	nRF_enable_pipe(&rf_rx, P0);

	nRF_set_CRC_length(&rf_tx, CRC_LENGTH_1BTYE);
	nRF_set_CRC_length(&rf_rx, CRC_LENGTH_1BTYE);
	nRF_enable_CRC(&rf_tx);
	nRF_enable_CRC(&rf_rx);

	uint8_t addr[5] = "qwert";

	nRF_set_address_width(&rf_tx, 5);
	nRF_set_address_width(&rf_rx, 5);
	nRF_set_TX_address(&rf_tx, addr);
	nRF_set_RX_address(&rf_tx, addr);
	nRF_set_RX_address(&rf_rx, addr);

	printf("RF_RX address: %s\n", nRF_get_RX_address(&rf_rx));
	printf("RF_TX address: %s\n", nRF_get_TX_address(&rf_tx));

	//nRF_flush_TX(&rf_tx);
	/*
	print_reg(&rf_tx, REG_FIFO_STATUS);
	printf("TX FIFO full:  %d\n", nRF_is_TX_full(&rf_tx));
	printf("TX FIFO full2: %d\n", nRF_is_TX_full2(&rf_tx));
	printf("TX FIFO empty: %d\n", nRF_is_TX_empty(&rf_tx));
	printf("\n");
	print_reg(&rf_rx, REG_FIFO_STATUS);
	printf("RX FIFO full:  %d\n", nRF_is_RX_full(&rf_rx));
	printf("RX FIFO empty: %d\n", nRF_is_RX_empty(&rf_rx));
	printf("RX FIFO empty2 %d\n", nRF_is_RX_empty2(&rf_rx));
	printf("\n");
	*/

	nRF_clear_bits(&rf_tx);
	nRF_clear_bits(&rf_rx);

	// present
	/*
	int8_t present_tx = nRF_is_present(&rf_tx);
	int8_t present_rx = nRF_is_present(&rf_rx);
	printf("TX present: %d\n", present_tx);
	printf("RX present: %d\n", present_rx);
	if ( (present_tx == 0) || (present_rx == 0) )
	{
		return -1;
	}
	*/

	//printf("RF_TX datarate: %d\n", nRF_get_datarate(&rf_tx));
	//printf("RF_RX datarate: %d\n", nRF_get_datarate(&rf_rx));

	// start RX listening
	nRF_start_listening(&rf_rx);

	print_reg(&rf_tx, 0x00);
	print_reg(&rf_rx, 0x00);
	/*
	printf("\n");
	printf("Registri, 1TX, 2RX\n");
	print_reg(&rf_tx, 0x00);
	print_reg(&rf_rx, 0x00);


	print_reg(&rf_tx, 0x01);
	print_reg(&rf_rx, 0x01);

	//print_reg(&rf_tx, 0x02);
	//print_reg(&rf_tx, 0x03);

	print_reg(&rf_tx, 0x04);
	print_reg(&rf_rx, 0x04);

	//print_reg(&rf_tx, 0x05);

	print_reg(&rf_tx, 0x06);
	print_reg(&rf_rx, 0x06);

	print_reg(&rf_tx, 0x07);
	print_reg(&rf_rx, 0x07);

	print_reg(&rf_tx, 0x08);
	print_reg(&rf_rx, 0x08);

	//print_reg(&rf_tx, 0x11);
	//print_reg(&rf_rx, 0x11);

	//print_reg(&rf_tx, 0x12);
	//print_reg(&rf_rx, 0x12);

	print_reg(&rf_tx, 0x0A);
	print_reg(&rf_rx, 0x0A);
	*/

	printf("Is data sent: %d\n", nRF_is_TX_data_sent(&rf_tx));

	printf("\t\t\t\tSaljem teret\n");
	nRF_clear_bits(&rf_tx);

	uint8_t payloadTX_size = 8;
	memcpy(nRF_TX_buffer, " ovo je neki tekst za poslat koji je malo duzi nego sto treba bit", 32);

	rtc_get_time();
	nRF_TX_buffer[0] = 48+RTC_data.seconds;
	printf("\t\t\t\t\t%s\n", nRF_TX_buffer);

	nRF_set_payload_size(&rf_tx, P0, payloadTX_size);
	nRF_set_payload_size(&rf_rx, P0, payloadTX_size);
	nRF_write_payload(&rf_tx, nRF_TX_buffer, payloadTX_size);

	printf("TX: Lost packets: %d\n", 			nRF_get_lost_packets			(&rf_tx));
	printf("TX: Retransmitted packets: %d\n", 	nRF_get_retransmitted_packets	(&rf_tx));

	printf("\n");
	print_reg(&rf_tx, REG_CONFIG);
	printf("TX: Is data sent: %d\n", nRF_is_TX_data_sent(&rf_tx));

	/*
	ce(&rf_rx, 0);		// radi i bez ovoga
	delay_ms(10);
	*/


	if (nRF_read_payload(&rf_rx) != NULL)
	{
		printf("nRF_read_payload() je uspjesno odradio svoje\n");
	}

	//printf("TX Retransmit count: %d\n", nRF_get_retransmit_count(&rf_tx));
	//printf("RX Retransmit count: %d\n", nRF_get_retransmit_count(&rf_rx));
	//printf("TX Retransmit delay: %d\n", nRF_get_retransmit_delay(&rf_tx));
	//printf("RX Retransmit delay: %d\n", nRF_get_retransmit_delay(&rf_rx));

	return 0;
	DEBUG_END;
}


uint8_t nRF_TX_buffer[32];
/*************************************************************************************************
				nRF_write_payload()
*************************************************************************************************/
void nRF_write_payload(nRF_hw_t *nRF0, uint8_t *buffer, uint8_t length)
{
#define TX_TIMEOUT 60			// INFO max time before fail: retry counts * retry delay = 15 * 4ms = 60 ms
#define TX_SINGLE_TIMEOUT 10	// 10 ms
	uint8_t spi_port = nRF0->spi_port;

	/*
	   // djeluje nepotrebno
	//nRF_flush_TX(nRF0);	

	reg_tmp[PWR_UP] = 1;
	reg_tmp[PRIM_RX] = 0;
	write_reg(nRF0, REG_CONFIG);
	delay_us(150);	// TODO datasheet, page X
					// vjerojatno kopirano odnegdje sa neta
	*/

	cs(nRF0, 0);
	spi_rw(spi_port, CMD_W_TX_PAYLOAD);
	while (length--)
	{
		spi_rw(spi_port, *buffer++);
	}
	cs(nRF0, 1);

	// CE pulse for 10us to send payload
	ce(nRF0, 1);
	delay_us(10);
	ce(nRF0, 0);

	while (nRF_is_TX_data_sent(nRF0) == 0)
	{
		if (nRF_get_retransmitted_packets(nRF0) == 15)
		{
			printf("Dosli smo do maximalno retransmitanih paketa, izlazim\n");
			return;
		}
		printf("TX Still sending payload: %d\n", nRF_is_TX_data_sent(nRF0));

		static uint8_t counter;

		// za slucaj kad TX modul popizdi
		if (counter >= TX_TIMEOUT/TX_SINGLE_TIMEOUT)
		{
			printf("TX timeout, exiting\n");
			return;
		}
		delay_ms(TX_SINGLE_TIMEOUT);
		counter++;
	}
}


uint8_t nRF_RX_buffer[32];
/*************************************************************************************************
				nRF_read_payload()
*************************************************************************************************/
uint8_t *nRF_read_payload(nRF_hw_t *nRF0)
{
#define RX_TIMEOUT 60			// INFO max time before fail: retry counts * retry delay = 15 * 4ms = 60 ms
#define RX_SINGLE_TIMEOUT 10	// 10 ms
	// izgleda da nije potrebno rucno spustit CE

	uint8_t spi_port = nRF0->spi_port;

	while (nRF_is_RX_data_ready(nRF0) == 0)	// wait for receive to complete
	{
		static uint8_t counter;
		printf("RX still waiting for data, counter: %d\n", counter); 


		if (counter >= RX_TIMEOUT/RX_SINGLE_TIMEOUT)
		{
			printf("RX timeout, exiting\n");
			return NULL;
		}
		delay_ms(RX_SINGLE_TIMEOUT);
		counter++;
	}

	if (nRF_is_RX_data_ready(nRF0) == 1)		// there is something in RX FIFO
	{
		uint8_t pipe		 = nRF_get_payload_pipe(nRF0);
		uint8_t payload_size = nRF_get_payload_size(nRF0, pipe);

		printf("pipe: %d, payload_size: %d\n", pipe, payload_size);

		// reading RX FIFO
		cs(nRF0, 0);
		spi_rw(spi_port, CMD_R_RX_PAYLOAD);

		for (uint8_t i=0; i<payload_size; i++)
		{
			nRF_RX_buffer[i] = spi_rw(spi_port, CMD_NOP);
		}
		cs(nRF0, 1);

		// printing RF FIFO
		printf("Printamo buffer: \n\t\t\t\t\t");
		for (uint8_t i=0; i<payload_size; i++)
		{
			//printf("[%d]: %c %d\n", i, nRF_RX_buffer[i], nRF_RX_buffer[i]);
			printf("%c", nRF_RX_buffer[i]);
		}
		printf("\n");

		nRF_clear_bits(nRF0);
	}
	else
	{
		printf("No RX data\n");
	}

	return nRF_RX_buffer;
}


/*************************************************************************************************
				nRF_is_present()
*************************************************************************************************/
bool nRF_is_present(nRF_hw_t *nRF0)
{
	int8_t ret;

	uint8_t *needed_address = nRF0->rx_address[0];		// pipe0
	uint8_t *real_address 	= nRF_get_RX_address(nRF0);
	uint8_t length 			= nRF0->address_width;
	/*
	uint8_t *needed_address = 0;
	uint8_t *real_address 	= 0;
	uint8_t length 			= 0;
	*needed_address = nRF0->rx_address[0];		// pipe0
	*real_address 	= nRF_get_RX_address(nRF0);
	length 			= nRF0->address_width;
	*/

	printf("addr: %s, addr: %s, length: %d\n", needed_address, real_address, length);
	printf("addr: %p, addr: %p, length: %d\n", needed_address, real_address, length);

	if (real_address[0] == 0)	// za slucaj da je prazno polje
	{
		printf("zajeb\n");
		return 0;
	}

	if (length > 5)
	{
		return 0;
	}

	ret = memcmp(needed_address, real_address, length);	// XXX
	if (ret == 0)
	{
		DEBUG_INFO("nRF module is present\n");
		//printf("nRF module is present\n");
		return 1;
	}
	else
	{
		ERROR("nRF module is not present\n");
		printf("nRF module is not present\n");
		return 0;
	}
}

/*************************************************************************************************
				nRF_start_listening()
*************************************************************************************************/
void nRF_start_listening(nRF_hw_t *nRF0)
{
	// moglo bi se dodat i paljenje i set mode
	nRF_flush_TX(nRF0);
	nRF_flush_RX(nRF0);

	ce(nRF0, 1);
	delay_us(130);	// datasheet v1.0, page 76
}

/*************************************************************************************************
				nRF_stop_listening()
*************************************************************************************************/
void nRF_stop_listening(nRF_hw_t *nRF0)
{
	ce(nRF0, 0);

	nRF_flush_TX(nRF0);
	nRF_flush_RX(nRF0);
}
