/*************************************************************************************************
				nRF_set_output_power()
*************************************************************************************************/
void nRF_set_output_power(nRF_hw_t *nRF0, nRF_output_power_t power)		// reg 0x06
{
	if ( (power < power_minus_18dBm) || (power > power_0dBm) )
	{
		ERROR("Wrong output power\n");
		//printf("Wrong output power\n");
	}
	else
	{
		bool b1, b0;
		b0 = power & 1;
		b1 = (power >> 1) & 1;

		//printf("\t\t\t\t%s(): power: %d bin: %d%d\n", __func__, power, b1, b0);

		// XXX hardcodano na 0dBm
		reg_tmp[RF_PWR1] = 1;
		reg_tmp[RF_PWR0] = 1;
		write_reg(nRF0, REG_RF_SETUP);
	}
}
