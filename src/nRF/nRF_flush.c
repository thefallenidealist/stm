/*************************************************************************************************
				nRF_flush_TX()
*************************************************************************************************/
void nRF_flush_TX(nRF_hw_t *nRF0)
{
	// used in TX mode
	uint8_t spi_port = nRF0->spi_port;

	cs(nRF0, 0);
	spi_rw(spi_port, CMD_FLUSH_TX);
	cs(nRF0, 1);
}

/*************************************************************************************************
				nRF_flush_RX()
*************************************************************************************************/
void nRF_flush_RX(nRF_hw_t *nRF0)
{
	/*
	Used for a PTX device
	Reuse last transmitted payload. Packets are 
	repeatedly retransmitted as long as CE is high.
	TX payload reuse is active until 
	W_TX_PAYLOAD or FLUSH TX is executed. TX 
	payload reuse must not be activated or deacti-
	vated during package transmission
	*/
	uint8_t spi_port = nRF0->spi_port;

	cs(nRF0, 0);
	spi_rw(spi_port, CMD_FLUSH_RX);
	cs(nRF0, 1);
}
