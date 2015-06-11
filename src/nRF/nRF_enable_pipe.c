/*************************************************************************************************
				nRF_enable_pipe()
*************************************************************************************************/
int8_t nRF_enable_pipe(nRF_hw_t *nRF0, nRF_pipe_t pipe)					// reg 0x02
{
	if (pipe > 5)
	{
		ERROR("Wrong pipe\n");
		return -1;
	}
	else
	{
		reg_tmp[pipe] = 1;	// ERX_Px = 1
		write_reg(nRF0, REG_EN_RXADDR);
		return 0;
	}
}

/*************************************************************************************************
				nRF_get_enabled_pipe()
*************************************************************************************************/
nRF_pipe_t nRF_get_enabled_pipe(nRF_hw_t *nRF0)
{
	uint8_t pipes = read_reg(nRF0, REG_EN_RXADDR);
	return pipes;
}

/*************************************************************************************************
				nRF_print_enabled_pipe()
*************************************************************************************************/
void nRF_print_enabled_pipe(nRF_hw_t *nRF0)
{
	uint8_t pipes = nRF_get_enabled_pipe(nRF0);

	printf("%s(): Enabled pipes: ", __func__);

	for (uint8_t i=0; i<8; i++)
	{
		if ( ((pipes >> i) & 1) == 1)
		{
			printf("P%d ", i);
		}
	}
	printf("\n");
}
