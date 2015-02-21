/*************************************************************************************************
				nRF_get_address_width()
*************************************************************************************************/
uint8_t nRF_get_address_width(nRF_hw_t *nRF0)							// reg 0x03
{
	uint8_t width = read_reg(nRF0, REG_SETUP_AW) + 2; // jer mu je "0b01" zapravo 3
	//printf("\t\t\t\twidth: %d\n", width);
	if (width < 3)
	{
		ERROR("Width should be 3, 4 or 5\n");
	}
	return width;
}
// INFO provjereno
