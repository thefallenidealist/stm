/*************************************************************************************************
				nRF_set_retransmit_delay()
*************************************************************************************************/
void nRF_set_retransmit_delay(nRF_hw_t *nRF0, delay_t delay)			// reg 0x04
{
	if ( (delay > DELAY_4000us) || (delay < DELAY_250us) )
	{
		ERROR("Wrong retransmit delay\n");
		// return -1;
	}
	else
	{
		bool b3, b2, b1, b0;
		b0 = delay & 1;
		b1 = (delay >> 1) & 1;
		b2 = (delay >> 2) & 1;
		b3 = (delay >> 3) & 1;

		//printf("\t\t\t\t%s(): delay: %d, bin: %d%d%d%d\n", __func__, delay, b3, b2, b1, b0);

		//write_reg(nRF0, REG_SETUP_RETR, (b3 << ARD3) | (b2 << ARD2) | (b1 << ARD1) | (b0 << ARD0));
		//write_reg(nRF0, REG_SETUP_RETR, (b3 << ARD3) | (b2 << ARD2) | (b1 << ARD1) | (b0 << ARD0), );	// XXX
	}
}
// INFO provjereno
