/*************************************************************************************************
				nRF_set_RX_payload_size()
*************************************************************************************************/
int8_t nRF_set_RX_payload_size(nRF_hw_t *nRF0, pipe_t pipe, uint8_t payload_size)	// reg 0x{11,12,13,14,15,16}
{
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
