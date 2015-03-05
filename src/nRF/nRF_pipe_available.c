/*************************************************************************************************
				nRF_get_payload_pipe()
*************************************************************************************************/
datapipe_t nRF_get_payload_pipe(nRF_hw_t *nRF0)					// reg 0x07, b321
{
	//Data pipe number for the payload available for 
	//reading from RX_FIFO
	//000-101: Data Pipe Number
	//110: Not Used
	//111: RX FIFO Empty		default

	uint8_t status = read_reg(nRF0, REG_STATUS);
	datapipe_t pipe = (status >> 1) & 0b111;

	/*
	if (pipe > 5)
	{
		printf("%s(): Wrong pipe: %d\n", __func__, pipe);
	}
	*/

	return pipe;
}
