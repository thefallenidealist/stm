#include "nRF.h"
#include "src/nRF/nRF_reg.h"

// TODO const keyword gdje treba
// TODO svaka funkcija provjerava jel dobila NULL adresu

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
#include "src/nRF/nRF_payload.c"
#include "src/nRF/nRF_auto_ack.c"
#include "src/nRF/nRF_listening.c"
#include "src/nRF/nRF_enhanced_shockburst.c"
#include "src/nRF/nRF_ack.c"
#include "src/nRF/nRF_feature.c"

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

nRF_hw_t rf_modul;
nRF_hw_t *grf = &rf_modul;

char nRF_TX_buffer[NRF_FIFO_SIZE] = {};
char nRF_RX_buffer[NRF_FIFO_SIZE] = {};

/*************************************************************************************************
				nRF_is_present()
*************************************************************************************************/
bool nRF_is_present(nRF_hw_t *nRF0)
{
	return 0;
}

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
	uint8_t payload_size = NRF_PAYLOAD_SIZE;

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
	// end of hw init

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

	nRF_set_output_power(&rf_modul, power_0dBm);
	nRF_set_datarate	(&rf_modul, datarate_2Mbps);
	//nRF_set_payload_size(&rf_modul, 0, payload_size);
	nRF_set_channel		(&rf_modul, 0);
	nRF_enable_pipe		(&rf_modul, 0);
	nRF_set_address_width(&rf_modul, NRF_ADDRESS_WIDTH);

	uint8_t mode = nRF_get_mode(&rf_modul);
	if (mode == TX)
	{
		nRF_set_TX_address	(&rf_modul, addr);
		nRF_set_RX_address	(&rf_modul, addr);
		// TX modul treba i RX adresu zbog ACK
	}
	else if (mode == RX)
	{
		nRF_set_RX_address	(&rf_modul, addr);
	}

	printf("RF_TX address: %s\n", nRF_get_TX_address(&rf_modul));
	printf("RF_RX address: %s\n", nRF_get_RX_address(&rf_modul));

	// CRC is forced if AutoACK is enabled
	nRF_enable_CRC(&rf_modul);
	nRF_set_CRC_length(&rf_modul, CRC_LENGTH_1BTYE);

#ifdef NRF_TX
	nRF_enable_auto_ack(&rf_modul, P0);	// iako su po defaultu omogucene za sve pajpove

	// ARD=500µs is long enough for any ACK payload length in 1 or 2Mbps mode.
	nRF_set_retransmit_delay(&rf_modul, DELAY_500us);
	nRF_set_retransmit_count(&rf_modul, 15);	// 1 to 15 retries

	nRF_power_on(&rf_modul);
	ce(&rf_modul, 0);	// nije RX, ne slusa
	// ce je po defaultu vec nula, al ajde
#endif

#ifdef NRF_RX
	nRF_power_on(&rf_modul);
	nRF_start_listening(&rf_modul);
#endif


	nRF_debug(&rf_modul);


}

// TODO nRF_send_payload_wait_ack()

void nRF_debug(nRF_hw_t *nRF0)
{

	printf("nRF pipe0 payload size: %d\n", 	nRF_get_payload_size(nRF0, 0));
	printf("nRF_is_RX_data_ready: %d\n", nRF_is_RX_data_ready(nRF0));
	printf("nRF_is_RX_data_ready: %d\n", nRF_is_RX_data_ready(nRF0));

	printf("nRF get address width: %d\n", nRF_get_address_width(nRF0));
	printf("nRF get retransmit delay: %d\n", nRF_get_retransmit_delay(nRF0));
	printf("nRF get retransmit count: %d\n", nRF_get_retransmit_count(nRF0));
	printf("nRF get channel: %d\n", nRF_get_channel(nRF0));
	printf("nRF get datarate: %d\n", nRF_get_datarate(nRF0));
	printf("nRF get payload pipe: %d\n", nRF_get_payload_pipe(nRF0));
	printf("nRF get pipe: %d\n", nRF_get_enabled_pipe(nRF0));

	printf("nRF get RX address: %s\n", nRF_get_RX_address(nRF0));	// ptr
	printf("nRF get TX address: %s\n", nRF_get_TX_address(nRF0));	// ptr
	printf("nRF get payload size: %d\n", nRF_get_payload_size(nRF0, 0));
	printf("nRF get mode [0: TX, 1: RX]: %d\n", nRF_get_mode(nRF0));
	printf("nRF get CRC length: %d\n", nRF_get_CRC_length(nRF0));

	printf("nRF pipe0 payload size: %d\n", 	nRF_get_payload_size(nRF0, 0));
	printf("nRF_is_RX_data_ready: %d\n", nRF_is_RX_data_ready(nRF0));

	// DEBUG oprintaj koji registar
	for (int i=0; i<0x1E; i++)
	{
		print_reg(nRF0, i);
	}

	printf("idemo omogucit dynamic payload\n");
	nRF_enable_dynamic_pipe(nRF0, P0);

	print_reg(nRF0, REG_FEATURE);
	print_reg(nRF0, REG_EN_AA);
	print_reg(nRF0, REG_DYNPD);
}
