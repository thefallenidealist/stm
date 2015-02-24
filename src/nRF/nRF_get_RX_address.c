/*************************************************************************************************
				nRF_get_RX_address()
*************************************************************************************************/
uint8_t *nRF_get_RX_address(nRF_hw_t *nRF0)				// reg 0x0{A,B,C,D,E,F}
//const char *nRF_get_RX_address(nRF_hw_t *nRF0)				// reg 0x0{A,B,C,D,E,F}
{
	// TODO zasad koristi samo pipe0 iako moze procitat adrese ostalih pipeova
	uint8_t pipe = 0;

	return nRF0->rx_address[pipe];

	/*
	uint8_t spi_port = nRF0->spi_port;
	// samo pipe0
	cs(nRF0, 0);
	spi_rw(spi_port, REG_RX_ADDR_P0 + CMD_R_REGISTER);

	char addr[5] = {};

	for (uint8_t i=0; i<5; i++) // 40 bits
	{
		addr[i] = spi_rw(spi_port, REG_RX_ADDR_P0);
	}
	cs(nRF0, 1);

	return (const char)addr;
	*/
}
