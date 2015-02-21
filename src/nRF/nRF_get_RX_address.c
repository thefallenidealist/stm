/*************************************************************************************************
				nRF_get_RX_address()
*************************************************************************************************/
uint8_t *nRF_get_RX_address(nRF_hw_t *nRF0)				// reg 0x0{A,B,C,D,E,F}
{
	// TODO zasad koristi samo pipe0 iako moze procitat adrese ostalih pipeova
	uint8_t pipe = 0;

	return nRF0->rx_address[pipe];
}
