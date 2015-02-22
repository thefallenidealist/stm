/*************************************************************************************************
				nRF_enable_pipe()
*************************************************************************************************/
int8_t nRF_enable_pipe(nRF_hw_t *nRF0, pipe_t pipe)					// reg 0x02
{

	//printf("%s(): argument: %d\n", __func__, pipe);

	// samo jednu po jednu XXX
	if (pipe > 5)
	{
		ERROR("Wrong pipe\n");
		return -1;
	}
	else
	{
		write_reg_full(nRF0, REG_EN_RXADDR, (1 << pipe));	// kad se enablea samo jedna
		return 0;
	}
}
