// TODO provjerit sve funkcije iz ovog fajla
/*************************************************************************************************
				nRF_write_ack()
*************************************************************************************************/
void nRF_write_ack(nRF_hw_t *nRF0, nRF_pipe_t pipe)
{
	if (pipe > 5)
	{
		printf("%s(): Zajeb, number of pipe %d is larger than 5\n", __func__, pipe);
		return;
	}

	uint8_t spi_port = nRF0->spi_port;

	cs(nRF0, 0);
	spi_rw(spi_port, (CMD_W_ACK_PAYLOAD + pipe));
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
