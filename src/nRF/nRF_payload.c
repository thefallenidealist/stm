/*************************************************************************************************
				nRF_write_payload()
*************************************************************************************************/
//void nRF_write_payload(nRF_hw_t *nRF0, uint8_t *buffer, uint8_t length)
void nRF_write_payload(nRF_hw_t *nRF0, char *buffer, uint8_t length)
{
	// TODO max length 32 bytes
	uint8_t spi_port = nRF0->spi_port;

	// 150602 novo3,  moj pokusaj
  	// write payload
	cs(nRF0, 0);
	spi_rw(spi_port, CMD_W_TX_PAYLOAD);
	while (length--)
	{
		spi_rw(spi_port, *buffer++);
	}
	cs(nRF0, 1);

	// pulse CE for transmission
	ce(nRF0, 1);
	delay_us(11);	// 10+ us
	ce(nRF0, 0);

	/*
	The nRF24L01+ stays in TX mode until it finishes transmitting a packet. If CE = 0, nRF24L01+ returns to 
	standby-I mode. If CE = 1, the status of the TX FIFO determines the next action. If the TX FIFO is not 
	empty the nRF24L01+ remains in TX mode and transmits the next packet. If the TX FIFO is empty the 
	nRF24L01+ goes into standby-II mode. The nRF24L01+ transmitter PLL operates in open loop when in TX 
	mode. It is important never to keep the nRF24L01+ in TX mode for more than 4ms at a time. If the 
	Enhanced ShockBurst™ features are enabled, nRF24L01+ is never in TX mode longer than 4ms.
	*/
}

/*************************************************************************************************
				nRF_read_payload()
*************************************************************************************************/
bool nRF_read_payload(nRF_hw_t *nRF0)
{
	// novo 150602

	// provjeri RX_DR
	bool data_ready = nRF_is_RX_data_ready(nRF0);

	if (data_ready == 1)
	{
		// dobili smo nesta
		//nRF_stop_listening(nRF0);	// XXX no, no, razjebe se

		uint8_t spi_port 	 = nRF0->spi_port;
		uint8_t pipe		 = nRF_get_payload_pipe(nRF0);
		uint8_t payload_size = nRF_get_payload_size(nRF0, pipe);

		// reading RX FIFO
		cs(nRF0, 0);
		spi_rw(spi_port, CMD_R_RX_PAYLOAD);

		for (uint8_t i=0; i<payload_size; i++)
		{
			// zapisivanje u globalni buffer
			nRF_RX_buffer[i] = spi_rw(spi_port, CMD_NOP);
		}
		cs(nRF0, 1);

		/*
		// printing RF FIFO
		printf("Printamo RX buffer: ");
		for (uint8_t i=0; i<payload_size; i++)
		{
			//printf("[%d]: %c %d\n", i, nRF_RX_buffer[i], nRF_RX_buffer[i]);
			printf("%c", nRF_RX_buffer[i]);
		}
		printf("\n");

		// obrisi buffer
		for (uint8_t i=0; i<NRF_FIFO_SIZE; i++)
		{
			nRF_RX_buffer[i] = '\0';
		}
		*/

		//nRF_clear_bits(nRF0); // ocisti RX_DR, TX_DS, MAX_RT
		nRF_clear_RX_data_ready(nRF0);
		// INFO mora se pocistit inace se razjebat

		return 1;
	}
	else
	{
		//printf("Nothing received\n");
		return 0;
	}
}
