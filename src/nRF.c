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

// mora ici vamo jer se kompajlira modul po modul, nije sve jedan veliki main.c
#define NRF_SPI	1				// F1, F4

#ifdef STM32F1
		#define NRF_RX
		//#define NRF_TX
	#define NRF_SPI_PRESCALER 32
	#define NRF_CS	"PB0"
	#define NRF_CE	"PB2"
	#define NRF_IRQ	"PB1"	// EXTI1
#endif
#ifdef STM32F4
		#define NRF_TX
		//#define NRF_RX
	#define NRF_SPI_PRESCALER 64
	#define NRF_CS	"PA4"
	#define NRF_CE	"PA3"
	#define NRF_IRQ	"PA5"	// XXX, NC, treba lemit
#endif

uint8_t addr[5] = "qwert";
#define NRF_ADDRESS_WIDTH	5

nRF_hw_t rf_modul;
nRF_hw_t *grf = &rf_modul;

#include "src/nRF/nRF_payload.c"

/*************************************************************************************************
				nRF_is_present()
*************************************************************************************************/
bool nRF_is_present(nRF_hw_t *nRF0)
{
	return 0;
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

void nrf_main10(void)
{




}

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


/*************************************************************************************************
				nRF_main()
*************************************************************************************************/
uint8_t nRF_TX_buffer[32];
uint8_t nRF_RX_buffer[32];

void nrf_main20(void)
{
	// moj pokusaj
	printf("%s() kaze zdravo\n", __func__);
	uint8_t payload_size = 8;

	// popuni buffere
	for (int i=0; i<32; i++)
	{
		nRF_TX_buffer[i] = 'a' + i;
		nRF_RX_buffer[i] = 0;
	}


	// hw init
	rf_modul.spi_port 	= NRF_SPI;
	rf_modul.spi_prescaler = NRF_SPI_PRESCALER;
	rf_modul.cs 		= NRF_CS;
	rf_modul.ce 		= NRF_CE;
	rf_modul.irq		= NRF_IRQ;

	delay_ms(11);	// 10.3 ms		// power on delay

	if (nRF_hw_init(&rf_modul) != 0)
	{
		printf("RF module is not initialized\n");
		 //return -1;
	}
	gpio_write(rf_modul.ce, 0);
	gpio_write(rf_modul.cs, 1);

	delay_ms(50);	// mirf tako kaze
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
	nRF_set_datarate	(&rf_modul, datarate_1Mbps);
	nRF_set_payload_size(&rf_modul, 0, payload_size);
	nRF_set_channel		(&rf_modul, 0);

	nRF_enable_pipe(&rf_modul, 0);
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


#ifdef NRF_TX
	// RF_WriteRegister(RF24_EN_AA, RF24_EN_AA_ENAA_P0); /* enable auto acknowledge. RX_ADDR_P0 needs to be equal to TX_ADDR! */
	// TODO u posebnu funkciju
	//write_reg(&rf_modul, (1 << ENAA_P0);	
	reg_tmp[ENAA_P0] = 1;
	write_reg(&rf_modul, REG_EN_AA);

	// RF_WriteRegister(RF24_SETUP_RETR, RF24_SETUP_RETR_ARD_750|RF24_SETUP_RETR_ARC_15); /* Important: need 750 us delay between every retry */
	nRF_set_retransmit_delay(&rf_modul, DELAY_750us);
	nRF_set_retransmit_count(&rf_modul, 15);
	// TX_POWERUP();  /* Power up in transmitting mode */
	// #define TX_POWERUP()   RF_WriteRegister(RF24_CONFIG, RF24_EN_CRC|RF24_CRCO|RF24_PWR_UP|RF24_PRIM_TX) /* enable 2 byte CRC, power up and set as PTX */
	nRF_enable_CRC(&rf_modul);
	nRF_set_CRC_length(&rf_modul, CRC_LENGTH_2BTYE);
	nRF_set_mode(&rf_modul, PTX);
	reg_tmp[PWR_UP] = 1;
	write_reg(&rf_modul, REG_CONFIG);
	delay_ms(2);

	ce(&rf_modul, 0);	// nije RX, ne slusa
#endif

#ifdef NRF_RX
	nRF_enable_CRC(&rf_modul);
	nRF_set_CRC_length(&rf_modul, CRC_LENGTH_2BTYE);
	nRF_set_mode(&rf_modul, PRX);
	reg_tmp[PWR_UP] = 1;
	write_reg(&rf_modul, REG_CONFIG);
	delay_ms(2);

	nRF_start_listening(&rf_modul);
#endif


	/*
	printf("nRF pipe0 payload size: %d\n", 	nRF_get_payload_size(grf, 0));
	printf("nRF_is_RX_data_ready: %d\n", nRF_is_RX_data_ready(grf));
	printf("nRF_is_RX_data_ready: %d\n", nRF_is_RX_data_ready(&rf_modul));

	printf("nRF address width: %d\n", nRF_get_address_width(grf));
	printf("nRF get retransmit delay: %d\n", nRF_get_retransmit_delay(grf));
	printf("nRF get retransmit count: %d\n", nRF_get_retransmit_count(grf));
	printf("nRF get channel: %d\n", nRF_get_channel(grf));
	printf("nRF get datarate: %d\n", nRF_get_datarate(grf));
	printf("nRF get payload pipe: %d\n", nRF_get_payload_pipe(grf));
	printf("nRF get pipe: %d\n", nRF_get_pipe(grf));

	printf("nRF get RX address: %s\n", nRF_get_RX_address(grf));	// ptr
	printf("nRF get TX address: %s\n", nRF_get_TX_address(grf));	// ptr
	printf("nRF get payload size: %d\n", nRF_get_payload_size(grf, 0));
	printf("nRF get mode [0: TX, 1: RX]: %d\n", nRF_get_mode(grf));
	printf("nRF get CRC length: %d\n", nRF_get_CRC_length(grf));

	printf("nRF pipe0 payload size: %d\n", 	nRF_get_payload_size(grf, 0));
	delay_ms(500);
	printf("nRF_is_RX_data_ready: %d\n", nRF_is_RX_data_ready(&rf_modul));
	*/











	// DEBUG oprintaj koji registar
	for (int i=0; i<12; i++)
	{
		print_reg(&rf_modul, i);
	}
	print_reg(&rf_modul, 0x11);
}
