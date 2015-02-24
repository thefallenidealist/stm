#include "nRF.h"
#include "src/nRF/nRF_reg.h"

// TODO
// low: GPIO i SPI
// mid: operacije sa registrima
// high: set i get funkcije

// TODO const keyword gdje treba

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

	nRF_hw_t rf_tx;
	nRF_hw_t rf_rx;

	rf_tx.spi_port = 1;
	rf_rx.spi_port = 2;
	rf_tx.spi_prescaler = 32;
	rf_rx.spi_prescaler = 32;
	rf_tx.cs = "PA4";
	rf_rx.cs = "PB5";
	rf_tx.ce = "PA3";
	rf_rx.ce = "PB4";
	//rf_tx.irq = "";	// NC
	//rf_rx.irq = "PB3";	// NC

	//delay_ms(500);

	delay_ms(11);	// 10.3 ms		// power on delay
	if (nRF_hw_init(&rf_tx) != 0)
	{
		printf("RF_TX is not initialized\n");
		// return -1;
	}

	delay_ms(11);	// 10.3 ms		// power on delay
	if (nRF_hw_init(&rf_rx) != 0)
	{
		printf("RF_RX is not initialized\n");
		// return -1;
	}

	// write 1 to clear bits
	reg_tmp[RX_DR] = 1;
	reg_tmp[TX_DS] = 1;
	reg_tmp[MAX_RT] = 1;
	write_reg(&rf_rx, REG_STATUS);
	write_reg(&rf_tx, REG_STATUS);

	nRF_set_mode(&rf_tx, TX);
	nRF_set_mode(&rf_rx, RX);
	nRF_power_on(&rf_tx);
	nRF_power_on(&rf_rx);
	// XXX
	//nRF_set_retransmit_count(&rf_tx, 15);
	//nRF_set_retransmit_delay(&rf_tx, DELAY_1ms);
	write_reg_full(&rf_tx,  REG_SETUP_RETR, 255);
	write_reg_full(&rf_rx, REG_SETUP_RETR, 255);

	//nRF_set_retransmit_count(&rf_rx, 15);
	//nRF_set_retransmit_delay(&rf_rx, DELAY_1ms);
	nRF_set_address_width(&rf_tx,  5);
	nRF_set_address_width(&rf_rx, 5);
	nRF_set_channel(&rf_tx,  0);
	nRF_set_channel(&rf_rx, 0);
	nRF_set_output_power(&rf_tx,  power_0dBm);
	nRF_set_output_power(&rf_rx, power_0dBm);
	// moguce da radi
	//nRF_set_data_rate(&rf_tx, datarate_1Mbps);
	//nRF_set_data_rate(&rf_rx, datarate_1Mbps);

	write_reg_full(&rf_tx,  REG_RF_SETUP, 0b00000110);	// full power, don't care: 0, 1MBps
	write_reg_full(&rf_rx, REG_RF_SETUP, 0b00000110);	// full power, don't care: 0, 1MBps

	nRF_set_RX_payload_size(&rf_tx, P0, 3);
	nRF_set_RX_payload_size(&rf_rx, P0, 3);
	nRF_enable_pipe(&rf_tx, P0);
	nRF_enable_pipe(&rf_rx, P0);
	nRF_enable_CRC(&rf_tx);
	nRF_enable_CRC(&rf_rx);
	nRF_set_CRC_length(&rf_tx, CRC_LENGTH_2BTYE);
	nRF_set_CRC_length(&rf_rx, CRC_LENGTH_2BTYE);

	//nRF_set_RX_address(&rf_rx, "testA");
	//nRF_set_TX_address(&rf_tx, "testA");
	//uint8_t addr[5] = "abcde";
	uint8_t addr[5] = {};
	addr[0] = 'a';
	addr[1] = 'b';
	addr[2] = 'c';
	addr[3] = 'd';
	addr[4] = 'a';

	//nRF_set_TX_address(&rf_rx, addr);		// XXX vjerojatno ne treba, al da se proba
	nRF_set_RX_address(&rf_rx, addr);
	nRF_set_TX_address(&rf_tx, addr);
	nRF_set_RX_address(&rf_tx, addr);	// mora bit ista kao modulTX TX adresa zbog ACK
	printf("RF_RX address: %s\n", nRF_get_RX_address(&rf_rx));
	printf("RF_TX address:  %s\n", nRF_get_TX_address(&rf_tx));

	printf("RF_TX  datarate: %d\n", nRF_get_data_rate(&rf_tx));
	printf("RF_RX datarate: %d\n", nRF_get_data_rate(&rf_rx));

	// start RX
	ce(&rf_rx, 1);
	delay_us(130);

	printf("\n");
	printf("Registri, 1TX, 2RX\n");
	print_reg(&rf_tx,  0x00);
	print_reg(&rf_rx, 0x00);

	print_reg(&rf_tx,  0x01);
	print_reg(&rf_rx, 0x01);

	//print_reg(&rf_tx, 0x02);
	//print_reg(&rf_tx, 0x03);

	print_reg(&rf_tx,  0x04);
	print_reg(&rf_rx, 0x04);

	//print_reg(&rf_tx, 0x05);

	print_reg(&rf_tx,  0x06);
	print_reg(&rf_rx, 0x06);

	print_reg(&rf_tx,  0x07);
	print_reg(&rf_rx, 0x07);

	print_reg(&rf_tx,  0x08);
	print_reg(&rf_rx, 0x08);

	//print_reg(&rf_tx,  0x11);
	//print_reg(&rf_rx, 0x11);

	//print_reg(&rf_tx,  0x12);
	//print_reg(&rf_rx, 0x12);

	print_reg(&rf_tx,  0x0A);
	print_reg(&rf_rx, 0x0A);

	/*
	printf("\n");
	printf("\n");
	printf("RF_RX registri:\n");
	print_reg(&rf_rx, 0x02);
	print_reg(&rf_rx, 0x03);
	print_reg(&rf_rx, 0x05);
	*/
	printf("Is data sent: %d\n", nRF_is_TX_data_sent(&rf_tx));


	printf("\t\t\t\tSaljem teret\n");
	// write 1 to clear bits
	reg_tmp[RX_DR] = 1;		// mora bit odje, picka mu mater'na
	reg_tmp[TX_DS] = 1;
	reg_tmp[MAX_RT] = 1;
	write_reg(&rf_tx, REG_STATUS);

	nRF_TX_buffer[0] = 'x';
	nRF_TX_buffer[1] = 'y';
	nRF_TX_buffer[2] = 'z';
	nRF_write_payload(&rf_tx, 3);


	printf("Lost packets: %d\n", 			nRF_get_lost_packets(&rf_rx));
	printf("Retransmitted packets: %d\n", 	nRF_get_retransmitted_packets(&rf_rx));

	printf("\n");
	print_reg(&rf_tx, REG_CONFIG);
	printf("Is data sent: %d\n", nRF_is_TX_data_sent(&rf_tx));

	delay_ms(100);	// pricekaj da posalje
	ce(&rf_rx, 0);
	delay_ms(10);

	printf("RX data ready: %d\n", nRF_is_RX_data_ready(&rf_rx));

	printf("bit: MAX_RT: %d\n", nRF_get_bit(&rf_tx, REG_STATUS, MAX_RT));


	//				RX
	// already listening
	printf("Pipe u kojoj su podaci [ne smije bit 110 nit 111]: %d\n", read_reg(&rf_rx, REG_STATUS) >> 1 & 0b111);
	printf("Printamo buffer: \n");
	for (uint8_t i=0; i<3; i++)
	{
		printf("[%d]: %d %c\n", i, nRF_RX_buffer[i], nRF_RX_buffer[i]);
	}

	/*
	printf("DEBUG reg\n");
	for(uint8_t i=0; i<=0x17; i++)
	{
		print_reg(&rf_tx, i);
		print_reg(&rf_rx, i);
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


uint8_t nRF_TX_buffer[32];
/*************************************************************************************************
				nRF_write_payload()
*************************************************************************************************/
//void nRF_write_payload(nRF_hw_t *nRF0, uint8_t *buffer, uint8_t length)
void nRF_write_payload(nRF_hw_t *nRF0, uint8_t length)
{
	uint8_t spi_port = nRF0->spi_port;
	uint8_t *buffer = &nRF_TX_buffer[0];	// TODO not hardcoded
	//nRF_flush_TX(nRF0);	// in main()

	uint8_t debug_buffer[4] = {};
	uint8_t debug_length[4] = {};


	//printf("%s(): payload length: %d\n", __func__, length);

	reg_tmp[PWR_UP] = 1;
	reg_tmp[PRIM_RX] = 0;
	write_reg(nRF0, REG_CONFIG);
	delay_us(150);

	cs(nRF0, 0);

	//spi_rw(spi_port, *nRF_get_TX_address(nRF0));


	spi_rw(spi_port, CMD_W_TX_PAYLOAD);
	while (length--)
	{
		//static uint8_t i;
		//debug_buffer[i] = *buffer;
		//debug_length[i] = length;
		spi_rw(spi_port, *buffer++);
		//i++;
	}

	cs(nRF0, 1);

	// CE pulse for 10us
	ce(nRF0, 1);
	delay_us(11);
	ce(nRF0, 0);


	for (uint8_t i=0; i<10; i++)
	{
		uint8_t tx_ds = (read_reg(nRF0, REG_STATUS)) >> 5 & 1;
		uint8_t max_rt = (read_reg(nRF0, REG_STATUS)) >> 4 & 1;
		uint8_t ret_pkg = (read_reg(nRF0, REG_OBSERVE_TX));
		printf("TX_DS: %d \t MAX_RT: %d \t retransmitted packets: %d\n", tx_ds, max_rt, ret_pkg);
		delay_ms(5);
	}

	/*
	printf("%s(): payload length: %d trenutni buffer: %d [0,1,2]: %d %d %d\n", __func__, length, *buffer, nRF_TX_buffer[0], nRF_TX_buffer[1], nRF_TX_buffer[2]);
	for (uint8_t i=0; i<4; i++)
	{
		printf("length: %d, buffer: %d %c\n", debug_length[i], debug_buffer[i], debug_buffer[i]);
	}
	*/
}


/*************************************************************************************************
				nRF_read_payload()
*************************************************************************************************/
uint8_t nRF_RX_buffer[32];

uint8_t *nRF_read_payload(nRF_hw_t *nRF0, uint8_t howmany)
{
	if ( (howmany < 0) || (howmany > 32) )
	{
		ERROR("Wrong number of bytes to read\n");
		printf("Wrong number of bytes to read\n");

		return NULL;
	}

	//delay_us(130);	// neka se nadje
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

/*************************************************************************************************
				nRF_get_bit()
*************************************************************************************************/
uint8_t nRF_get_bit(nRF_hw_t *nRF0, uint8_t reg, uint8_t bit)
{
	//uint8_t spi_port = nRF0->spi_port;
	uint8_t status = read_reg(nRF0, reg);
	return (status >> bit) & 1;
}
