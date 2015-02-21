#include "flash.h"

int8_t flash_init(flash_hw_t *flash0)
{
	char *cs = flash0->cs;

	uint8_t spi_port = flash0->spi_port;
	uint16_t prescaler = flash0->spi_prescaler;

	gpio_init(cs, OUT);
	spi_init(spi_port, prescaler);

	return 0;
}

void flash_main()
{
	printf("%s()\n", __func__);
}
