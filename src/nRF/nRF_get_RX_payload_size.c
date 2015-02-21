/*************************************************************************************************
				nRF_get_RX_payload_size()
*************************************************************************************************/
int8_t nRF_get_RX_payload_size(nRF_hw_t *nRF0, pipe_t pipe)			// reg 0x{11,12,13,14,15,16}
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
