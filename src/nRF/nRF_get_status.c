/*************************************************************************************************
				get_status()
*************************************************************************************************/
static uint8_t get_status(nRF_hw_t *nRF0)
{
	// ili ovako ili procitat registar STATUS (0x07)
	uint8_t status;
	uint8_t spi_port = nRF0->spi_port;

	cs(nRF0, 0);
	status = spi_rw(spi_port, 0xFF);
	cs(nRF0, 1);

	/*
	   14 = RX FIFO empty
	 */

	return status;
}
