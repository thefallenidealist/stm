/*************************************************************************************************
				nRF_get_lost_packets()
*************************************************************************************************/
uint8_t nRF_get_lost_packets(nRF_hw_t *nRF0)						// reg 0x08
{
	uint8_t status = read_reg(nRF0, REG_OBSERVE_TX);
	uint8_t count = (status >> 4) & 0b1111;
	return count;
}

/*************************************************************************************************
				nRF_get_retransmitted_packets()
*************************************************************************************************/
uint8_t nRF_get_retransmitted_packets(nRF_hw_t *nRF0)				// reg 0x08
{
	uint8_t status = read_reg(nRF0, REG_OBSERVE_TX);
	uint8_t count = status & 0b1111;
	return count;
}
