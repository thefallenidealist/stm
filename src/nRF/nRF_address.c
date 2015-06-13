/*************************************************************************************************
				nRF_set_RX_address()
*************************************************************************************************/
int8_t nRF_set_RX_address(nRF_hw_t *nRF0, nRF_pipe_t pipe, uint8_t address[])	// reg 0x0A
{
	// INFO	ako dobije duzu adresu nego sto treba, zapisat ce samo onoliko bajtova koliko treba
	// INFO ako dobije kracu onda ce zapisat koliko ima i smece iz memorije
	// INFO za P{2,3,4,5} postavi samo LSB, MSB pokupi od P1

	uint8_t width 	 = nRF_get_address_width(nRF0);	// uvijek ce bit 3..5
	uint8_t spi_port = nRF0->spi_port;

	if ( (pipe == P0) || (pipe == P1) )	// only P0 and P1 have 5 full 5 bytes address
	{
		cs(nRF0, 0);
		spi_rw(spi_port, (REG_RX_ADDR_P0+pipe) + CMD_W_REGISTER);

		for (uint8_t i=0; i<width; i++) // 40 bits
		{
			spi_rw(spi_port, address[i]);
		}

		cs(nRF0, 1);
	}
	else if (pipe <= P5)
	{
		// LSB
		cs(nRF0, 0);
		spi_rw(spi_port, (REG_RX_ADDR_P0+pipe) + CMD_W_REGISTER);
		spi_rw(spi_port, address[width-1]);
		cs(nRF0, 1);
	}
	else
	{
		printf("%s() zajeb: wrong pipe: %d, exiting\n", __func__, pipe);
		return 0xFF;
	}

	return 0;
}

/*************************************************************************************************
				nRF_set_TX_address()
*************************************************************************************************/
int8_t nRF_set_TX_address(nRF_hw_t *nRF0, uint8_t address[])		// reg 0x10
{
	uint8_t width 	 = nRF_get_address_width(nRF0);	// 3..5
	uint8_t spi_port = nRF0->spi_port;

	cs(nRF0, 0);
	spi_rw(spi_port, REG_TX_ADDR + CMD_W_REGISTER);	// 0x10

	for (uint8_t i=0; i<width; i++)
	{
		spi_rw(spi_port, address[i]);
	}

	cs(nRF0, 1);

	return 0;
}

/*************************************************************************************************
				nRF_get_RX_address()
*************************************************************************************************/
static uint8_t *nRF_get_RX_address(nRF_hw_t *nRF0, nRF_pipe_t pipe)				// reg 0x0{A,B,C,D,E,F}
{
	static uint8_t addr[5] = {};	// max 5 bytes of address

	uint8_t spi_port = nRF0->spi_port;
	uint8_t width 	 = nRF_get_address_width(nRF0);

	if ( (pipe == P0) || (pipe == P1) )	// only P0 and P1 have 5 full 5 bytes address
	{
		cs(nRF0, 0);
		spi_rw(spi_port, (REG_RX_ADDR_P0+pipe) + CMD_R_REGISTER);

		for (uint8_t i=0; i<width; i++) // 40 bits
		{
			addr[i] = spi_rw(spi_port, REG_RX_ADDR_P0 + pipe);
		}

		cs(nRF0, 1);
	}
	else if (pipe <= P5)
	{
		// MSBs
		cs(nRF0, 0);
		spi_rw(spi_port, (REG_RX_ADDR_P1) + CMD_R_REGISTER);

		for (uint8_t i=0; i<width-1; i++)
		{
			addr[i] = spi_rw(spi_port, REG_RX_ADDR_P1);
		}

		cs(nRF0, 1);

		// LSB
		cs(nRF0, 0);
		spi_rw(spi_port, (REG_RX_ADDR_P0+pipe) + CMD_R_REGISTER);
		addr[width-1] = spi_rw(spi_port, REG_RX_ADDR_P0 + pipe);
		cs(nRF0, 1);
	}
	else
	{
		printf("%s() zajeb: wrong pipe: %d, exiting\n", __func__, pipe);
		return NULL;
	}

	return addr;
}

/*************************************************************************************************
				nRF_get_TX_address()
*************************************************************************************************/
static uint8_t *nRF_get_TX_address(nRF_hw_t *nRF0)	
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
				print_address()
*************************************************************************************************/
static void print_address(nRF_hw_t *nRF0, uint8_t mode, nRF_pipe_t pipe)		// mode TX/RX pokupi iz enuma
{
	uint8_t *address 		= NULL;
	uint8_t *address_copy 	= NULL;
	uint8_t length 			= nRF_get_address_width(nRF0);

	if (mode == RX)
	{
		address = nRF_get_RX_address(nRF0, pipe);
		printf("pipe%d: ", pipe);
	}
	else if (mode == TX)
	{
		address = nRF_get_TX_address(nRF0);
		printf("       ");	// da ispis bude poravnat sa RX address
	}
	else
	{
		printf("%s() zajeb\n", __func__);
		return;
	}
	address_copy = address;

	for (uint8_t i=0; i<length; i++)
	{
		printf("0x%02X ", *address++);
	}

	printf("\t");

	address = address_copy;		// ponovo pokazi na pocetak adrese
	for (uint8_t i=0; i<length; i++)
	{
		if ( (*address >= 32) && (*address < 127))	// is printable
		{
			printf("%c", *address++);		// print char
		}
		else
		{
			printf("[0x%02X]", *address++);	// print hex
		}
	}

	printf("\n");
}

/*************************************************************************************************
				nRF_print_RX_address()
*************************************************************************************************/
void nRF_print_RX_address(nRF_hw_t *nRF0, nRF_pipe_t pipe)
{
	printf("%s(): ", __func__);
	print_address(nRF0, RX, pipe);
}

/*************************************************************************************************
				nRF_print_TX_address()
*************************************************************************************************/
void nRF_print_TX_address(nRF_hw_t *nRF0)
{
	printf("%s(): ", __func__);
	print_address(nRF0, TX, 0);	// zapravo pipe nije bitan jer je samo jedan TX pipe
}
