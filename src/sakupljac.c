#include "sakupljac.h"

#ifdef NRF_H
	#define PACKET_SIZE		NRF_FIFO_SIZE
#else
	#define PACKET_SIZE		32
#endif

/*************************************************************************************************
				sakupljac_init()
*************************************************************************************************/
void sakupljac_init(void)
{
#ifdef NRF_H
	nRF_main();
#endif

	printf("%s() ovdje\n", __func__);
	print_remaining_stack();

	uint32_t polje[3] = {};

	print_remaining_stack();

	
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
	//printf("%s()\n", __func__);
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
	static char buffer[PACKET_SIZE] = {};
	
	int ret;
	ret = strcmp(cmd, CMD_SVJETLO);
	if (ret == 0)
	{
		uint8_t svjetlo = atoi(arg);
		//printf("%s(): Idemo postaviti svjelo na: %s %d\n", __func__, arg, svjetlo);
		printf("%s(): Idemo postaviti svjelo na: %d\n", __func__, svjetlo);
		// TODO provjere jel svjetlo 0 ili 1		kasnije 0..100 za PWM
		
		snprintf(buffer, sizeof(buffer), "%s:%s", cmd, arg);
		sakupljac_send(buffer, sizeof(buffer));
	}

	ret = strcmp(cmd, CMD_GRIJAC);
	if (ret == 0)
	{
		uint8_t grijac = atoi(arg);
		printf("%s(): Idemo postaviti grijac na: %d\n", __func__, grijac);
		// TODO provjere jel grijac 0 ili 1		kasnije 0..100 za PWM
		snprintf(buffer, sizeof(buffer), "%s:%s", cmd, arg);
		sakupljac_send(buffer, sizeof(buffer));
	}
}

/*************************************************************************************************
				sakupljac_send()
*************************************************************************************************/
void sakupljac_send(char *buffer, uint8_t length)
{
	printf("%s(): dobio buffer: %s, length: %d\n", __func__, buffer, length);

#ifdef NRF_H
	printf("%s(): Idemo poslat\n", __func__);
	nRF_write_status_t status = nRF_write(grf, buffer, length);
	printf("%s(): poslao\n", __func__);

	if (status == NRF_SEND_SUCCESS)
	{
		printf("%s(): nRF TX uspjesno poslao: \"%s\"\n", __func__, buffer);
	}
	else if (status == NRF_SEND_IN_PROGRESS)
	//if (status == NRF_SEND_IN_PROGRESS)
	{
		printf("%s(): nRF TX still sending, retransmit count: %d\n", __func__, nRF_get_retransmit_count(grf));
	}
	else if (status == NRF_SEND_FAILED)
	//if (status == NRF_SEND_FAILED)
	{
		//printf("%s(): nRF TX send failed\n", __func__);
		printf("%s(): nRF TX send failed, buffer: %s\n", __func__, buffer);
	}
	else if (status == NRF_SEND_TIMEOUT)
	//if (status == NRF_SEND_TIMEOUT)
	{
		printf("%s(): nRF TX software timeout\n", __func__);
	}
	else
	{
		printf("%s(): nRF TX doso do else\n", __func__);
	}
#endif
}
