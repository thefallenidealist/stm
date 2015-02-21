/*************************************************************************************************
				nRF_get_data_rate()
*************************************************************************************************/
datarate_t nRF_get_data_rate(nRF_hw_t *nRF0)						// reg 0x06
{
	uint8_t status = read_reg(nRF0, REG_RF_SETUP);
	datarate_t datarate = (status >> RF_DR) & 1;
	return datarate;
}
// INFO provjereno, ali ne radi zbog write_reg
