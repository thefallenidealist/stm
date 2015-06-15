/*************************************************************************************************
				nRF_write_ack()
*************************************************************************************************/
void nRF_write_ack(nRF_hw_t *nRF0, char *buffer, uint8_t length)
{
	// samo zapisi payload u TX FIFO, nemoj slat (togglat CE)
	uint8_t spi_port = nRF0->spi_port;

	/*
	// DEBUG TODO
#define SIZE 16
	uint8_t length = SIZE;
	static uint8_t counter;

	char cbuffer[33] = {};
	char *buffer = cbuffer;
	snprintf(buffer, SIZE, "PRX ACK %02d", counter++);
	*/

	uint8_t pipe = 0;

	if (nRF_is_TX_full(nRF0) == 1)
	{
		printf("%s(): Zajeb, TX is full, exiting\n", __func__);
		return ;
	}

	cs(nRF0, 0);
	spi_rw(spi_port, (CMD_W_ACK_PAYLOAD | pipe));
	while (length--)
	{
		spi_rw(spi_port, *buffer++);
	}
	cs(nRF0, 1);
}

/*************************************************************************************************
				nRF_read_ack()
*************************************************************************************************/
char *nRF_read_ack(nRF_hw_t *nRF0)	
{
	if (nRF_is_RX_full(nRF0) == 1)
	{
		printf("%s(): Zajeb, RX is full, flushing and ______exiting\n", __func__);
		nRF_flush_RX(nRF0);
		//return;		TODO
	}

	char *ack_buffer = nRF0->RX_buffer;
	uint8_t spi_port = nRF0->spi_port;

	uint8_t length = nRF_get_dynamic_payload_length(nRF0);

	nRF_clear_buffer(ack_buffer);
	ack_buffer = nRF0->RX_buffer;	// vrati pointer na pocetak

	cs(nRF0, 0);
	spi_rw(spi_port, CMD_R_RX_PAYLOAD);
	for (uint8_t i=0 ; i<length; i++)
	{
		ack_buffer[i] = spi_rw(spi_port, CMD_NOP);
	}
	cs(nRF0, 1);
	ack_buffer = nRF0->RX_buffer;	// vrati pointer na pocetak
	nRF_clear_RX_data_ready(nRF0);

	return ack_buffer;	// jebena konjino
}

// TODO testirat ovo sranje
/*************************************************************************************************
				nRF_write_payload_no_ack()
*************************************************************************************************/
void nRF_write_payload_no_ack(nRF_hw_t *nRF0, char *buffer, uint8_t length)
{
	if (length > 32)
	{
		printf("%s(): Zajeb, length (%d) larger than 32, exiting\n", __func__, length);
		return ;
	}

	uint8_t spi_port = nRF0->spi_port;

  	// write payload
	cs(nRF0, 0);
	spi_rw(spi_port, CMD_W_TX_PAYLOAD_NO_ACK);
	while (length--)
	{
		spi_rw(spi_port, *buffer++);
	}
	cs(nRF0, 1);
}
