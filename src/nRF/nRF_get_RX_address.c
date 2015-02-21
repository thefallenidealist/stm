/*************************************************************************************************
				nRF_get_RX_address()
*************************************************************************************************/
int8_t nRF_get_RX_address(nRF_hw_t *nRF0, pipe_t pipe)				// reg 0x0{A,B,C,D,E,F}
{
#define BASE_PIPE REG_RX_ADDR_P0

	uint8_t tmp_addr[5] = {};

	if ( (pipe > 5) || (pipe < 0) )
	{
		ERROR("Wrong pipe\n");
		//printf("Wrong pipe\n");
		return -1;
	}
	else
	{
		uint8_t width = nRF_get_address_width(nRF0);
		uint8_t spi_port = nRF0->spi_port;

		cs(nRF0, 0);
		// 40 bits, 8bit reads

		if (pipe < 2)	// P0, P1
		{
			spi_rw(spi_port, (BASE_PIPE+pipe) + CMD_R_REGISTER);	// 0x0A+pipe

			// procitaj normalno onoliko bajtova kolika je sirina adrese
			for (uint8_t i=0; i<width; i++)
			{
				tmp_addr[i] = spi_rw(spi_port, 0xFF);
			}
		}
		else
		{
			spi_rw(spi_port, (BASE_PIPE) + CMD_R_REGISTER);	

			// procitaj max 4 MSB od P0
			for (uint8_t i=0; i<width-1; i++)
			{
				tmp_addr[i] = spi_rw(spi_port, 0xFF);
			}
			cs(nRF0, 1);
			cs(nRF0, 0);

			// procitaj LSB
			spi_rw(spi_port, (BASE_PIPE+pipe) + CMD_R_REGISTER);	// 0x0A+pipe
			tmp_addr[width-1] = spi_rw(spi_port, 0xFF);
		}
		cs(nRF0, 1);

		// zapisimo u objekt
		for (uint8_t i=0; i<width; i++)
		{
			//memmove(&nRF0->address[i], &tmp_addr[i], sizeof(nRF0->address[i]));
			// 2D polje
			printf("\t\t\t\tA memmove: pipe: %d, i: %d\n");
			memmove(&nRF0->address[pipe][i], &tmp_addr[i], sizeof(nRF0->address[pipe][i]));
			printf("\t\t\t\tB memmove: pipe: %d, i: %d\n");
		}
		return 0;
	}
}
