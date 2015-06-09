/*************************************************************************************************
				nRF_enable_dynamic_payload()
*************************************************************************************************/
void nRF_enable_dynamic_payload(nRF_hw_t *nRF0)
{
	uint8_t spi_port = nRF0->spi_port;

	cs(nRF0, 0);
	spi_rw(spi_port, CMD_ACTIVATE);	// potrebno za aktivirat spesl ficrse
	spi_rw(spi_port, 0x73);
	cs(nRF0, 1);

	// INFO override the pipes "RX_PW" setting
	reg_tmp[EN_DPL] = 1;
	write_reg(nRF0, REG_FEATURE);
}

/*************************************************************************************************
				nRF_disable_dynamic_payload()
*************************************************************************************************/
void nRF_disable_dynamic_payload(nRF_hw_t *nRF0)
{
	reg_tmp[EN_DPL] = 0;
	write_reg(nRF0, REG_FEATURE);
}

/*************************************************************************************************
				nRF_enable_dynamic_payload_ack()
*************************************************************************************************/
void nRF_enable_dynamic_payload_ack(nRF_hw_t *nRF0)
{
	/*
	If ACK packet payload is activated, ACK packets have dynamic payload lengths and the Dynamic Payload 
	Length feature should be enabled for pipe 0 on the PTX and PRX. This is to ensure that they receive the 
	ACK packets with payloads. If the ACK payload is more than 15 byte in 2Mbps mode the ARD must be 
	500µS or more, and if the ACK payload is more than 5 byte in 1Mbps mode the ARD must be 500µS or 
	more. In 250kbps mode (even when the payload is not in ACK) the ARD must be 500µS or more.
	*/
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
	// Enables the W_TX_PAYLOAD_NOACK command
	reg_tmp[EN_DYN_ACK] = 1;
	write_reg(nRF0, REG_FEATURE);
}

/*************************************************************************************************
				nRF_disable_dynamic_payload_noack()
*************************************************************************************************/
void nRF_disable_dynamic_payload_noack(nRF_hw_t *nRF0)
{
	// Enables the W_TX_PAYLOAD_NOACK command
	reg_tmp[EN_DYN_ACK] = 1;
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

	// just in case
	nRF_enable_dynamic_payload(nRF0);
	nRF_enable_auto_ack(nRF0, pipe);

	reg_tmp[pipe] = 1;	// DPL_Px = 1
	write_reg(nRF0, REG_DYNPD);

}

/*************************************************************************************************
				nRF_disable_dynamic_pipe()
*************************************************************************************************/
void nRF_disable_dynamic_pipe(nRF_hw_t *nRF0, nRF_pipe_t pipe)
{
	// TODO
}

/*************************************************************************************************
				nRF_get_dynamic_payload_length()
*************************************************************************************************/
uint8_t nRF_get_dynamic_payload_length(nRF_hw_t *nRF0, nRF_pipe_t pipe)
{
	// The length of the received payload is read by the SPI command "R_RX_PL_WID."

	uint8_t spi_port = nRF0->spi_port;
	uint8_t length = 0xFF;

	ce(nRF0, 0);
	length = spi_rw(spi_port, CMD_R_RX_PL_WID);
	ce(nRF0, 1);

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
