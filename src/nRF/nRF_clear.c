/*************************************************************************************************
				nRF_clear_RX_data_ready()
*************************************************************************************************/
void nRF_clear_RX_data_ready(nRF_hw_t *nRF0)
{
	// write 1 to clear bits
	reg_tmp[RX_DR] = 1;	
	write_reg(nRF0, REG_STATUS);
}


/*************************************************************************************************
				nRF_clear_TX_data_sent()
*************************************************************************************************/
void nRF_clear_TX_data_sent(nRF_hw_t *nRF0)	
{
	reg_tmp[TX_DS] = 1;
	write_reg(nRF0, REG_STATUS);
}

/*************************************************************************************************
				nRF_clear_TX_max_retransmits
*************************************************************************************************/
void nRF_clear_TX_max_retransmits(nRF_hw_t *nRF0)	
{
	reg_tmp[MAX_RT] = 1;
	write_reg(nRF0, REG_STATUS);
}
