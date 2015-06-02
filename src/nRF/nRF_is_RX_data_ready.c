/*************************************************************************************************
				nRF_is_RX_data_ready()
*************************************************************************************************/
bool nRF_is_RX_data_ready(nRF_hw_t *nRF0)							// reg 0x06, b6
{
	//Data Ready RX FIFO interrupt. Asserted when
	//new data arrives RX FIFOb.
	//Write 1 to clear bit.

	//printf("%s(): arg: %p\n", __func__, nRF0);

	uint8_t status = read_reg(nRF0, REG_STATUS);
	return ((status >> RX_DR) & 1);		// after reset: 0
}
// INFO provjereno

void nRF_clear_RX_data_ready(nRF_hw_t *nRF0)							// reg 0x06, b6
{
	// write 1 to clear
	//reg_tmp[RX_DR] = 0;
	reg_tmp[RX_DR] = 1;
	write_reg(nRF0, REG_STATUS);
}
