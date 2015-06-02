/*************************************************************************************************
				nRF_write_payload()
*************************************************************************************************/
void nRF_write_payload(nRF_hw_t *nRF0, uint8_t *buffer, uint8_t length)
{
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

	// start transmission
	ce(nRF0, 1);
	delay_us(15);
	// end transmission
	ce(nRF0, 0);
}

/*************************************************************************************************
				nRF_read_payload()
*************************************************************************************************/
//uint8_t *nRF_read_payload(nRF_hw_t *nRF0)
bool nRF_read_payload(nRF_hw_t *nRF0)
{
	// novo 150602

	// provjeri RX_DR
	bool data_ready = nRF_is_RX_data_ready(nRF0);
	//printf("%s(): RX data ready: %d\n", __func__, data_ready);

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
			// zapisivanje u globalni buffer
			nRF_RX_buffer[i] = spi_rw(spi_port, CMD_NOP);
		}
		cs(nRF0, 1);

		// printing RF FIFO
		printf("Printamo RX buffer: ");
		for (uint8_t i=0; i<payload_size; i++)
		{
			//printf("[%d]: %c %d\n", i, nRF_RX_buffer[i], nRF_RX_buffer[i]);
			printf("%c", nRF_RX_buffer[i]);
		}
		printf("\n");

		//nRF_clear_bits(nRF0); // ocisti RX_DR, TX_DS, MAX_RT
		nRF_clear_RX_data_ready(nRF0);
		// INFO mora se pocistit inace se razjebat

		return 1;
	}
	else
	{
		printf("Nothing received\n");
		return 0;
	}

	//print_reg(grf, 0x00);
	//print_reg(grf, REG_STATUS);
}
