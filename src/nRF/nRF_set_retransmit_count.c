/*************************************************************************************************
				nRF_set_retransmit_count()
*************************************************************************************************/
void nRF_set_retransmit_count(nRF_hw_t *nRF0, uint8_t count)		// reg 0x04
{
	if ( (count < 0) || (count > 15) )
	{
		ERROR("count must be 0..15\n");
		//printf("count must be 0..15\n");
		// return -1;
	}
	else
	{
		bool b3, b2, b1, b0;
		b0 =  count & 1;
		b1 = (count >> 1) & 1;
		b2 = (count >> 2) & 1;
		b3 = (count >> 3) & 1;

		//printf("\t\t\t\t%s(): count: %d bin:%d%d%d%d\n", __func__, count, b3, b2, b1, b0);

		//write_reg(nRF0, REG_SETUP_RETR, (b3 << ARC3) | (b2 << ARC2) | (b1 << ARC1) | (b0 << ARC0));
		//write_reg(nRF0, REG_SETUP_RETR, (b3 << ARC3) | (b2 << ARC2) | (b1 << ARC1) | (b0 << ARC0)); XXX
	}
}
// INFO provjereno
