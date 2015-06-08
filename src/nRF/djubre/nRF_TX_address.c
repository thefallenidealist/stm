/*************************************************************************************************
				nRF_set_TX_address()
*************************************************************************************************/
int8_t nRF_set_TX_address(nRF_hw_t *nRF0, uint8_t address[])		// reg 0x10
{
	uint8_t width = nRF_get_address_width(nRF0);

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
		}
		cs(nRF0, 1);

		return 0;
	}
}


/*************************************************************************************************
				nRF_get_TX_address()
*************************************************************************************************/
uint8_t *nRF_get_TX_address(nRF_hw_t *nRF0)	
{
	// INFO ima samo jedan TX pipe
	static uint8_t addr[5] = {};	// max 5 bytes of address

	uint8_t spi_port = nRF0->spi_port;
	uint8_t width = nRF_get_address_width(nRF0);

	cs(nRF0, 0);
	spi_rw(spi_port, REG_TX_ADDR + CMD_R_REGISTER);

	for (uint8_t i=0; i<width; i++) // up to 5 bytes
	{
		addr[i] = spi_rw(spi_port, REG_TX_ADDR);
	}
	cs(nRF0, 1);

	return addr;
}

/*************************************************************************************************
				nRF_print_TX_address()
*************************************************************************************************/
void nRF_print_TX_address(nRF_hw_t *nRF0)
{
	uint8_t *addr = nRF_get_TX_address(nRF0);
	uint8_t addr_length = nRF_get_address_width(nRF0);

	printf("%s(): ", __func__);
	for (uint8_t i=0; i<addr_length; i++)
	{
		printf("0x%X ", *addr++);
	}
	printf("\n");
}
