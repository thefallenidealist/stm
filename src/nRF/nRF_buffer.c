/*************************************************************************************************
				nRF_clear_buffer()
*************************************************************************************************/
static inline void nRF_clear_buffer(char *buffer)
{
	for (uint8_t i=0; i<NRF_FIFO_SIZE+1; i++)	// 32+1 neka se nadje mjesta za NULL char
	{
		buffer[i] = '\0';
	}
}
