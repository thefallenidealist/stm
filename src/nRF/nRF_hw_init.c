/*************************************************************************************************
				nRF_hw_init()
*************************************************************************************************/
int8_t nRF_hw_init(nRF_hw_t *nRF0)
{
	DEBUG_START;

	char *cs = nRF0->cs;
	char *ce = nRF0->ce;
	char *irq = nRF0->irq;
	uint16_t prescaler = nRF0->spi_prescaler;

	nRF0->mode = MODE_ERROR;

	if (strlen(cs) != 0)
	{
		//printf("%s(): cs: %s\n", __func__, cs);
		gpio_init(cs, OUT);
		gpio_write(cs, 1);
	}
	else
	{
		ERROR("CS pin not connected\n");
	}

	if (strlen(ce) != 0)
	{
		//printf("%s(): ce: %s\n", __func__, nRF0->ce);
		gpio_init(ce, OUT);
		gpio_write(ce, 0);
	}
	else
	{
		ERROR("CE pin not connected\n");
	}

	if (strlen(irq) != 0)
	{
		//printf("%s(): irq: %s\n", __func__, nRF0->irq);
		gpio_init(irq, IN);
		// TODO exti vanjski
	}
	else
	{
		DEBUG_INFO("IRQ pin not connected\n");
	}

	if (spi_init(nRF0->spi_port, prescaler))	// TODO ili oboje cp argument, ili oboje neCP
	{
		ERROR("SPI not initialized\n");

		DEBUG_END;
		return -1;
	}

	DEBUG_END;
	return 0;
}
