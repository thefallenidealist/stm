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

	printf("max ch: %d\n", max_ch);
	if (ch > max_ch)
	{
		ERROR("Wrong channel\n");
		// return -1;
	}
	else
	{
		bool b6, b5, b4, b3, b2, b1, b0;
		uint8_t new_ch = ch+2;	// jer je ch0 0b0000010 (2)

		b0 = (new_ch >> RF_CH0) & 1;
		b1 = (new_ch >> RF_CH1) & 1;
		b2 = (new_ch >> RF_CH2) & 1;
		b3 = (new_ch >> RF_CH3) & 1;
		b4 = (new_ch >> RF_CH4) & 1;
		b5 = (new_ch >> RF_CH5) & 1;
		b6 = (new_ch >> RF_CH6) & 1;

		//printf("%s() ch: %d new ch: %d bin: %d%d%d%d%d%d%d\n", __func__, ch, new_ch, b6, b5, b4, b3, b2, b1, b0);
		//write_reg(nRF0, REG_RF_CH, (b6 << RF_CH6) | (b5 << RF_CH5) | (b4 << RF_CH4) | (b3 << RF_CH3) | (b2 << RF_CH2) | (b1 << RF_CH1) | (b0 << RF_CH0));
		// XXX
		//write_reg(nRF0, REG_RF_CH, (b6 << RF_CH6) | (b5 << RF_CH5) | (b4 << RF_CH4) | (b3 << RF_CH3) | (b2 << RF_CH2) | (b1 << RF_CH1) | (b0 << RF_CH0));
	}
}
// INFO provjereno, ali ne i hardverski
