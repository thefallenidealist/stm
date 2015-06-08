/*************************************************************************************************
				nRF_set_datarate()
*************************************************************************************************/
void nRF_set_datarate(nRF_hw_t *nRF0, nRF_datarate_t datarate)			// reg 0x06
{
	if ( (datarate < datarate_1Mbps) || (datarate > datarate_2Mbps) )
	{
		ERROR("Wrong datarate\n");
		//printf("Wrong datarate\n");
		return;
	}
	else
	{
		reg_tmp[RF_DR] = datarate;
		write_reg(nRF0, REG_RF_SETUP);
	}
}

/*************************************************************************************************
				nRF_get_datarate()
*************************************************************************************************/
nRF_datarate_t nRF_get_datarate(nRF_hw_t *nRF0)						// reg 0x06
//uint8_t nRF_get_datarate(nRF_hw_t *nRF0)						// reg 0x06
{
	uint8_t status = read_reg(nRF0, REG_RF_SETUP);
	nRF_datarate_t datarate = (status >> RF_DR) & 1;

	return datarate;
}
