/*************************************************************************************************
				nRF_set_payload_size()
*************************************************************************************************/
int8_t nRF_set_payload_size(nRF_hw_t *nRF0, nRF_pipe_t pipe, uint8_t payload_size)	// reg 0x{11,12,13,14,15,16}
{
	// broj bajtova koje zelimo slat i primat za odredjeni pajp

	uint8_t spi_port = nRF0->spi_port;

	if (pipe > 5)
	{
		ERROR("Wrong pipe\n");
		printf("Wrong pipe\n");
		return -1;
	}
	else if ( (payload_size < 1) || (payload_size > 32) )
	{
		ERROR("Wrong payload size\n");
		printf("Wrong payload size\n");
		return -1;
	}
	else
	{
		cs(nRF0, 0);
		spi_rw(spi_port, (REG_RX_PW_P0+pipe) + CMD_W_REGISTER);		// 0x11 
		spi_rw(spi_port, payload_size);
		cs(nRF0, 1);

		//write_reg_full(nRF0, REG_RX_PW_P0+pipe, payload_size);

		// zapisi u objekt
		// INFO i nije potrebno kad _get_ procita direktno sa divajsa
		//memmove(&nRF0->rx_payload_size[pipe], &payload_size, sizeof(nRF0->rx_payload_size));

		return 0;
	}
}
// INFO provjereno

/*************************************************************************************************
				nRF_get_payload_size()
*************************************************************************************************/
int8_t nRF_get_payload_size(nRF_hw_t *nRF0, nRF_pipe_t pipe)			// reg 0x{11,12,13,14,15,16}
{
	if (pipe > 5)
	{
		ERROR("Wrong pipe\n");
		printf("Wrong pipe\n");
		return -1;
	}
	else
	{
		uint8_t payload_size = read_reg(nRF0, REG_RX_PW_P0 + pipe);
		return payload_size;
	}
}
// INFO provjereno




// TODO ispitat kako ovo radi
/*************************************************************************************************
				nRF_get_payload_width()
*************************************************************************************************/
uint8_t nRF_get_payload_width(nRF_hw_t *nRF0)
{
	// TODO za sta bi ovo moglo posluzit?
	/*
		CMD	 R_RX_PL_WIDa
	Read RX payload width for the top 
	R_RX_PAYLOAD in the RX FIFO.
	Note: Flush RX FIFO if the read value is larger 
	than 32 bytes.
	*/
	uint8_t spi_port = nRF0->spi_port;

	cs(nRF0, 0);
	uint8_t width = spi_rw(spi_port, CMD_R_RX_PL_WID);
	cs(nRF0, 1);

	if (width > 32)
	{
		nRF_flush_RX(nRF0);
		return 0;
	}
	else
	{
		return width;
	}
}
