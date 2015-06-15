/*************************************************************************************************
				nRF_is_present()
*************************************************************************************************/
bool nRF_is_present(nRF_hw_t *nRF0)
{
	/*
	uint8_t address1[] = {0x00, 0x01, 0x02, 0x03, 0x04};
	uint8_t *address2 = NULL;
	uint8_t address_width = nRF_get_address_width(nRF0);

	nRF_set_TX_address(nRF0, address1);
	delay_ms(1);
	address2 = nRF_get_TX_address(nRF0);

	for (uint8_t i=0; i<address_width; i++)
	{
		if (address1[i] != *address2++)
		{
			return 0;
		}
	}
	*/


	// nova verzija, samo pokusa procitat defaultnu TX addresu
	const uint8_t default_tx_address[] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
	uint8_t *address = NULL;
	uint8_t address_width = nRF_get_address_width(nRF0);
	address = nRF_get_TX_address(nRF0);

	for (uint8_t i=0; i<address_width; i++)
	{
		if (default_tx_address[i] != *address++)
		{
			return 0;
		}
	}

	/*
	   // XXX ne pomaze, reg_config ispadne 8, a kasnije bude 0x00
	uint8_t reg_config = read_reg(nRF0, REG_CONFIG);

	printf("\t\t\t\t%s() reg_config: %d\n", __func__, reg_config);

	if (reg_config == 0x00)	// REG_CONFIG should't be empty
	{
		return 0;
	}
	*/

	return 1;
}
