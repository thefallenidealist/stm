static bool g_reg_feature_enabled = 0;
/*************************************************************************************************
				nRF_enable_dynamic_payload()
*************************************************************************************************/
void nRF_enable_FEATURE(nRF_hw_t *nRF0)
{
	// only in power down or standby mode (when CE is 0);
	if (g_reg_feature_enabled == 0)
	{
		uint8_t spi_port = nRF0->spi_port;

		cs(nRF0, 0);
		spi_rw(spi_port, CMD_ACTIVATE);	// potrebno za aktivirat spesl ficrse
		spi_rw(spi_port, 0x73);
		cs(nRF0, 1);

		printf("\t\tREG_FEATURE enabled\n");
	}
	else
	{
		printf("%s(): REG_FEATURE is already activated, variable: %d\n", __func__,
				g_reg_feature_enabled);
	}
}

/*************************************************************************************************
				nRF_enable_dynamic_payload()
*************************************************************************************************/
void nRF_enable_dynamic_payload(nRF_hw_t *nRF0)
{
	nRF_enable_FEATURE(nRF0);

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
	// Disables the W_TX_PAYLOAD_NOACK command
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

	// just in case
	//nRF_enable_dynamic_payload(nRF0);
	//nRF_enable_auto_ack(nRF0, pipe);

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
uint8_t nRF_get_dynamic_payload_length(nRF_hw_t *nRF0)
{
	// The length of the received payload is read by the SPI command "R_RX_PL_WID."

	uint8_t spi_port = nRF0->spi_port;
	uint8_t length = 0xFF;

	cs(nRF0, 0);
	//length = spi_rw(spi_port, CMD_R_RX_PL_WID);
	spi_rw(spi_port, CMD_R_RX_PL_WID);
	length = spi_rw(spi_port, 0);		// pokusaj
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

/*************************************************************************************************
**************************************************************************************************
**************************************************************************************************
**************************************************************************************************
**************************************************************************************************
*************************************************************************************************/
// novo 150609
void nRF_enable_feature_dynPL(nRF_hw_t *nRF0, nRF_pipe_t pipe)
{
	// ACTIVATE
	uint8_t spi_port = nRF0->spi_port;

	cs(nRF0, 0);
	spi_rw(spi_port, CMD_ACTIVATE);
	spi_rw(spi_port, 0x73);
	cs(nRF0, 1);

	// activate EN_DPL
	reg_tmp[EN_DPL] = 1;
	write_reg(nRF0, REG_FEATURE);

	// enable pipe
	nRF_enable_dynamic_pipe(nRF0, pipe);
}

//NRF24L01_EnableFeatureAckPL
void nRF_enable_feature_ackPL(nRF_hw_t *nRF0)
{
	nRF_enable_feature_dynPL(nRF0, P0);
	// set ARD TODO
	// enable autoACK
	reg_tmp[EN_ACK_PAY] = 1;
	write_reg(nRF0, REG_FEATURE);
}

// SetAckPayload
void nRF_set_ACK_payload(nRF_hw_t *nRF0, nRF_pipe_t pipe, char *buffer, uint8_t length)
{
	// moj pokusaj

	nRF_set_mode(nRF0, TX);
	delay_us(130);




	bool TX_full = nRF_is_TX_full(nRF0);

	if (TX_full == 1)
	{
		printf("TX is full\n");
	}
	else
	{
		uint8_t spi_port = nRF0->spi_port;

		cs(nRF0, 0);
		spi_rw(spi_port, CMD_W_ACK_PAYLOAD);
		while (length--)
		{
			spi_rw(spi_port, *buffer++);
		}
		cs(nRF0, 1);

		// pulse CE for transmission
		ce(nRF0, 1);
		delay_us(11);	// 10+ us
		ce(nRF0, 0);
	}

	nRF_set_mode(nRF0, RX);
	delay_us(130);

	printf("%s() kraj\n", __func__);
}


