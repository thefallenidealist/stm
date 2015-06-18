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

/*************************************************************************************************
				sakupljac_parse()
*************************************************************************************************/
#define CMD_SVJETLO	"set_svjetlo"
#define CMD_GRIJAC	"set_grijac"

void sakupljac_parse(char *cmd, char *arg)
{
	// UART IRQ dobije string "cmd:abcd", pozove uart_parse(), ako ima delimiter ':', ovaj razbije i pozove uart_cmd() koja to samo 
	// proslijedi ovoj funkciji
	
	//printf("%s(): cmd: %s, arg: %s\n", __func__, cmd, arg);
	
	int ret;
	ret = strcmp(cmd, CMD_SVJETLO);
	if (ret == 0)
	{
		uint8_t svjetlo = atoi(arg);
		//printf("%s(): Idemo postaviti svjelo na: %s %d\n", __func__, arg, svjetlo);
		printf("%s(): Idemo postaviti svjelo na: %d\n", __func__, svjetlo);
		// TODO provjere jel svjetlo 0 ili 1		kasnije 0..100 za PWM
	}

	ret = strcmp(cmd, CMD_GRIJAC);
	if (ret == 0)
	{
		uint8_t grijac = atoi(arg);
		printf("%s(): Idemo postaviti grijac na: %d\n", __func__, grijac);
		// TODO provjere jel grijac 0 ili 1		kasnije 0..100 za PWM
	}
}
