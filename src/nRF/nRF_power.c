/*************************************************************************************************
				nRF_power_on()
*************************************************************************************************/
void nRF_power_on(nRF_hw_t *nRF0)
{
	reg_tmp[PWR_UP] = 1;
	write_reg(nRF0, REG_CONFIG);

	delay_ms(2);	// 1.5 ms
	delay_ms(2);	// dodatno jos, za slucaj da je SI24R01 kopija
	// sada je u Standby-I modu
}

/*************************************************************************************************
				nRF_power_off()
*************************************************************************************************/
void nRF_power_off(nRF_hw_t *nRF0)
{
	nRF_flush_RX(nRF0);
	nRF_flush_TX(nRF0);

	reg_tmp[PWR_UP] = 0;
	write_reg(nRF0, REG_CONFIG);
	delay_ms(10);		// izgeda da mu treba malo vremena da skuzi da se ugasio
						// nakon gasenja pokazi da je samo PWR_UP = 0
	// XXX kasnije citanje ovog registra pokaze da su svi bitovi nula
}

/*************************************************************************************************
				nRF_is_powered()
*************************************************************************************************/
bool nRF_is_powered(nRF_hw_t *nRF0)
{
	uint8_t status = read_reg(nRF0, REG_CONFIG);
	bool powered = (status >> 1) & 1;

	return powered;
}
