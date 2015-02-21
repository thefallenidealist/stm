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
		//uint8_t address_length = strlen((const char*)address);	// cast da se kompajler ne buni jer je uint8_t type
	//uint8_t address_length = sizeof(address)/sizeof(address[0]);

	//printf("\t\t\t\t%s(): pipe: %d, address: %s\n", __func__, pipe, address);

	//if ( (pipe > 5) || (pipe < 0) )
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
	/*
	else if (address_length != width)
	{
		DEBUG_INFO("TODO");
		printf("Dobivena adresa je duza ili kraca od stvarno potrebne adrese\n");
		// XXX
		return -1;
	}
	*/
	else
	{
		cs(nRF0, 0);
		// 40 bits, 8bit reads
		spi_rw(spi_port, (BASE_PIPE+pipe) + CMD_W_REGISTER);	// 0x0A+pipe

		for (uint8_t i=0; i<width; i++)
		{
			spi_rw(spi_port, address[i]);
			// zapisi i u objekt
			// INFO ipak treba zbog _get_ returna
			memmove(&nRF0->rx_address[pipe][i], &address[i], sizeof(nRF0->rx_address[pipe][i]));
		}
		cs(nRF0, 1);

		// da bi mogao posluzit kao string
		memset(&nRF0->rx_address[pipe][width], 0, 1);

		return 0;
	}
}
