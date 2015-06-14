/*************************************************************************************************
				nRF_set_mode()
*************************************************************************************************/
void nRF_set_mode(nRF_hw_t *nRF0, nRF_mode_t mode)
{
	if (nRF0 == NULL)
	{
		ERROR("Wrong nRF module address\n");
		printf("Wrong nRF module address\n");
	}
	else if (mode > RX)
	{
		ERROR("Wrong mode\n");
		printf("Wrong mode\n");
	}
	else
	{
		if (mode == RX)
		{
			// pokusaj da se ne mora startat prvo RX modul pa onda TX
			delay_ms(5);	// worst case Tpd2stby

			nRF_clear_bits(nRF0);
			nRF_flush_TX(nRF0);
			nRF_flush_RX(nRF0);

			reg_tmp[PRIM_RX] = 1;
			write_reg(nRF0, REG_CONFIG);

			ce(nRF0, 1);	// start listening
			delay_us(130);	// TX/RX settling, datasheet page 22
		}
		else if (mode == TX)
		{
			delay_ms(5);	// worst case Tpd2stby

			reg_tmp[PRIM_RX] = 0;
			write_reg(nRF0, REG_CONFIG);

			ce(nRF0, 0);
			delay_us(130);	// TX/RX settling, datasheet page 22
		}
		else
		{
			ERROR("Wrong mode\n");
			printf("Wrong mode\n");
		}
	}
}

/*************************************************************************************************
				nRF_get_mode()
*************************************************************************************************/
nRF_mode_t nRF_get_mode(nRF_hw_t *nRF0)
{
	nRF_mode_t mode = MODE_ERROR;

	uint8_t status = read_reg(nRF0, REG_CONFIG);
	mode = status & 1;

	return mode;
}
