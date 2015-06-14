/*************************************************************************************************
				nRF_is_RX_empty2()
*************************************************************************************************/
bool nRF_is_RX_empty2(nRF_hw_t *nRF0)
{
	uint8_t pipe = nRF_get_payload_pipe(nRF0);

	if (pipe == 7)	// 0b111 RX FIFO empty
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*************************************************************************************************
				nRF_is_RX_empty()
*************************************************************************************************/
bool nRF_is_RX_empty(nRF_hw_t *nRF0)
{
	uint8_t reg_value = read_reg(nRF0, REG_FIFO_STATUS);
	bool empty = (reg_value >> RX_EMPTY) & 1;
	return empty;
}

/*************************************************************************************************
				nRF_is_RX_full()
*************************************************************************************************/
bool nRF_is_RX_full(nRF_hw_t *nRF0)
{
	uint8_t reg_value = read_reg(nRF0, REG_FIFO_STATUS);
	bool full = (reg_value >> RX_FULL) & 1;
	return full;
}
