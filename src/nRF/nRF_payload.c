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







	/*
	nRF_flush_TX(nRF0);	

	cs(nRF0, 0);
	spi_rw(spi_port, CMD_W_TX_PAYLOAD);
	while (length--)
	{
		spi_rw(spi_port, *buffer++);
	}
	cs(nRF0, 1);

	// CE pulse for 10us to send payload
	ce(nRF0, 1);
	//delay_us(10);
	delay_us(15);
	ce(nRF0, 0);
	*/





	/*
	// vjerojatno bolje u posebnoj funkciji
	while (nRF_is_TX_data_sent(nRF0) == 0)
	{
		if (nRF_get_retransmitted_packets(nRF0) == 15)
		{
			printf("Dosli smo do maximalno retransmitanih paketa, izlazim\n");
			return;
		}
		printf("TX Still sending payload: %d\n", nRF_is_TX_data_sent(nRF0));

		static uint8_t counter;
		*/

		/*
		// za slucaj kad TX modul popizdi
		if (counter >= TX_TIMEOUT/TX_SINGLE_TIMEOUT)
		{
			printf("TX timeout, exiting\n");
			return;
		}
		*/
	/*
		delay_ms(TX_SINGLE_TIMEOUT);
		counter++;
	}
*/


	// 150602 novo
	/*
	// flush old data
	nRF_flush_TX(nRF0);
  	// write payload
  	// RF_WriteRegisterData(RF24_W_TX_PAYLOAD, payload, payloadSize); // write payload 
	cs(nRF0, 0);
	spi_rw(spi_port, CMD_W_TX_PAYLOAD);
	while (length--)
	{
		spi_rw(spi_port, *buffer++);
	}
	cs(nRF0, 1);

	// start transmission
	ce(nRF0, 1);
	delay_us(15);
	// end transmission
	ce(nRF0, 0);
	*/

	// 150602 novo2, mirf
  	// write payload
	cs(nRF0, 0);
	spi_rw(spi_port, CMD_W_TX_PAYLOAD);
	while (length--)
	{
		spi_rw(spi_port, *buffer++);
	}
	cs(nRF0, 1);

	/*
	// start transmission
	ce(nRF0, 1);
	delay_us(15);
	// end transmission
	ce(nRF0, 0);
	*/

	// 150602 novo3,  moj pokusaj
  	// write payload
	cs(nRF0, 0);
	spi_rw(spi_port, CMD_W_TX_PAYLOAD);
	while (length--)
	{
		spi_rw(spi_port, *buffer++);
	}
	cs(nRF0, 1);

	// start transmission
	ce(nRF0, 1);
	delay_us(15);
	// end transmission
	ce(nRF0, 0);
}

/*************************************************************************************************
				nRF_read_payload()
*************************************************************************************************/
uint8_t *nRF_read_payload(nRF_hw_t *nRF0)
{
	/*
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
	*/

	// novo 150602
	/*
	if (status&RF24_STATUS_RX_DR) { // data received interrupt 
		RF_RxPayload(payload, sizeof(payload)); // will reset RX_DR bit 
		RF_ResetStatusIRQ(RF24_STATUS_RX_DR|RF24_STATUS_TX_DS|RF24_STATUS_MAX_RT); // make sure we reset all flags. Need to have the pipe number too 
	}
	*/

	// provjeri RX_DR
	bool data_ready = nRF_is_RX_data_ready(grf);
	printf("%s(): RX data ready: %d\n", __func__, data_ready);

	if (data_ready == 1)
	{
		// dobili smo nesta
		uint8_t spi_port 	 = nRF0->spi_port;
		uint8_t pipe		 = nRF_get_payload_pipe(nRF0);
		uint8_t payload_size = nRF_get_payload_size(nRF0, pipe);
		// reading RX FIFO
		cs(nRF0, 0);
		spi_rw(spi_port, CMD_R_RX_PAYLOAD);

		for (uint8_t i=0; i<payload_size; i++)
		{
			nRF_RX_buffer[i] = spi_rw(spi_port, CMD_NOP);
		}
		cs(nRF0, 1);

		// printing RF FIFO
		printf("Printamo RX buffer: \n\t\t\t\t\t");
		for (uint8_t i=0; i<payload_size; i++)
		{
			printf("[%d]: %c %d\n", i, nRF_RX_buffer[i], nRF_RX_buffer[i]);
			//printf("%c", nRF_RX_buffer[i]);
		}
		printf("\n");

		nRF_clear_bits(nRF0);
	}

	//print_reg(grf, REG_STATUS);
}
