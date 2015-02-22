/*************************************************************************************************
				nRF_set_data_rate()
*************************************************************************************************/
void nRF_set_data_rate(nRF_hw_t *nRF0, datarate_t datarate)			// reg 0x06
{
	//if ( (datarate != 0) && (datarate != 1) )
	if ( (datarate < datarate_1Mbps) || (datarate > datarate_2Mbps) )
	{
		ERROR("Wrong datarate\n");
		//printf("Wrong datarate\n");
		// return -1;
	}
	else
	{
		reg_tmp[RF_DR] = datarate;
		write_reg(nRF0, REG_RF_SETUP);
	}
}
// INFO provjereno
