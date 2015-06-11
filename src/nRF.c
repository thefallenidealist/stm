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
#include "src/nRF/nRF_enhanced_shockburst.c"
#include "src/nRF/nRF_ack.c"
#include "src/nRF/nRF_feature.c"
#include "src/nRF/nRF_present.c"

// XXX jebena magija: veliki ARM sjebe nRF, osim ako se ne resetira lijevim prstenjakom
// TODO moguce rjesenje magije 100nF + 1-10uF C na Vcc i GND

// mora ici vamo jer se kompajlira modul po modul, nije sve jedan veliki main.c
#define NRF_SPI	1				// F1, F4

#ifdef STM32F1
	#define NRF_RX
	#define NRF_SPI_PRESCALER 32
	#define NRF_CS	"PB0"
	#define NRF_CE	"PB2"
	#define NRF_IRQ	"PB1"	// EXTI1
#endif
#ifdef STM32F4
	#define NRF_TX
	#define NRF_SPI_PRESCALER 64
	#define NRF_CS	"PA4"
	#define NRF_CE	"PA3"
	#define NRF_IRQ	"PA5"	// XXX, NC, treba lemit
#endif

uint8_t addr[5] = "qwert";
uint8_t addr_tx[5] = "addrT";
uint8_t addr_rx[5] = "addrR";

nRF_hw_t rf_modul;
nRF_hw_t *grf = &rf_modul;

char nRF_TX_buffer[NRF_FIFO_SIZE] = {};
char nRF_RX_buffer[NRF_FIFO_SIZE] = {};

/*
void nrf_check(void)
{
#ifdef NRF_TX
	while (nRF_is_TX_data_sent(grf) == 0)
	{
		if (nRF_get_retransmitted_packets(grf) == 15)
		{
			printf("Dosli smo do maximalno retransmitanih paketa, izlazim\n");
			return;
		}
		printf("TX Still sending payload: %d\n", nRF_is_TX_data_sent(grf));

		static uint8_t counter;

		delay_ms(TX_SINGLE_TIMEOUT);
		counter++;
	}
#endif
}
*/


/*************************************************************************************************
				nRF_main()
*************************************************************************************************/
int8_t nRF_main(void)
{
	// moj pokusaj
	printf("%s() kaze zdravo\n", __func__);
	//uint8_t payload_size = NRF_PAYLOAD_SIZE;

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

	if (nRF_is_present(&rf_modul) == 0)
	{
		printf("%s(): Zajeb, nema nRF modula ili se uzjebo, izlazim.\n", __func__);
		while(1); 	// treba ga rucno fizicki resetirat (power toggle)
		//return -1;
	}

#ifdef NRF_TX
	nRF_set_mode(&rf_modul, TX);
#endif
#ifdef NRF_RX
	nRF_set_mode(&rf_modul, RX);
#endif
	if (nRF_get_mode(&rf_modul) == RX)
	{
		printf("Ovo je RX modul.\n");
	}
	else if (nRF_get_mode(&rf_modul) == TX)
	{
		printf("Ovo je TX modul.\n");
	}
	else
	{
		printf("Krivi mod: %d\n", rf_modul.mode);
	}

	nRF_set_channel		(&rf_modul, 1);
	nRF_set_datarate	(&rf_modul, datarate_2Mbps);
	nRF_set_output_power(&rf_modul, power_0dBm);
	nRF_enable_pipe		(&rf_modul, P0);
	nRF_enable_pipe		(&rf_modul, P1);
	/*
	//nRF_enable_pipe		(&rf_modul, P2);
	//nRF_enable_pipe		(&rf_modul, P3);
	nRF_enable_pipe		(&rf_modul, P4);
	nRF_enable_pipe		(&rf_modul, P5);
	*/
	nRF_enable_auto_ack	(&rf_modul, P0);
	nRF_enable_auto_ack	(&rf_modul, P1);
	/*
	nRF_enable_auto_ack	(&rf_modul, P2);
	nRF_enable_auto_ack	(&rf_modul, P3);
	nRF_enable_auto_ack	(&rf_modul, P4);
	nRF_enable_auto_ack	(&rf_modul, P5);
	*/
	nRF_enable_dynamic_payload	(&rf_modul);
	nRF_enable_dynamic_pipe		(&rf_modul, P0);
	nRF_enable_dynamic_pipe		(&rf_modul, P1);

	/*
	delay_ms(10);
	printf("\t\t idemo provjerit jel stvarno uspjelo\n");
	print_reg(&rf_modul, REG_FEATURE);
	print_reg(&rf_modul, REG_DYNPD);
	*/

	nRF_set_CRC_length	(&rf_modul, CRC_LENGTH_1BTYE);
	nRF_set_retransmit_delay(&rf_modul, DELAY_500us);
	nRF_set_retransmit_count(&rf_modul, 15);


	uint8_t mode = nRF_get_mode(&rf_modul);
	if (mode == TX)
	{
		nRF_set_TX_address	(&rf_modul, addr_tx);
		nRF_set_RX_address	(&rf_modul, P1, addr_rx);
	}
	else if (mode == RX)
	{
		nRF_set_TX_address	(&rf_modul, addr_rx);	// salje na adresi na kojoj TX slusa
		nRF_set_RX_address	(&rf_modul, P1, addr_tx);	// slusa na adresi na kojoj TX salje
	}
	nRF_power_on(&rf_modul);

	nRF_debug(&rf_modul);
	delay_s(3);
	return 0;	// bezveze
}

// TODO nRF_send_payload_wait_ack()

void nRF_debug(nRF_hw_t *nRF0)
{
	printf("\n\n\t\t\t\t\t\t%s()\n", __func__);


	/*
	printf("nRF pipe0 payload size: %d\n", 	nRF_get_payload_size(nRF0, 0));
	printf("nRF_is_RX_data_ready: %d\n", nRF_is_RX_data_ready(nRF0));
	printf("nRF_is_RX_data_ready: %d\n", nRF_is_RX_data_ready(nRF0));
	*/

	print_reg(nRF0, 0);
	print_reg(nRF0, 3);
	printf("nRF get address width: %d\n", nRF_get_address_width(nRF0));
	printf("nRF get retransmit delay: %d us\n", nRF_get_retransmit_delay_in_us(nRF0));
	printf("nRF get retransmit count: %d\n", nRF_get_retransmit_count(nRF0));
	printf("nRF get channel: %d\n", nRF_get_channel(nRF0));
	printf("nRF get datarate: %d\n", nRF_get_datarate(nRF0));
	printf("nRF get payload pipe: %d\n", nRF_get_payload_pipe(nRF0));
	//printf("nRF get enabled pipe: %d\n", nRF_get_enabled_pipe(nRF0));
	nRF_print_enabled_pipe(nRF0);

	nRF_print_RX_address(nRF0, P0);
	nRF_print_RX_address(nRF0, P1);
	nRF_print_TX_address(nRF0);
	printf("nRF get payload size: %d\n", nRF_get_payload_size(nRF0, P0));
	printf("nRF get mode [0: TX, 1: RX]: %d\n", nRF_get_mode(nRF0));
	printf("nRF get CRC length: %d byte[s]\n", nRF_get_CRC_length(nRF0));

	printf("nRF_is_RX_data_ready: %d\n", nRF_is_RX_data_ready(nRF0));

	// DEBUG oprintaj koji registar
	for (int i=0; i<0x1E; i++)
	{
		print_reg(nRF0, i);
	}

	printf("nRF pipe0 payload size: %d\n", 	nRF_get_payload_size(nRF0, P0));
	printf("nRF get dynamic payload length: %d\n", nRF_get_dynamic_payload_length(nRF0, P0));

}
