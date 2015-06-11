/*************************************************************************************************
				nRF_get_payload_pipe()
*************************************************************************************************/
//nRF_pipe_t nRF_get_payload_pipe(nRF_hw_t *nRF0)					// reg 0x07, b321
nRF_payload_pipe_t nRF_get_payload_pipe(nRF_hw_t *nRF0)					// reg 0x07, b321
{
	// vrati pipe ako u njemu ima nesta
	// vrati u kojem pajpu je payload ili vrati '7' ako... :

	//Data pipe number for the payload available for 
	//reading from RX_FIFO
	//000-101: Data Pipe Number
	//110: Not Used
	//111: RX FIFO Empty		default

	uint8_t status = read_reg(nRF0, REG_STATUS);
	nRF_payload_pipe_t pipe = (status >> 1) & 0b111;

	/*
	if (pipe == 0b110)
	{
		printf("%s(): pipe not used (raw: %d\n", __func__, pipe);
	}
	if (pipe == 0b111)
	{
		printf("%s(): RX FIFO empty (default, raw: %d)\n", __func__, pipe);
	}
	*/
	
	return pipe;
}

