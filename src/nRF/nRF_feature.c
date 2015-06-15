/*************************************************************************************************
				nRF_enable_dynamic_payload()
*************************************************************************************************/
void nRF_enable_dynamic_payload(nRF_hw_t *nRF0)
{
	// INFO override the pipes "RX_PW" setting
	reg_tmp[EN_DPL] = 1;
	write_reg(nRF0, REG_FEATURE);

	nRF0->dynamic_payload = 1;
}

/*************************************************************************************************
				nRF_disable_dynamic_payload()
*************************************************************************************************/
void nRF_disable_dynamic_payload(nRF_hw_t *nRF0)
{
	reg_tmp[EN_DPL] = 0;
	write_reg(nRF0, REG_FEATURE);

	nRF0->dynamic_payload = 0;
}

/*************************************************************************************************
				nRF_is_dynamic_payload_enabled()
*************************************************************************************************/
bool nRF_is_dynamic_payload_enabled(nRF_hw_t *nRF0)
{
	// faster than register read
	//return nRF0->dynamic_payload;
	// zna se sjebat iako prodje init i REG_FEATURE = 0x00
	uint8_t reg_value = read_reg(nRF0, REG_FEATURE);

	printf("%s(): reg_value (FEATURE): %d\n", __func__, reg_value);

	if (reg_value != 0x00)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*************************************************************************************************
				nRF_enable_dynamic_payload_ack()
*************************************************************************************************/
void nRF_enable_dynamic_payload_ack(nRF_hw_t *nRF0)
{
	reg_tmp[EN_ACK_PAY] = 1;
	write_reg(nRF0, REG_FEATURE);
}

/*************************************************************************************************
				nRF_disable_dynamic_payload_ack()
*************************************************************************************************/
void nRF_disable_dynamic_payload_ack(nRF_hw_t *nRF0)
{
	reg_tmp[EN_ACK_PAY] = 0;
	write_reg(nRF0, REG_FEATURE);
}

/*************************************************************************************************
				nRF_enable_dynamic_payload_noack()
*************************************************************************************************/
void nRF_enable_dynamic_payload_noack(nRF_hw_t *nRF0)
{
	// INFO Enables the W_TX_PAYLOAD_NOACK command
	reg_tmp[EN_DYN_ACK] = 1;
	write_reg(nRF0, REG_FEATURE);
}

/*************************************************************************************************
				nRF_disable_dynamic_payload_noack()
*************************************************************************************************/
void nRF_disable_dynamic_payload_noack(nRF_hw_t *nRF0)
{
	reg_tmp[EN_DYN_ACK] = 0;
	write_reg(nRF0, REG_FEATURE);
}

/*************************************************************************************************
				nRF_enable_dynamic_pipe()
*************************************************************************************************/
void nRF_enable_dynamic_pipe(nRF_hw_t *nRF0, nRF_pipe_t pipe)
{
	if (pipe > 5)
	{
		printf("%s(): Zajeb, pipe number %d is larger than 5, exiting.\n", __func__, pipe);
		return;
	}

	// Enable dynamic payload length data pipe N.
	// (Requires EN_DPL and ENAA_PN)

	reg_tmp[pipe] = 1;	// DPL_Px = 1
	write_reg(nRF0, REG_DYNPD);

}

/*************************************************************************************************
				nRF_disable_dynamic_pipe()
*************************************************************************************************/
void nRF_disable_dynamic_pipe(nRF_hw_t *nRF0, nRF_pipe_t pipe)
{
	if (pipe > 5)
	{
		printf("%s(): Zajeb, pipe number %d is larger than 5, exiting.\n", __func__, pipe);
		return;
	}

	reg_tmp[pipe] = 0;	// DPL_Px = 0
	write_reg(nRF0, REG_DYNPD);
}

/*************************************************************************************************
				nRF_get_dynamic_payload_length()
*************************************************************************************************/
uint8_t nRF_get_dynamic_payload_length(nRF_hw_t *nRF0)
{
	uint8_t spi_port = nRF0->spi_port;
	uint8_t length = 0xFF;	// invalid payload length

	cs(nRF0, 0);
	spi_rw(spi_port, CMD_R_RX_PL_WID);
	length = spi_rw(spi_port, CMD_NOP);
	cs(nRF0, 1);

	/*
	Always check if the packet width reported is 32 bytes or shorter when using the 
	R_RX_PL_WID command. If its width is longer than 32 bytes then the packet contains errors 
	and must be discarded. Discard the packet by using the Flush_RX command.
	*/
	if (length > 32)
	{
		nRF_flush_RX(nRF0);
		return 0xFF;
	}

	return length;
}
