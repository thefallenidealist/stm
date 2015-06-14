/*************************************************************************************************
				nRF_start_listening()
*************************************************************************************************/
static inline void nRF_start_listening(nRF_hw_t *nRF0)
{
	nRF_clear_bits(nRF0);
	nRF_flush_TX(nRF0);	
	nRF_flush_RX(nRF0);

	ce(nRF0, 1);	// Activate PRX mode by setting the CE pin high. page 37
	delay_us(130);	// datasheet v1.0, page 76
}

/*************************************************************************************************
				nRF_stop_listening()
*************************************************************************************************/
static inline void nRF_stop_listening(nRF_hw_t *nRF0)
{
	ce(nRF0, 0);

	nRF_flush_TX(nRF0);
	nRF_flush_RX(nRF0);
}
