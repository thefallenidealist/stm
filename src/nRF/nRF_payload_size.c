/*************************************************************************************************
				nRF_set_payload_size()
*************************************************************************************************/
uint8_t nRF_set_payload_size(nRF_hw_t *nRF0, nRF_pipe_t pipe, uint8_t payload_size)	// reg 0x{11,12,13,14,15,16}
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

		return 0;
	}
}

/*************************************************************************************************
				nRF_get_payload_size()
*************************************************************************************************/
uint8_t nRF_get_payload_size(nRF_hw_t *nRF0, nRF_pipe_t pipe)			// reg 0x{11,12,13,14,15,16}
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
