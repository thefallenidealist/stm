/*************************************************************************************************
				nRF_write_payload()
*************************************************************************************************/
void nRF_write_payload(nRF_hw_t *nRF0, char *buffer, uint8_t length)
{
	// INFO
	// moguce mu rec da flusha TX tako da u slucaju da je pokusao prosli paket poslat maksimalno
	// puta i nije uspio... posalje novi bez explicitnog flushanja iz main()
	// nRF_flush_TX(nRF0);

	uint8_t spi_port = nRF0->spi_port;
	uint8_t payload_length = 0;
	// TODO odma na pocetku provjerit jel length <=32
	bool dynamic_payload_enabled = nRF_is_dynamic_payload_enabled(nRF0);	// da samo jednom pozove funkciju

	//if (nRF_is_dynamic_payload_enabled(nRF0) == 1)
	if (dynamic_payload_enabled == 1)
	{
		payload_length = length;
	}
	else
	{
		payload_length = nRF_get_payload_size(nRF0, P0);	// TODO not hardcoded pipe
	}

	uint8_t empty_payload = 0;

	// TODO preimenovat varijable i printfova da imaju smisla, ne znam ni na hrvatskom rec da ima smisla

	if (length > 32)
	{
		// pipe maksimalno moze imat 32 znaka
		printf("%s(): Zajeb, length (%d) larger than 32, exiting\n", __func__, length);
		return;
	}
	else if (length > payload_length)
	{
		//printf("%s(): Warning: pipe payload width is %d, argument length is %d, trimming\n", __func__, payload_length, length);
		length = payload_length;	// ne moze poslat vise bajtova nego sto je payload length
	}
	else if (length < payload_length)
	{
		empty_payload = payload_length - length;
		//printf("%s(): Info: payload (%d) is smaller than pipe width (%d)\n", __func__, length, payload_length);
	}

  	// write payload
	cs(nRF0, 0);
	spi_rw(spi_port, CMD_W_TX_PAYLOAD);
	while (length--)
	{
		spi_rw(spi_port, *buffer++);
	}
	if (dynamic_payload_enabled == 0)
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
				nRF_read_payload()
*************************************************************************************************/
bool nRF_read_payload(nRF_hw_t *nRF0)
{
	// novo 150602
	uint8_t spi_port 	 = nRF0->spi_port;
	uint8_t payload_size = 1;

	bool data_ready = nRF_is_RX_data_ready(nRF0);	// provjeri RX_DR

	if (data_ready == 1)	// dobili smo nesta
	{
		uint8_t pipe		 = nRF_get_payload_pipe(nRF0);			// provjeri u kojem pajpu je teret

		if (nRF_is_dynamic_payload_enabled(nRF0) == 1)
		{
			payload_size = nRF_get_dynamic_payload_length(nRF0);
		}
		else
		{
			payload_size = nRF_get_payload_size(nRF0, pipe);
		}

		//printf("%s(): payload_size: %d\n", __func__, payload_size);
		nRF_clear_buffer(nRF_RX_buffer);

		// reading RX FIFO
		cs(nRF0, 0);
		spi_rw(spi_port, CMD_R_RX_PAYLOAD);

		for (uint8_t i=0; i<payload_size; i++)
		{
			// zapisivanje u globalni buffer
			nRF_RX_buffer[i] = spi_rw(spi_port, CMD_NOP);
		}
		cs(nRF0, 1);
		nRF_RX_buffer[payload_size] = '\0';	// neka se nadje

		//nRF_clear_bits(nRF0); // ocisti RX_DR, TX_DS, MAX_RT
		nRF_clear_RX_data_ready(nRF0); // INFO mora se pocistit inace se razjebat

		return 1;
	}
	else
	{
		//printf("Nothing received\n");
		return 0;
	}
}















/*************************************************************************************************
				nRF_write()
*************************************************************************************************/
void nRF_write(nRF_hw_t *nRF0, char *buffer, uint8_t length)
{
	// kao pametniji write_payload gdje pokusava vise puta poslat i stalno provjerava jel poslano
	uint8_t  ARC = nRF_get_retransmit_count(nRF0);
	uint16_t ARD = nRF_get_retransmit_delay_in_us(nRF0);
	uint32_t timeout_us = ARC*ARD*2;	// 15ms

	nRF_stop_listening(nRF0);

	reg_tmp[PWR_UP] = 1;
	reg_tmp[PRIM_RX] = 0;
	delay_us(150);	// 130
	nRF_write_payload(nRF0, buffer, length);

	// cekaj na ACK ili da posalje maksimalni broj puta
	uint32_t sent_at = get_uptime_us();
	do
	{
		printf("%s(): Jos uvijek se salje paket, uptime_us: %ld\n", __func__, get_uptime_us());
	}
	// treba radit sve dok nije poslao		ili		sve dok nije ispucao sanse		ili 	timeouto
	while ( !((nRF_is_TX_data_sent(nRF0) == 1) || (nRF_is_TX_data_failed(nRF0) == 1) || (get_uptime_us() - sent_at > timeout_us)));

	// ili je poslao ili fejlao
	if (nRF_is_TX_data_sent(nRF0) == 1)
	{
		printf("%s(): TX_DS Paket je poslan\n", __func__);
		nRF_clear_bits(nRF0);	// INFO rijesi magiju i da se moze startat prvo TX pa RX
		// INFO rijesi ovo: "radi dobro, ali ako se usred slanja ugasi RX ovaj i dalje javlja da je uspjesno poslao sve"
	}
	else if (nRF_is_TX_data_failed(nRF0) == 1)
	{
		printf("%s(): MAX_RT: %d Maksimalno se potrudio i svejedno fejlao\n", __func__, nRF_get_retransmit_count(nRF0));
		nRF_clear_bits(nRF0);
	}
	else if (nRF_is_RX_data_ready(nRF0) == 1)
	{
		uint8_t length = nRF_get_dynamic_payload_length(nRF0);
		printf("%s(): RX_DR Izgleda da smo dobili ACK, duzina: %d\n", __func__, length);
	}
	else
	{
		// u slucaju zesceg zajeba, ne bi nikad trebao doc ovamo nego bi trebao javit MAX_RT=1 ako nije poslao
		printf("%s(): Timeout od %d us se dogodio\n", __func__, get_uptime_us()-sent_at);
	}

	// power_down
}
