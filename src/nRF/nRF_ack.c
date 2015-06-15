// TODO provjerit sve funkcije iz ovog fajla
/*************************************************************************************************
				nRF_write_ack()
*************************************************************************************************/
/*
void nRF_prepare_ack(nRF_hw_t *nRF0)
{
	// zapisi samo ono sto cemo posalt kao ACK u TX FIFO
	char ctx_buffer[] = "PRX salje nazad";
	char *tx_buffer = ctx_buffer;
	uint8_t spi_port = grf->spi_port;
	uint8_t length = 5;

	// zapuni buffer prije nego sto dobije podatke
	cs(nRF0, 0);
	spi_rw(spi_port, CMD_W_TX_PAYLOAD);
	while (length--)
	{
		spi_rw(spi_port, *tx_buffer++);
	}
	cs(nRF0, 1);
}
*/

/*************************************************************************************************
				nRF_write_ack()
*************************************************************************************************/
void nRF_write_ack(nRF_hw_t *nRF0)
{
	// samo zapisi payload u TX FIFO, nemoj slat (togglat CE)
	uint8_t spi_port = nRF0->spi_port;

	// DEBUG TODO
#define SIZE 10
	uint8_t length = SIZE;
	char cbuffer[SIZE] = "PRX ACK";
	char *buffer = cbuffer;
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
//uint8_t *nRF_read_ack(nRF_hw_t *nRF0)	// vrati pointer na svoj buffer;
char *nRF_read_ack(nRF_hw_t *nRF0)	// vrati pointer na svoj buffer;
{
	if (nRF_is_RX_full(nRF0) == 1)
	{
		printf("%s(): Zajeb, RX is full, flushing and ______exiting\n", __func__);
		nRF_flush_RX(nRF0);
		//return;		TODO
	}

	//static uint8_t ack_buffer[32] = {};
	static char ack_buffer[32] = {};
	uint8_t spi_port = nRF0->spi_port;

	uint8_t length = nRF_get_dynamic_payload_length(nRF0);

	printf("%s(): length: %d\n", __func__, length);

	cs(nRF0, 0);
	spi_rw(spi_port, CMD_R_RX_PAYLOAD);
	for (uint8_t i=0 ; i<length; i++)
	{
		//ack_buffer[i] = spi_rw(spi_port, 0x00);
		ack_buffer[i] = spi_rw(spi_port, CMD_NOP);
	}
	cs(nRF0, 1);

}

/*************************************************************************************************
				nRF_write_payload_no_ack()
*************************************************************************************************/
void nRF_write_payload_no_ack(nRF_hw_t *nRF0, char *buffer, uint8_t length)
{
	// INFO
	// zapravo isti nRF_write_payload() osim sto salje drugi CMD
	// TODO mora bit omogucen EN_DYN_ACK u REG_FEATURE da bi ovo radilo, page 63


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

	/*
	// pulse CE for transmission
	ce(nRF0, 1);
	delay_us(11);	// 10+ us
	ce(nRF0, 0);
	*/
}
