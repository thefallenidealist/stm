#include "sakupljac.h"

#define PACKET_SIZE		NRF_FIFO_SIZE

/*************************************************************************************************
				sakupljac_init()
*************************************************************************************************/
void sakupljac_init(void)
{
	nRF_main();
	
}

/*************************************************************************************************
				sakupljac_main()
*************************************************************************************************/
void sakupljac_main(void)
{
	// sakupljac (PTX) posalje bilo sta na sobe (PRX) i ove vrate status
	// ne salji nista dok ne dobijes komandu sa serijskog
	
	/*
	if (komanda_sa_serijkog)
	{
		static char sakupljac_buffer[PACKET_SIZE] = {};
		char *buffer = sakupljac_buffer;
		uint8_t length = PACKET_SIZE;

		nRF_write_status_t status = nRF_write(grf, buffer, length);

		if (status == NRF_SEND_SUCCESS)
		{
				printf("%s(): nRF TX uspjesno poslao: \"%s\"\n", __func__, buffer);
		}
		//else if (status == NRF_SEND_IN_PROGRESS)
		if (status == NRF_SEND_IN_PROGRESS)
		{
				printf("%s(): nRF TX still sending, retransmit count: %d\n", __func__, nRF_get_retransmit_count(grf));
		}
		//else if (status == NRF_SEND_FAILED)
		if (status == NRF_SEND_FAILED)
		{
				//printf("%s(): nRF TX send failed\n", __func__);
				printf("%s(): nRF TX send failed, buffer: %s\n", __func__, buffer);
		}
		//else if (status == NRF_SEND_TIMEOUT)
		if (status == NRF_SEND_TIMEOUT)
		{
				printf("%s(): nRF TX software timeout\n", __func__);
		}


		delay_ms(500);
	}
	*/
}
