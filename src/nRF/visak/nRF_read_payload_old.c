/*************************************************************************************************
				nRF_read_payload_old()
*************************************************************************************************/
uint8_t *nRF_read_payload_old(nRF_hw_t *nRF0, uint8_t howmany)
{
	if ( (howmany < 0) || (howmany > 32) )
	{
		ERROR("Wrong number of bytes to read\n");
		printf("Wrong number of bytes to read\n");

		return NULL;
	}

	uint8_t spi_port = nRF0->spi_port;

	cs(nRF0, 0);
	spi_rw(spi_port, CMD_R_RX_PAYLOAD);

	for (uint8_t i=0; i<howmany; i++)
	{
		nRF_RX_buffer[i] = spi_rw(spi_port, CMD_NOP);
	}
	cs(nRF0, 1);

	return nRF_RX_buffer;
}
