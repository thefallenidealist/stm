/*************************************************************************************************
				nRF_hw_init()
*************************************************************************************************/
int8_t nRF_hw_init(nRF_hw_t *nRF0)
{
	DEBUG_START;

	char *cs = nRF0->cs;
	char *ce = nRF0->ce;
	char *irq = nRF0->irq;
	uint8_t  spi_port = nRF0->spi_port;
	uint16_t prescaler = nRF0->spi_prescaler;

	//nRF0->mode = MODE_ERROR;
	nRF0->dynamic_payload = 0;

	if (strlen(cs) != 0)
	{
		gpio_init(cs, OUT);
		gpio_write(cs, 1);
	}
	else
	{
		ERROR("CS pin not connected\n");
	}

	if (strlen(ce) != 0)
	{
		gpio_init(ce, OUT);
		gpio_write(ce, 0);
	}
	else
	{
		ERROR("CE pin not connected\n");
	}

	if (strlen(irq) != 0)
	{
		gpio_init(irq, IN);
		// TODO exti vanjski
	}
	else
	{
		DEBUG_INFO("IRQ pin not connected\n");
	}

	if (spi_init(spi_port, prescaler))	
	{
		ERROR("SPI not initialized\n");

		DEBUG_END;
		return -1;
	}

	DEBUG_END;
	return 0;
}
