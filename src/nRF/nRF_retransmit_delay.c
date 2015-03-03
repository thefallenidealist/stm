/*************************************************************************************************
				nRF_set_retransmit_delay()
*************************************************************************************************/
int8_t nRF_set_retransmit_delay(nRF_hw_t *nRF0, delay_t delay)			// reg 0x04
{
	/*
			datasheet, page 63
	If the ACK payload is more than 15 byte in 2Mbps mode the ARD must be 500µS or more, if the ACK
	payload is more than 5byte in 1Mbps mode the ARD must be 500µS or more. In 250kbps mode (even
	when the payload is not in ACK) the ARD must be 500µS or more.
	*/
	if ( (delay > DELAY_4000us) || (delay < DELAY_250us) )
	{
		ERROR("Wrong retransmit delay\n");
		return -1;
	}
	else
	{
		bool b3, b2, b1, b0;
		b0 = delay & 1;
		b1 = (delay >> 1) & 1;
		b2 = (delay >> 2) & 1;
		b3 = (delay >> 3) & 1;

		reg_tmp[ARD0] = b0;
		reg_tmp[ARD1] = b1;
		reg_tmp[ARD2] = b2;
		reg_tmp[ARD3] = b3;

		write_reg(nRF0, REG_SETUP_RETR);
		return 0;
	}
}

/*************************************************************************************************
				nRF_get_retransmit_delay()
*************************************************************************************************/
uint8_t nRF_get_retransmit_delay(nRF_hw_t *nRF0)
{
	uint8_t status = read_reg(nRF0, REG_SETUP_RETR);
	uint8_t delay = (status >> 4) & 0b1111;
	return delay;
}
