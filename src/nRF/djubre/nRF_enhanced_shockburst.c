/*************************************************************************************************
				nRF_disable_enhanced_shockburst()
*************************************************************************************************/
void nRF_disable_enhanced_shockburst(nRF_hw_t *nRF0)
{
	/*
	You must disable Enhanced ShockBurst™ for backward compatibility with the nRF2401A, nRF2402, 
	nRF24E1 and nRF24E2. Set the register EN_AA = 0x00 and ARC = 0 to disable Enhanced ShockBurst™. 
	In addition, the nRF24L01+ air data rate must be set to 1Mbps or 250kbps.
	*/
	write_reg_full(nRF0, REG_EN_AA, 0x00);
	nRF_set_retransmit_count(nRF0, 0);

	//The CRC is optional in the ShockBurst
}

/*************************************************************************************************
				nRF_enable_enhanced_shockburst()
*************************************************************************************************/
void nRF_enable_enhanced_shockburst(nRF_hw_t *nRF0)
{
	// TODO
	// po defaultu je u enhanced ShockBurstu?
}
