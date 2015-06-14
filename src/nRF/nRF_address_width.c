/*************************************************************************************************
				nRF_set_address_width()
*************************************************************************************************/
void nRF_set_address_width(nRF_hw_t *nRF0, uint8_t width)				// reg 0x03
{
	if ( (width < 3) || (width > 5) )
	{
		ERROR("Wrong address width\n");
	}
	else
	{
		// 11 = 5, 10 = 4, 01 = 3 bytes width address
		uint8_t new_width = width - 2;	// jer mu je 0b00 zapravo 2

		bool b1, b0;
		b0 = new_width & 1;
		b1 = (new_width >> 1) & 1;

		reg_tmp[AW1] = b1;
		reg_tmp[AW0] = b0;
		write_reg(nRF0, REG_SETUP_AW);

		// write into object
		//nRF0->address_width = width;
	}
}

/*************************************************************************************************
				nRF_get_address_width()
*************************************************************************************************/
uint8_t nRF_get_address_width(nRF_hw_t *nRF0)							// reg 0x03
{
	return (read_reg(nRF0, REG_SETUP_AW) + 2);	// +2 jer  0b01 znaci da je adresa siroka 3b
}
