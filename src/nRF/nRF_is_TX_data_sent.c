/*************************************************************************************************
				nRF_is_TX_data_sent()
*************************************************************************************************/
bool nRF_is_TX_data_sent(nRF_hw_t *nRF0)					
{
	//Data Sent TX FIFO interrupt. Asserted when 
	//packet transmitted on TX. If AUTO_ACK is acti-
	//vated, this bit is set high only when ACK is 
	//received.
	//Write 1 to clear bit.

	uint8_t reg_value = read_reg(nRF0, REG_STATUS);
	return ((reg_value >> TX_DS) & 1);		// after reset: 0
}

/*************************************************************************************************
				nRF_is_TX_data_failed()
*************************************************************************************************/
bool nRF_is_TX_data_failed(nRF_hw_t *nRF0)
{
	// provjerava jel MAX_RT aktivan
	// aktivan je kad je TX pokusao retransmitat maksimalni broj puta
	uint8_t reg_value = read_reg(nRF0, REG_STATUS);
	return ((reg_value >> MAX_RT) & 1);
}
