/*************************************************************************************************
				nRF_power_on()
*************************************************************************************************/
void nRF_power_on(nRF_hw_t *nRF0)
{
	reg_tmp[PWR_UP] = 1;
	write_reg(nRF0, REG_CONFIG);

	delay_ms(2);	// 1.5 ms
	// sada je u Standby-I modu
}

/*************************************************************************************************
				nRF_power_off()
*************************************************************************************************/
void nRF_power_off(nRF_hw_t *nRF0)
{
	// XXX izgleda da ovako pravi probleme
	reg_tmp[PWR_UP] = 0;
	write_reg(nRF0, REG_CONFIG);

	//write_reg_full(nRF0, REG_CONFIG, 0);
}

/*************************************************************************************************
				nRF_is_powered()
*************************************************************************************************/
bool nRF_is_powered(nRF_hw_t *nRF0)
{
	uint8_t status = read_reg(nRF0, REG_CONFIG);
	bool powered = (status >> 1) & 1;

	//printf("powered: %d\n", powered);

	return powered;
}
