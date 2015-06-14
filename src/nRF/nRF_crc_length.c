/*************************************************************************************************
				nRF_set_CRC_length()
*************************************************************************************************/
int8_t nRF_set_CRC_length(nRF_hw_t *nRF0, nRF_crc_length_t crc_length)
{
	if ( (crc_length < CRC_LENGTH_1BTYE) || (crc_length > CRC_LENGTH_2BTYE) )
	{
		ERROR("Wrong CRC length\n");
		printf("Wrong CRC length\n");
		return 0xFF;
	}
	else
	{
		reg_tmp[CRCO] = crc_length;
		write_reg(nRF0, REG_CONFIG);
		return 0;
	}
}

/*************************************************************************************************
				nRF_get_CRC_length()
*************************************************************************************************/
uint8_t nRF_get_CRC_length(nRF_hw_t *nRF0)
{
	uint8_t reg_value = read_reg(nRF0, REG_CONFIG);
	uint8_t length = ((reg_value >> 2) & 1) + 1;	// 0 is 1 byte, 1 is 2 bytes

	return length;
}
