#include "soba.h"

#define SOBA1_SVJETLO	"PA12"
#define SOBA1_GRIJAC	"PA11"
	// vec zauzet PB6, PB7
#define SOBA_PACKET_SIZE	NRF_FIFO_SIZE

/*************************************************************************************************
				soba_init()
*************************************************************************************************/
void soba_init(void)
{
	gpio_init(SOBA1_SVJETLO, OUT);
	gpio_init(SOBA1_GRIJAC, OUT);

	gpio_write(SOBA1_SVJETLO, 0);
	gpio_write(SOBA1_GRIJAC, 0);

	bmp180_init();
	nRF_main();
}

/*************************************************************************************************
				soba_set/get svasta
*************************************************************************************************/
void soba_set_svjetlo(bool arg)
{
	gpio_write(SOBA1_SVJETLO, arg);
}

bool soba_get_svjetlo(void)
{
	return gpio_read(SOBA1_SVJETLO);
}

void soba_set_grijac(bool arg)
{
	gpio_write(SOBA1_GRIJAC, arg);
}

bool soba_get_grijac(void)
{
	return gpio_read(SOBA1_GRIJAC);
}
/*************************************************************************************************/


/*************************************************************************************************
				soba_get_status()
*************************************************************************************************/
char *soba_get_status(void)
{

	soba_set_svjetlo(1);
	soba_set_grijac(1);

	static char status[SOBA_PACKET_SIZE] = {};

	float temperatura = bmp180_get_temperature();
	bool svjetlo = soba_get_svjetlo();
	bool grijac  = soba_get_grijac();

	/*
	printf("temperatura: %.1f C\n", temperatura);
	printf("svjetlo: %d\n", svjetlo);
	printf("grijac: %d\n", grijac);
	*/

	snprintf(status, sizeof(status), "s1_te:%02.1f_gr:%01d_sv:%01d", temperatura, grijac, svjetlo);
	printf("%s(), status: %s\n", __func__, status);
	return status;
}

/*************************************************************************************************
				soba_send_status()
*************************************************************************************************/
void soba_send_status(void)
{
	// nastimaj ACK
}
/*************************************************************************************************
				soba_main()
*************************************************************************************************/
void soba_main(void)
{
	soba_get_status();
	//soba_send_status();
}
