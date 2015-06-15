/*************************************************************************************************
				nRF_read_RX_FIFO
*************************************************************************************************/
static inline void nRF_read_RX_FIFO(nRF_hw_t *nRF0, uint8_t payload_size)
{
	uint8_t spi_port 	= nRF0->spi_port;
	char    *buffer		= nRF0->RX_buffer;

	cs(nRF0, 0);
	spi_rw(spi_port, CMD_R_RX_PAYLOAD);

	for (uint8_t i=0; i<payload_size; i++)
	{
		buffer[i] = spi_rw(spi_port, CMD_NOP);
	}
	cs(nRF0, 1);
	buffer[payload_size] = '\0';	// neka se nadje
}

/*************************************************************************************************
				nRF_write_TX_FIFO()
*************************************************************************************************/
static inline void nRF_write_TX_FIFO(nRF_hw_t *nRF0, char *buffer, uint8_t length, bool dynamic_payload, uint8_t empty_payload)
{
	uint8_t spi_port = nRF0->spi_port;

  	// write payload
	cs(nRF0, 0);
	spi_rw(spi_port, CMD_W_TX_PAYLOAD);
	while (length--)
	{
		spi_rw(spi_port, *buffer++);
	}
	if (dynamic_payload == 0)
	{
		// ako buffer ima manje bajtova, popuni sa praznima
		while (empty_payload--)
		{
			spi_rw(spi_port, ' ');
		}
	}
	cs(nRF0, 1);

	// pulse CE for transmission
	ce(nRF0, 1);
	delay_us(11);	// 10+ us
	ce(nRF0, 0);
}

/*************************************************************************************************
				nRF_write_payload()
*************************************************************************************************/
static inline void nRF_write_payload(nRF_hw_t *nRF0, char *buffer, uint8_t length)
{
	uint8_t payload_length = 0;
	uint8_t empty_payload_length = 0;
	bool	dynamic_payload_enabled = nRF_is_dynamic_payload_enabled(nRF0);	// da samo jednom pozove funkciju

	if (length > 32)
	{
		// pipe maksimalno moze imat 32 znaka
		printf("%s(): Zajeb, length (%d) larger than 32, exiting\n", __func__, length);
		return;
	}

	if (dynamic_payload_enabled == 1)
	{
		payload_length = length;
	}
	else	// static length payload
	{
		payload_length = nRF_get_payload_size(nRF0, P0);	// TODO not hardcoded pipe

		if (length > payload_length)
		{
			// ako je kao arugment dobio duzinu manju od 32, ali vecu od pipe length, onda skrati length
			length = payload_length;
		}
		else if (length < payload_length)
		{
			// ako je kao argument dobio kracu duzinu od pipe length, tad ostatak treba bit prazni teret
			empty_payload_length = payload_length - length;
		}
	}
	nRF_write_TX_FIFO(nRF0, buffer, length, dynamic_payload_enabled, empty_payload_length);
}

/*************************************************************************************************
				nRF_read()
*************************************************************************************************/
bool nRF_read(nRF_hw_t *nRF0)
{
	//uint8_t spi_port 	 = nRF0->spi_port;
	uint8_t payload_size = 1;
	uint8_t pipe = 0xFF;
	char *buffer = nRF0->RX_buffer;

	if (nRF_is_TX_empty(nRF0) == 1)
	{
		// nemoj zapunit FIFO ako ne dobiva pakete
		nRF_write_ack(nRF0);	// kao prepare ACK, on ce ga automatski poslat kad dobije paket
	}

	bool data_ready = nRF_is_RX_data_ready(nRF0);	// provjeri RX_DR

	if (data_ready == 1)	// dobili smo nesta
	{
		// buffer je vec spreman, ovo ce ga samo poslat kao ACK_PAYLOAD



		pipe = nRF_get_payload_pipe(nRF0);			// provjeri u kojem pajpu je teret

		if (nRF_is_dynamic_payload_enabled(nRF0) == 1)
		{
			payload_size = nRF_get_dynamic_payload_length(nRF0);
		}
		else
		{
			payload_size = nRF_get_payload_size(nRF0, pipe);
		}

		nRF_clear_buffer(buffer);
		nRF_read_RX_FIFO(nRF0, payload_size);

		//nRF_flush_RX(nRF0);	// ACK PD pokusaj

		//nRF_clear_bits(nRF0); // ocisti RX_DR, TX_DS, MAX_RT
		nRF_clear_RX_data_ready(nRF0); // INFO mora se pocistit inace se razjebat

		//nRF_flush_TX(nRF0);
		return 1;
	}
	else
	{
		return 0;
	}
}

/*************************************************************************************************
				nRF_write()
*************************************************************************************************/
nRF_write_status_t nRF_write(nRF_hw_t *nRF0, char *buffer, uint8_t length)
{
	// kao pametniji write_payload gdje pokusava vise puta poslat i stalno provjerava jel poslano
	uint8_t  ARC = nRF_get_retransmit_count(nRF0);
	uint16_t ARD = nRF_get_retransmit_delay_in_us(nRF0);
	uint32_t timeout_us = ARC*ARD*2;	// 15ms
	uint32_t sent_at = 0;

	nRF_write_status_t status = NRF_SEND_INVALID;

	nRF_stop_listening(nRF0);


	/*
	// provjeri jel dobio ACK od PRX
	if (nRF_is_RX_data_ready(nRF0))
	{
		printf("%s(): izgleda da smo dobili ACK nazad\n", __func__);
	}
	*/



	// pretpostavka da je power_on() i set_mode(TX)

	nRF_write_payload(nRF0, buffer, length);
	sent_at = get_uptime_us();

	do
	{
		//printf("%s() jos salje\n", __func__);
		status = NRF_SEND_IN_PROGRESS;
	}
	// treba radit sve dok *nije* poslao		ili		sve dok nije ispucao sanse		ili 	timeouto
	while ( !((nRF_is_TX_data_sent(nRF0) == 1) || (nRF_is_TX_data_failed(nRF0) == 1) || ((get_uptime_us() - sent_at) > timeout_us)));

	if (nRF_is_TX_data_sent(nRF0) == 1)
	{
		status = NRF_SEND_SUCCESS;
		//nRF_clear_bits(nRF0);	// INFO rijesi magiju da se morao startat prvo RX pa TX
								// INFO moguce da je magija sama od sebe rijesena kad se TX uspije ispravno startat
		// pokusaj
		nRF_flush_TX(nRF0);
		nRF_clear_bits(nRF0);
	}
	if (nRF_is_RX_data_ready(nRF0) == 1)
	{
		uint8_t length = nRF_get_dynamic_payload_length(nRF0);
		printf("%s(): RX_DR Izgleda da smo dobili ACK, duzina: %d\n", __func__, length);
		status = NRF_ACK;
	}

	if (nRF_is_TX_data_failed(nRF0) == 1)
	{
		status = NRF_SEND_FAILED;
		nRF_flush_TX(nRF0);		// jer se nece sam ocistit
		nRF_clear_bits(nRF0);
	}
	/*
	else
	{
		// u slucaju zesceg zajeba, ne bi nikad trebao doc ovamo nego bi trebao javit MAX_RT=1 ako nije poslao
		printf("%s(): Timeout od %d us se dogodio\n", __func__, get_uptime_us()-sent_at);
		reg_value = NRF_SEND_TIMEOUT;
		nRF_clear_bits(nRF0);
	}
	*/

	return status;
}
