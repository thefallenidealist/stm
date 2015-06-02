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
		if ( (mode == RX) || (mode == TX) )
		{
			reg_tmp[PRIM_RX] = mode;
			write_reg(nRF0, REG_CONFIG);
			delay_us(130);	// TX/RX settling, datasheet page 22
			// zapisi i u objekt
			nRF0->mode = mode;
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
