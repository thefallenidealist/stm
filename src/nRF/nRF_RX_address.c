/*************************************************************************************************
				nRF_set_RX_address()
*************************************************************************************************/
int8_t nRF_set_RX_address(nRF_hw_t *nRF0, uint8_t address[])	// reg 0x0A
{
#define BASE_PIPE REG_RX_ADDR_P0
	// TODO zasad implentirano samo pipe0
	uint8_t pipe = 0;
	// LSB se prvi zapisuje
	uint8_t width = nRF_get_address_width(nRF0);
	uint8_t spi_port = nRF0->spi_port;

	//printf("\t\t\t\t%s(): pipe: %d, address: %s\n", __func__, pipe, address);

	if (pipe > 5)		// unsigned enum
	{
		ERROR("Wrong pipe\n");
		printf("Wrong pipe\n");
		return -1;
	}
	else if ( (width < 3) || (width > 5) )
	{
		ERROR("Wrong address width\n");
		printf("Wrong address width\n");
		return -1;
	}
	// INFO	ako dobije duzu adresu nego sto treba, zapisat ce samo onoliko bajtova koliko treba
	// TODO ako dobije kracu onda...
	else
	{
		cs(nRF0, 0);
		// 40 bits, 8bit reads
		spi_rw(spi_port, (BASE_PIPE+pipe) + CMD_W_REGISTER);	// 0x0A+pipe

		//printf("%s(): address width: %d\n", __func__, width);

		for (uint8_t i=0; i<width; i++)
		{
			spi_rw(spi_port, address[i]);
			// zapisi i u objekt
			// INFO ipak treba zbog _get_ returna
			memmove(&nRF0->rx_address[pipe][i], &address[i], sizeof(nRF0->rx_address[pipe][i]));
		}
		cs(nRF0, 1);

		// dodaj NULL na kraj da se moze ispisat kao string
		memset(&nRF0->rx_address[pipe][width], 0, 1);

		return 0;
	}
}

/*************************************************************************************************
				nRF_get_RX_address()
*************************************************************************************************/
uint8_t *nRF_get_RX_address(nRF_hw_t *nRF0)				// reg 0x0{A,B,C,D,E,F}
{
	// TODO zasad koristi samo pipe0 iako moze procitat adrese ostalih pipeova
	uint8_t pipe = 0;
	return nRF0->rx_address[pipe];

	/*
	   // XXX sjebano
	uint8_t spi_port = nRF0->spi_port;

	cs(nRF0, 0);
	spi_rw(spi_port, REG_RX_ADDR_P0 + CMD_R_REGISTER);

	char addr[5] = {};
	uint8_t width = nRF_get_address_width(nRF0);

	for (uint8_t i=0; i<width; i++) // 40 bits
	{
		addr[i] = spi_rw(spi_port, REG_RX_ADDR_P0);	// samo pipe0
	}
	cs(nRF0, 1);

	printf("%s(): address: %s\n", __func__, addr);

	return (const char)addr;
	*/
}
