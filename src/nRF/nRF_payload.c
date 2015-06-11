/*************************************************************************************************
				nRF_write_payload()
*************************************************************************************************/
void nRF_write_payload(nRF_hw_t *nRF0, char *buffer, uint8_t length)
{
	// INFO
	// moguce mu rec da flusha TX tako da u slucaju da je pokusao prosli paket poslat maksimalno
	// puta i nije uspio... posalje novi bez explicitnog flushanja iz main()
	// nRF_flush_TX(nRF0);


	if (length > 32)
	{
		printf("%s(): Zajeb, length (%d) larger than 32, exiting\n", __func__, length);
		return;
	}

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

	/*
	   nakon slanja paketa ne radi nista 130us
	   onda se presalta u RX mode i ocekuje ACK
	   			page 	45
	   */
}

/*************************************************************************************************
				nRF_read_payload()
*************************************************************************************************/
bool nRF_read_payload(nRF_hw_t *nRF0)
{
	// novo 150602

	//bool data_ready = nRF_is_RX_data_ready(nRF0);	// provjeri RX_DR

	//if (data_ready == 1)	// dobili smo nesta
	{
		uint8_t spi_port 	 = nRF0->spi_port;
		uint8_t pipe		 = nRF_get_payload_pipe(nRF0);			// provjeri u kojem pajpu je teret
		uint8_t payload_size = nRF_get_payload_size(nRF0, pipe);	// provjeri koliko je velik teret
				// vjerojatno nije potrebno ako nije dynamic payload, al neka se nadje

		// reading RX FIFO
		cs(nRF0, 0);
		spi_rw(spi_port, CMD_R_RX_PAYLOAD);

		printf("%s(): pipe: %d, size: %d\n\t\t", __func__, pipe, payload_size);

		for (uint8_t i=0; i<payload_size; i++)
		{
			// zapisivanje u globalni buffer
			nRF_RX_buffer[i] = spi_rw(spi_port, CMD_NOP);
			// DEBUG idemo oprintat
			printf("%c ", nRF_RX_buffer[i]);
		}
		cs(nRF0, 1);
		printf("\n");

		//nRF_clear_bits(nRF0); // ocisti RX_DR, TX_DS, MAX_RT
		nRF_clear_RX_data_ready(nRF0); // INFO mora se pocistit inace se razjebat


		return 1;
	}
	/*
	else
	{
		//printf("Nothing received\n");
		return 0;
	}
	*/
}





/*************************************************************************************************
				nRF_write()
*************************************************************************************************/
void nRF_write(nRF_hw_t *nRF0, char *buffer, uint8_t length)
{
	// kao pametniji write_payload gdje pokusava vise puta poslat i stalno provjerava jel poslano

	nRF_stop_listening(nRF0);

	reg_tmp[PWR_UP] = 1;
	reg_tmp[PRIM_RX] = 0;
	delay_us(150);	// 130
	nRF_write_payload(nRF0, buffer, length);

	uint8_t  ARC = nRF_get_retransmit_count(nRF0);
	uint16_t ARD = nRF_get_retransmit_delay_in_us(nRF0);
	uint32_t timeout_us = ARC*ARD;
	/*
	printf("\t\t ARC: %d\n", nRF_get_retransmit_count(nRF0));
	printf("\t\t ARD: %d us\n", nRF_get_retransmit_delay_in_us(nRF0));
	printf("\t\t REG_SETUP_RETR: ");
	print_reg(nRF0, REG_SETUP_RETR);
	*/
	
	// cekaj na ACK ili da posalje maksimalni broj puta
	uint32_t sent_at = get_uptime_us();
	do
	{
		printf("%s(): Jos uvijek se salje paket, uptime_us: %ld\n", __func__, get_uptime_us());
		//printf("%s(): get_uptime_us(): %ld - sent_at: %ld < timeout_us: %ld\n", __func__, get_uptime_us(), sent_at, timeout_us);
	}
	// treba radit sve dok nije poslao		ili		sve dok nije ispucao sanse		ili 	timeouto
	while ( !((nRF_is_TX_data_sent(nRF0) == 1) || (nRF_is_TX_data_failed(nRF0) == 1) || (get_uptime_us() - sent_at > timeout_us)));

	// ili je poslao ili fejlao
	if (nRF_is_TX_data_sent(nRF0) == 1)
	{
		printf("%s(): TX_DS Paket je poslan\n", __func__);
	}
	else if (nRF_is_TX_data_failed(nRF0) == 1)
	{
		printf("%s(): MAX_RT: %d Maksimalno se potrudio i svejedno fejlao\n", __func__, nRF_get_retransmit_count(nRF0));
		nRF_clear_bits(nRF0);
	}
	else if (nRF_is_RX_data_ready(nRF0) == 1)
	{
		uint8_t length = nRF_get_dynamic_payload_length(nRF0, P0);		// XXX hardcoded pipe0
		printf("%s(): RX_DR Izgleda da smo dobili ACK, duzina: %d\n", __func__, length);
	}
	else
	{
		printf("%s(): Timeout od %d us se dogodio pa je ovaj iziso, zadani timeout: %d\n", __func__,
				get_uptime_us()-sent_at, timeout_us);
	}

	// power_down
}
