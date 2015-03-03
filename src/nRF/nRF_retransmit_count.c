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

		reg_tmp[ARC3] = b3;
		reg_tmp[ARC2] = b2;
		reg_tmp[ARC1] = b1;
		reg_tmp[ARC0] = b0;

		write_reg(nRF0, REG_SETUP_RETR);
	}
}

/*************************************************************************************************
				nRF_get_retransmit_count()
*************************************************************************************************/
uint8_t nRF_get_retransmit_count(nRF_hw_t *nRF0)
{
	uint8_t status = read_reg(nRF0, REG_SETUP_RETR);
	uint8_t count = status & 0b1111;
	return count;
}
