/*************************************************************************************************
				nRF_set_mode()
*************************************************************************************************/
void nRF_set_mode(nRF_hw_t *nRF0, nRF_mode_t mode)
{
	if (nRF0 == NULL)
	{
		ERROR("Wrong nRF address\n");
		printf("Wrong nRF address\n");
	}
	else if (mode > RX)
	{
		ERROR("Wrong mode\n");
		printf("Wrong mode\n");
	}
	else
	{
		if (nRF_powered(nRF0) == 1)
		{
			// treba ga ugasit prije stimanja moda
			//printf("Gasim pizdariju\n");
			nRF_power_off(nRF0);
		}

		if (mode == RX)
		{
			ce(nRF0, 1);	// for RX mode

			reg_tmp[PRIM_RX] = mode;
			write_reg(nRF0, REG_CONFIG);

			//printf("Palim pizdariju\n");
			nRF_power_on(nRF0);
		}
		else
		{
			// kad se napuni buffer

			ce(nRF0, 0);

			reg_tmp[PRIM_RX] = mode;
			write_reg(nRF0, REG_CONFIG);

			//printf("Palim pizdariju\n");
			nRF_power_on(nRF0);

			ce(nRF0, 1);
			delay_us(15);	// 10 us
			// sam se vrati u TX mode
		}

		/*
		The TX mode is an active mode where the nRF24L01 transmits a packet. To enter this mode, the 
		nRF24L01 must have the PWR_UP bit set high,  PRIM_RX bit set low, a payload in the TX FIFO and, a high 
		pulse on the CE for more than 10µs.

		The nRF24L01 stays in TX mode until it finishes transmitting a current packet. If CE = 0 nRF24L01 returns 
		to standby-I mode. If CE = 1, the next action is determined by the status of the TX FIFO. If the TX FIFO is 
		not empty the nRF24L01 remains in TX mode, transmitting the next packet. If the TX FIFO is empty the 
		nRF24L01 goes into standby-II mode.The nRF24L01 transmitter PLL operates in open loop when in TX 
		mode. It is important to never keep the nRF24L01 in TX mode for more than 4ms at a time. If the auto 
		retransmit is enabled, the nRF24L01 is never in TX mode long enough to disobey this rule.
		*/

	}
}

/*************************************************************************************************
				nRF_get_mode()
*************************************************************************************************/
nRF_mode_t nRF_get_mode(nRF_hw_t *nRF0)
{
	nRF_mode_t mode = MODE_ERROR;

	if (nRF0 == NULL)
	{
		ERROR("Wrong nRF address\n");
		printf("Wrong nRF address\n");
		return mode;
	}
	else
	{
		uint8_t status = read_reg(nRF0, REG_CONFIG);
		nRF_mode_t mode = status & 1;

		//printf("mode: [0 TX, 1 RX]: %d\n", mode);
		return mode;
	}
}
