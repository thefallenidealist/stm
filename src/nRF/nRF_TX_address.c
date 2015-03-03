/*************************************************************************************************
				nRF_set_TX_address()
*************************************************************************************************/
int8_t nRF_set_TX_address(nRF_hw_t *nRF0, uint8_t address[])		// reg 0x10
//int8_t nRF_set_TX_address(nRF_hw_t *nRF0, const unsigned char address[6])		// reg 0x10
{
	uint8_t width = nRF_get_address_width(nRF0);
	//printf("%s(): address width: %d\n", __func__, width);

	uint8_t spi_port = nRF0->spi_port;
	//uint8_t address_length = sizeof(address)/sizeof(address[0]);

	if ( (width < 3) || (width > 5) )
	{
		ERROR("Wrong address width\n");
		printf("%s(): Wrong address width\n", __func__);

		return -1;
	}
	/*
	else if (address_length != width)
	{
		DEBUG_INFO("TODO");
		printf("%s(): Dobivena adresa je duza ili kraca od stvarno potrebne adrese\n", __func__);
		printf("%s(): Dobivena duzina: %d\n", __func__, address_length);
		//printf("Potrebna duzina: %d\n", width);
		return -1;
	}
	*/
	else
	{
		cs(nRF0, 0);
		// 40 bits, 8bit reads
		spi_rw(spi_port, REG_TX_ADDR + CMD_W_REGISTER);	// 0x10

		for (uint8_t i=0; i<width; i++)
		{
			spi_rw(spi_port, address[i]);
			// zapisi i u objekt
			// INFO ipak treba zbog _get_ returna
			memmove(&nRF0->tx_address[i], &address[i], sizeof(nRF0->tx_address[i]));
		}
		cs(nRF0, 1);

		// da bi mogao posluzit kao string
		memset(&nRF0->tx_address[width], 0, 1);

		return 0;
	}
}


/*************************************************************************************************
				nRF_get_TX_address()
*************************************************************************************************/
uint8_t *nRF_get_TX_address(nRF_hw_t *nRF0)						// reg 0x10
{
	/*
	uint8_t width = nRF_get_address_width(nRF0);
	uint8_t spi_port = nRF0->spi_port;
	uint8_t address_length = strlen((const char*)address);	// cast da se kompajler ne buni jer je uint8_t type

	if ( (width < 3) || (width > 5) )
	{
		ERROR("Wrong address width\n");
		printf("Wrong address width\n");
		return -1;
	}
	else if (address_length != width)
	{
		DEBUG_INFO("TODO");
		printf("Dobivena adresa je duza ili kraca od stvarno potrebne adrese\n");
		return -1;
	}
	else
	{
		cs(nRF0, 0);
		// 40 bits, 8bit reads
		spi_rw(spi_port, REG_TX_ADDR + CMD_R_REGISTER);	// 0x10

		for (uint8_t i=0; i<width; i++)
		{
			spi_rw(spi_port, address[i]);
			// zapisi i u objekt
			//memmove(&nRF0->tx_address[i], &address[i], sizeof(nRF0->address[i]));
		}
		cs(nRF0, 1);

		// da bi mogao posluzit kao string
		memset(&nRF0->tx_address[width], 0, 1);

		return 0;
	}
	*/

	// nRF_set_TX_address je zapisao u objekt
	return nRF0->tx_address;
}
