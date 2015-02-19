#include "nRF_novi.h"
#include "nRF_reg.c" 		// TODO malo bolje, ne includeat .c

/*************************************************************************************************
				nRF_main()
*************************************************************************************************/
void nRF_main()
{
	DEBUG_START;

	nRF_hw_t bezicni;

	bezicni.spi_port = 1;
	//bezicni.spi_speed_MHz = 
	bezicni.spi_prescaler = 32;
	bezicni.cs = "PB5";
	bezicni.ce = "PB4";
	//bezicni.irq = "PB3";	// NC

	if (nRF_init(&bezicni) != 0)
	{
		ERROR("module not initialized\n");
		// return -1;
	}
	delay_ms(11);	// 10.3 ms


	printf("nRF je odradio hardverski init\n");

#define	REG_CONFIG	0x00
#define PWR_UP		1	// 1: POWER UP, 0:POWER DOWN

	// power up
	write_reg(&bezicni, REG_CONFIG, (1 << PWR_UP));
	delay_ms(2);	// 1.5ms
	// sad je u Standby-1 modu

	printf("idemo citat registre\n");
	print_reg(&bezicni, 0x00);
	print_reg(&bezicni, 0x01);
	print_reg(&bezicni, 0x02);
	print_reg(&bezicni, 0x03);


	DEBUG_END;
}

/*************************************************************************************************
				nRF_init()
*************************************************************************************************/
int8_t nRF_init(nRF_hw_t *nRF0)
{
	DEBUG_START;

	char *cs = nRF0->cs;
	char *ce = nRF0->ce;
	char *irq = nRF0->irq;
	uint16_t prescaler = nRF0->spi_prescaler;

	if (strlen(cs) != 0)
	{
		//printf("%s(): cs: %s\n", __func__, cs);
		gpio_init(cs, OUT);
	}
	else
	{
		ERROR("CS pin not connected\n");
	}

	if (strlen(ce) != 0)
	{
		//printf("%s(): ce: %s\n", __func__, nRF0->ce);
		gpio_init(ce, OUT);
	}
	else
	{
		ERROR("CE pin not connected\n");
	}

	if (strlen(irq) != 0)
	{
		//printf("%s(): irq: %s\n", __func__, nRF0->irq);
		gpio_init(irq, IN);
	}
	else
	{
		DEBUG_INFO("IRQ pin not connected\n");
	}

	if (spi_init(1, prescaler))
	{
		ERROR("SPI not initialized\n");

		DEBUG_END;
		return -1;
	}

	DEBUG_END;
	return 0;
}


/*************************************************************************************************
				ce()
*************************************************************************************************/
static void ce(nRF_hw_t *nRF0, state_t state)
{
	char *ce = nRF0->ce;
	gpio(ce, state);
}

/*************************************************************************************************
				cs()
*************************************************************************************************/
static void cs(nRF_hw_t *nRF0, state_t state)
{
	char *cs = nRF0->cs;
	gpio(cs, state);
}

/*************************************************************************************************
				read_reg()
*************************************************************************************************/
static uint8_t read_reg(nRF_hw_t *nRF0, uint8_t reg)
{
	DEBUG_START;
	uint8_t status;
	uint8_t spi_port = nRF0->spi_port;

	cs(nRF0, 0);
	//spi_rw(CMD_R_REGISTER + reg);	// ako citanje REG_STATUS bude zajebavalo ovo zakomentirat samo u tom slucaju
	//status = spi_rw(0x00);	// dummy write
	spi_rw(spi_port, CMD_R_REGISTER + reg);
	status = spi_rw(spi_port, 0x00);	// dummy write
	cs(nRF0, 1);

	DEBUG_END;
	return status;
}
/*************************************************************************************************
				print_reg()
*************************************************************************************************/
static void print_reg(nRF_hw_t *nRF0, uint8_t reg)
{
	DEBUG_START;

	uint8_t status = read_reg(nRF0, reg);
	printf("reading reg: 0x%X: %d\n", reg, status);	
	for (int i=0; i<8; i++)
	{
		printf("reg bit %d: %d\n", i, ((status >> i) & 1));
	}

	DEBUG_END;
	printf("\n");
}

/*************************************************************************************************
				write_reg()
*************************************************************************************************/
static uint8_t write_reg(nRF_hw_t *nRF0, uint8_t reg, uint8_t arg)
{
	DEBUG_START;
	printf("write reg: reg: 0x%X, value: %d\n", reg, arg);

	uint8_t status;
	//char *cs = nRF0->cs;
	uint8_t spi_port = nRF0->spi_port;

	cs(nRF0, 0);
	//status = spi_rw(reg + CMD_W_REGISTER);
	status = spi_rw(spi_port, reg + CMD_W_REGISTER);
	spi_rw(spi_port, arg);

	delay_ms(1);	// bezveze

	cs(nRF0, 1);

	DEBUG_END;
	return status;
}
