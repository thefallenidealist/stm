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




// TODO	
// ne koristit write_reg nego direktno SPI i zapisivat bit po bit i gotovo



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



	// power up
	write_reg(&primac, REG_CONFIG, (1 << PWR_UP) | (0 << PRIM_RX) | (1 << EN_CRC));
	delay_ms(2);	// 1.5ms
	// sad je u Standby-1 modu

	print_reg(&primac, REG_CONFIG);


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

	/*
	nRF_set_address_width(&primac, 5);
	uint8_t width = nRF_get_address_width(&primac);
	printf("nRF main: address width: %d\n", width);
	printf("address width: %d\n", primac.address_width);
	nRF_get_RX_address(&primac);	// zapise u objekt

	printf("address: \n");
	for (uint8_t i=0; i<primac.address_width; i++)
	{
		printf("[%d]: 0x%X\n", i, primac.address[0][i]);
	}
	*/
	
	// set RX address	
	// INFO kod postavljanja RX/TX addresa treba rucno pazit da se podudara, inace se skratit ili nesto gore
	nRF_set_address_width(&primac, 5);
	uint8_t rx_address[5] = {'a','b','c','d','e'};
	if (nRF_set_RX_address(&primac, rx_address))
	{
		printf("nRF set RX address error\n");
	}
	printf("nRF_get_RX_address return: %s\n", nRF_get_RX_address(&primac)); // nacin 2

	// set TX address
	uint8_t tx_address[5] = {'t','x','T','X','1'};
	if (nRF_set_TX_address(&primac, tx_address))
	{
		printf("nRF set TX address error\n");
	}
	printf("nRF_get_TX_address return: %s\n", nRF_get_TX_address(&primac)); // nacin 2

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

	nRF_disable_CRC(&primac);

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

	//print_reg(&primac, REG_RX_PW_P0);

	DEBUG_END;
}

/*************************************************************************************************
				nRF_enable_pipe()
*************************************************************************************************/
int8_t nRF_enable_pipe(nRF_hw_t *nRF0, pipe_t pipe)					// reg 0x02
{

	printf("%s(): argument: %d\n", __func__, pipe);

	// samo jednu po jednu XXX
	if (pipe > 5)
	{
		ERROR("Wrong pipe\n");
		return -1;
	}
	else
	{
		write_reg(nRF0, REG_EN_RXADDR, (1 << pipe));	// kad se enablea samo jedna
		//write_reg(nRF0, REG_EN_RXADDR, pipe + 1);	// +1 jer kad se omogucava pipe0, onda b0 = 1
		//write_reg(nRF0, REG_EN_RXADDR, (pipe << 1) + 1);
		return 0;
	}
}


/*************************************************************************************************
				nRF_enable_CRC()
*************************************************************************************************/
void nRF_enable_CRC(nRF_hw_t *nRF0)
{
	uint8_t spi_port = nRF0->spi_port;

	uint8_t old_value = read_reg(nRF0, REG_CONFIG);
	uint8_t new_value;

	//new_value = 


	/*
	cs(nRF0, 0);
	spi_rw(spi_port, REG_CONFIG + CMD_W_REGISTER);
	


	cs(nRF0, 1);
	*/
}

/*************************************************************************************************
				nRF_disable_CRC()
*************************************************************************************************/
void nRF_disable_CRC(nRF_hw_t *nRF0)
{
	uint8_t spi_port = nRF0->spi_port;

	uint8_t old_value = read_reg(nRF0, REG_CONFIG);
	uint8_t new_value;

	new_value = old_value & ~EN_CRC;

	printf("%s(): old: %d, new: %d\n", __func__, old_value, new_value);


	/*
	cs(nRF0, 0);
	spi_rw(spi_port, REG_CONFIG + CMD_W_REGISTER);
	


	cs(nRF0, 1);
	*/
}

/*
   TODO
   nRF_get_CRC_length
   nRF_set_CRC_length
   set_mode RX TX
   power_on
   power_off
   enable_auto_ACK(pipe_t pipe)		// po defaultu upaljeno za sve

   write_payload		
   */


void nRF_write_payload(nRF_hw_t *nRF0, uint8_t *buffer, uint8_t length)
{
	uint8_t spi_port = nRF0->spi_port;

	cs(nRF0, 0);

	spi_rw(spi_port, CMD_W_TX_PAYLOAD);
	while (length --)
	{
		spi_rw(spi_port, *buffer++);
	}

	cs(nRF0, 1);


}
