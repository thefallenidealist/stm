// TODO provjerit sve funkcije iz ovog fajla
/*************************************************************************************************
				nRF_write_ack()
*************************************************************************************************/
void nRF_write_ack(nRF_hw_t *nRF0)
{
	// vrlo slican write_TX_FIFO osim sto koristi drugu komandu
	uint8_t spi_port = nRF0->spi_port;

	// DEBUG TODO
	uint8_t length = 7;
	char cbuffer[] = "PRX ACK";
	char *buffer = cbuffer;
	uint8_t pipe = 1;

	if (nRF_is_TX_full(nRF0) == 1)
	{
		printf("%s(): Zajeb, TX is full, exiting\n", __func__);
	}
	// mozda provjera jel omogucen dynamic payload


	//nRF_write_TX_FIFO(nRF0, buffer, length, 1, 0);
	// samo popuni, nemoj poslat (nemoj togglat CE)
	cs(nRF0, 0);
	spi_rw(spi_port, CMD_W_TX_PAYLOAD);
	while (length--)
	{
		spi_rw(spi_port, *buffer++);
	}
	cs(nRF0, 1);

	// posalji ACK
	cs(nRF0, 0);
	spi_rw(spi_port, (CMD_W_ACK_PAYLOAD | (pipe & 0b111)));
	cs(nRF0, 1);

	// pulse CE for transmission
	ce(nRF0, 1);
	delay_us(11);	// 10+ us
	ce(nRF0, 0);
}

/*************************************************************************************************
				nRF_write_payload_no_ack()
*************************************************************************************************/
void nRF_write_payload_no_ack(nRF_hw_t *nRF0, char *buffer, uint8_t length)
{
	// INFO
	// zapravo isti nRF_write_payload() osim sto salje drugi CMD
	// TODO mora bit omogucen EN_DYN_ACK u REG_FEATURE da bi ovo radilo, page 63


	if (length > 32)
	{
		printf("%s(): Zajeb, length (%d) larger than 32, exiting\n", __func__, length);
		return ;
	}

	uint8_t spi_port = nRF0->spi_port;

  	// write payload
	cs(nRF0, 0);
	spi_rw(spi_port, CMD_W_TX_PAYLOAD_NO_ACK);
	while (length--)
	{
		spi_rw(spi_port, *buffer++);
	}
	cs(nRF0, 1);

	// pulse CE for transmission
	ce(nRF0, 1);
	delay_us(11);	// 10+ us
	ce(nRF0, 0);
}
