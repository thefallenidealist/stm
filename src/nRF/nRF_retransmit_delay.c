/*************************************************************************************************
				nRF_set_retransmit_delay()
*************************************************************************************************/
int8_t nRF_set_retransmit_delay(nRF_hw_t *nRF0, nRF_delay_t delay)			// reg 0x04
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
				nRF_get_retransmit_delay_in_us()
*************************************************************************************************/
uint16_t nRF_get_retransmit_delay_in_us(nRF_hw_t *nRF0)
{
	// moze posluzit za racunaje softerskog timeouta kod slanja
	uint8_t reg_value = read_reg(nRF0, REG_SETUP_RETR);
	uint8_t delay = (reg_value >> 4) & 0b1111;

	switch (delay)
	{
		case DELAY_250us:
			return 250;
		case DELAY_500us:
			return 500;
		case DELAY_750us:
			return 750;
		case DELAY_1000us:
			return 1000;
		case DELAY_1250us:
			return 1250;
		case DELAY_1500us:
			return 1500;
		case DELAY_1750us:
			return 1750;
		case DELAY_2000us:
			return 2000;
		case DELAY_2250us:
			return 2250;
		case DELAY_2500us:
			return 2500;
		case DELAY_2750us:
			return 2750;
		case DELAY_3000us:
			return 3000;
		case DELAY_3250us:
			return 3250;
		case DELAY_3500us:
			return 3500;
		case DELAY_3750us:
			return 3750;
		case DELAY_4000us:
			return 4000;
		default:
			printf("%s() Zajeb, wrong ARD delay: %d\n", __func__, delay);
			return 0;
	}
}
