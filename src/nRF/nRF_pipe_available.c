/*************************************************************************************************
				nRF_datapipe_available()
*************************************************************************************************/
datapipe_t nRF_pipe_available(nRF_hw_t *nRF0)					// reg 0x07, b321
{
	// TODO malo bolje sredit, return neki ubacit itd

	//Data pipe number for the payload available for 
	//reading from RX_FIFO
	//000-101: Data Pipe Number
	//110: Not Used
	//111: RX FIFO Empty		default

	uint8_t status = read_reg(nRF0, REG_STATUS);
	datapipe_t pipe = (status >> 1) & 0b111;

	//printf("%s(): data pipe: %d\n", __func__, pipe);

	if (pipe == RX_FIFO_empty)
	{
		printf("%s(): RX FIFO is empty\n", __func__);
	}
	else if (pipe == pipe_not_used)
	{
		printf("%s(): pipe is not used\n");
	}
	else if ( (pipe <= avaible_pipe5) || (pipe >= avaible_pipe0) )
	{
		printf("%s(): Avaible pipe: %d\n", __func__, pipe);
	}

	return pipe;
}
// TODO provjerit sve osim RX FIFO empty
