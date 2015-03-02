/*************************************************************************************************
				nRF_set_channel()
*************************************************************************************************/
void nRF_set_channel(nRF_hw_t *nRF0, uint8_t ch)					// reg 0x05
{
	// 7b, default: 0000010
	// Freq: 2.400GHz to 2.525GHz
		// 125 MHz
	// Freq = 2400 + ch
	// 1Mbps	- kanali razmakniti 1MHz
	// 2Mbps	- kanali razmakniti 2Mhz

	// pretpostavka da je defaultni kanal 0 = 0000010

	datarate_t datarate = nRF_get_data_rate(nRF0);
	uint8_t max_ch = 0;

	// TODO ch test when datarate is 2Mbps

	if (datarate == datarate_1Mbps)
	{
		//printf("datarate is 1Mbps\n");
		max_ch = 125;	// uracunat i nulti
	}
	else if (datarate == datarate_2Mbps)
	{
		//printf("datarate is 2Mbps\n");
		max_ch = 62;	// uracunat i nulti
	}
	else
	{
		ERROR("uknown datarate\n");
		//printf("uknown datarate\n");
	}

	//printf("max ch: %d\n", max_ch);

	if (ch > max_ch)
	{
		ERROR("Wrong channel\n");
		// return -1;
	}
	else
	{
		uint8_t new_ch = ch+2;	// jer je ch0 0b0000010 (2)

		//printf("%s() ch: %d, new ch: %d bin: %s\n", __func__, ch, new_ch, dec2bin8_str(new_ch));
		write_reg_full(nRF0, REG_RF_CH, new_ch);
	}
}
// INFO provjereno

/*************************************************************************************************
				nRF_set_channel()
*************************************************************************************************/
uint8_t nRF_get_channel(nRF_hw_t *nRF0)
{
	uint8_t status = read_reg(nRF0, REG_RF_CH);

	return status-2;
}
