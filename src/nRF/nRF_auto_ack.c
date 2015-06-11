/*************************************************************************************************
				nRF_enable_auto_ack()
*************************************************************************************************/
void nRF_enable_auto_ack(nRF_hw_t *nRF0, nRF_pipe_t pipe)
{
	// defaultno su svi pajpovi enableani
	reg_tmp[pipe] = 1;
	write_reg(nRF0, REG_EN_AA);
}

/*************************************************************************************************
				nRF_disable_auto_ack()
*************************************************************************************************/
void nRF_disable_auto_ack(nRF_hw_t *nRF0, nRF_pipe_t pipe)
{
	reg_tmp[pipe] = 0;
	write_reg(nRF0, REG_EN_AA);
}
