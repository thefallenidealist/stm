#include "nRF.h"
#include "src/nRF/nRF_reg.h"

// TODO const keyword gdje treba
// TODO svaka funkcija provjerava jel dobila NULL adresu

#include "src/nRF/nRF_hw_init.c"
#include "src/nRF/nRF_gpio.c"
#include "src/nRF/nRF_reg.c"
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
#include "src/nRF/nRF_address.c"
#include "src/nRF/nRF_payload_size.c"
#include "src/nRF/nRF_flush.c"
#include "src/nRF/nRF_observe_tx.c"
#include "src/nRF/nRF_crc.c"
#include "src/nRF/nRF_power.c"
#include "src/nRF/nRF_enable_pipe.c"
#include "src/nRF/nRF_mode.c"
#include "src/nRF/nRF_crc_length.c"
#include "src/nRF/nRF_payload.c"
#include "src/nRF/nRF_auto_ack.c"
#include "src/nRF/nRF_listening.c"
//#include "src/nRF/nRF_enhanced_shockburst.c"
#include "src/nRF/nRF_ack.c"
#include "src/nRF/nRF_feature.c"
#include "src/nRF/nRF_present.c"
#include "src/nRF/nRF_buffer.c"

// TODO payload_size i payload_width preimenova u payload_length da bude manje zbunjujuce


nRF_hw_t *grf = NULL;
const uint8_t addr[6] = "qwert";
//uint8_t addr_tx[5] = "addrT";
//uint8_t addr_rx[5] = "addrR";

/*************************************************************************************************
				nRF_main()
*************************************************************************************************/
int8_t nRF_main(void)
{
	// moj pokusaj
	printf("%s() kaze zdravo\n", __func__);

	static nRF_hw_t rf_modul;
	grf = &rf_modul;

	// hw init
	rf_modul.spi_port 	= NRF_SPI;
	rf_modul.spi_prescaler = NRF_SPI_PRESCALER;
	rf_modul.cs 		= NRF_CS;
	rf_modul.ce 		= NRF_CE;
	rf_modul.irq		= NRF_IRQ;


	if (nRF_hw_init(&rf_modul) != 0)
	{
		printf("RF module is not initialized\n");
		return -1;	// TODO not hardcoded
	}
	gpio_write(rf_modul.ce, 0);
	gpio_write(rf_modul.cs, 1);

	delay_ms(11);	// 10.3 ms		// power on delay
	delay_ms(100);	// datasheet page 22		Power on reset
	// ne pomazu dodatni delayi

	if (nRF_is_present(&rf_modul) == 0)
	{
		printf("%s(): Zajeb, nema nRF modula ili se uzjebo, izlazim.\n", __func__);
		while(1); 	// treba ga rucno fizicki resetirat (power toggle)
		//return -1;
	}

	nRF_set_output_power(&rf_modul, power_0dBm);
	nRF_set_datarate	(&rf_modul, datarate_1Mbps);
	//uint8_t payload_size = NRF_PAYLOAD_SIZE;
	//nRF_set_payload_size(&rf_modul, P0, payload_size);
	nRF_set_channel		(&rf_modul, 10);
	nRF_enable_pipe		(&rf_modul, P0);
	nRF_set_address_width(&rf_modul, NRF_ADDRESS_WIDTH);

#ifdef NRF_TX
	printf("Ovo je TX modul.\n");

	//char tx_addr[] = "aTX123";
	//nRF_set_TX_address	(&rf_modul, tx_addr);

	//nRF_set_TX_address	(&rf_modul, addr);
	//nRF_set_RX_address	(&rf_modul, P0, addr);
#endif
#ifdef NRF_RX
	printf("Ovo je RX modul.\n");
	//ce(&rf_modul, 1);	// start listening

	//char rx_addr[] = "aRX123";
	//nRF_set_RX_address	(&rf_modul, P0, rx_addr);

	//nRF_set_TX_address	(&rf_modul, addr);
	//nRF_set_RX_address	(&rf_modul, P0, addr);
	//nRF_set_RX_address	(&rf_modul, P1, addr);	// DYN ACK
#endif

	nRF_enable_CRC(&rf_modul);			// CRC is forced if AutoACK is enabled
	nRF_set_CRC_length(&rf_modul, CRC_LENGTH_2BTYE);
	nRF_enable_auto_ack(&rf_modul, P0);	// iako su po defaultu omogucene za sve pajpove

	nRF_set_retransmit_delay(&rf_modul, DELAY_1500us);	// ARD=500µs is long enough for any ACK payload length in 1 or 2Mbps mode.
	nRF_set_retransmit_count(&rf_modul, 15);			// 1 to 15 retries

	nRF_enable_dynamic_payload(&rf_modul);
	nRF_enable_dynamic_pipe(&rf_modul, P0);
	nRF_enable_dynamic_payload_ack(&rf_modul);

#ifdef NRF_TX
	nRF_set_mode(&rf_modul, TX);
#endif

#ifdef NRF_RX
	nRF_set_mode(&rf_modul, RX);
#endif
	/*
	nRF_clear_bits(&rf_modul);
	nRF_flush_TX(&rf_modul);
	nRF_flush_RX(&rf_modul);
	delay_ms(100);
	nRF_power_on(&rf_modul);
	*/

	nRF_debug(&rf_modul);
	delay_ms(1500);

	return 0;
}

void nRF_debug(nRF_hw_t *nRF0)
{
	printf("\n\n\t\t\t\t\t\t%s()\n", __func__);

	print_reg(nRF0, 0);
	print_reg(nRF0, 3);
	printf("nRF get address width: %d\n", nRF_get_address_width(nRF0));
	printf("nRF get retransmit delay: %d us\n", nRF_get_retransmit_delay_in_us(nRF0));
	printf("nRF get retransmit count: %d\n", nRF_get_retransmit_count(nRF0));
	printf("nRF get channel: %d\n", nRF_get_channel(nRF0));
	printf("nRF get datarate: %d\n", nRF_get_datarate(nRF0));
	printf("nRF get payload pipe: %d\n", nRF_get_payload_pipe(nRF0));
	nRF_print_enabled_pipe(nRF0);
	nRF_print_RX_address(nRF0, P0);
	nRF_print_RX_address(nRF0, P1);
	nRF_print_TX_address(nRF0);
	printf("nRF get payload size: %d\n", nRF_get_payload_size(nRF0, P0));
	printf("nRF get mode [0: TX, 1: RX]: %d\n", nRF_get_mode(nRF0));
	printf("nRF get CRC length: %d byte[s]\n", nRF_get_CRC_length(nRF0));

	printf("nRF_is_RX_data_ready: %d\n", nRF_is_RX_data_ready(nRF0));

	// DEBUG oprintaj sve registre
	for (int i=0; i<0x1E; i++)
	{
		print_reg(nRF0, i);
	}
}
