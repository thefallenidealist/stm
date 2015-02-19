#include "nRF_struct.h"

//nRF_hw_t gobj[10];
nRF_hw_t obj_array[10];
//int globalna = 2;

/*
static void spi_init(uint8_t spi_number)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	SPI_InitTypeDef		SPI_InitStructure;


	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

	SPI_InitStructure.SPI_Direction	= SPI_Direction_2Lines_FullDuplex;	// separate MOSI and MISO
	SPI_InitStructure.SPI_Mode	= SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize	= SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL	= SPI_CPOL_Low;		// nRF CPOL = 0
	SPI_InitStructure.SPI_CPHA	= SPI_CPHA_1Edge;	// nRF CPHA = 0
	// NRF max = 8
	// TODO neka prescaler dobije kao argument
	SPI_InitStructure.SPI_BaudRatePrescaler	= SPI_BaudRatePrescaler_64;	// zasad 1.125 MHz
	SPI_InitStructure.SPI_FirstBit		= SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial	= 7;

	if (spi_number == 1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);	// SPI1

		GPIO_InitStructure.GPIO_Pin = SPI1_SCK | SPI1_MISO | SPI1_MOSI;		// SPI1
		GPIO_Init(SPI1_PORT, &GPIO_InitStructure);				// SPI1

		SPI_Cmd(SPI1, ENABLE);			// SPI1
		SPI_Init(SPI1, &SPI_InitStructure);	// SPI1
	}
	// TODO SPI2
	else
	{
		printf("error: spi_init(): TODO SPI2\n");
	}
}
*/

/*************************************************************************************************
  		parse_spi()
*************************************************************************************************/
static int parse_spi(const char *arg)
{
	int ret = -9;	// defaultna, pogresna vrijednost

	ret = strncmp(arg, "SPI", 3);
	if (ret == 0)
	{
		uint8_t spi_number = atoi(&arg[3]);
		if (spi_number != 0)
		{
			if (spi_number >= 3)
			{
				printf("nRF_init(): STM32F1x doesn't have SPI%d.\n", spi_number);
				return EXIT_WRONG_SPI_NUMBER;
			}
			printf("SPI je SPI%d\n", spi_number);

			//arg->pins.spi_number = spi_number;	// zajeb, ne dobije struct kao argument
								// ako dobije struct kao argument razjebe ostatak

			// sve oke pozovi SPI init
			printf("pozivam spi_init()\n");
			spi_init(spi_number);
		}
		else
		{
			printf("nRF_init(): Wrong SPI number!\n");
			return EXIT_WRONG_SPI_NUMBER;
		}
	}
	else
	{
		printf("nRF_init(): Wrong SPI: %s.\n", arg);
		return EXIT_WRONG_SPI;
	}

	return EXIT_SUCCESS;
}

/*************************************************************************************************
  		nRF_init()
*************************************************************************************************/
static int nRF_init(nRF_hw_t *self)
{
	int ret;
	ret = parse_spi(self->spi);

	if (ret)
	{
		printf("error parse_spi() failed, exit code: %d\n", ret);
		return EXIT_FAILED;
	}

	//ret = parse_gpio("CS", self->cs);
	ret = parse_gpio("CS", self->cs, OUT);
	if (ret)
	{
		printf("error parse_gpio() for %s failed, exit code: %d\n", "CS", ret);
		return EXIT_FAILED;
	}

	//ret = parse_gpio("CE", self->ce);
	ret = parse_gpio("CE", self->ce, OUT);
	if (ret)
	{
		printf("error parse_gpio() for %s failed, exit code: %d\n", "CE", ret);
		return EXIT_FAILED;
	}

	//ret = parse_gpio("IRQ", self->irq);
	ret = parse_gpio("IRQ", self->irq, IN);
	if (ret)
	{
		printf("error parse_gpio() for %s failed, exit code: %d\n", "IRQ", ret);
		return EXIT_FAILED;
	}

	return EXIT_SUCCESS;
}

/*************************************************************************************************
  		nRF_constructor()
*************************************************************************************************/
static void nRF_constructor(nRF_hw_t *self)
{
	// kao konstruktor, popuni neispravnim defaultnim vrijednostima
	// koje ce se kasnije provjeravat
	self->spi = "X0";
	self->cs  = "X0";
	self->ce  = "X0";
	self->irq = "X0";
}

/*************************************************************************************************
  		nRF_print()
*************************************************************************************************/
static void nRF_print(nRF_hw_t *self)
{
	printf("nRF_print():\n");
	printf("\time: %s\n", self->name);
	printf("\tSPI: %s\n", self->spi);
	printf("\tCS: %s\n", self->cs);
	printf("\tCE: %s\n", self->ce);
	printf("\tIRQ: %s\n", self->irq);
}


/*************************************************************************************************
  						public function
*************************************************************************************************/
/*************************************************************************************************
  		nRF_new()
*************************************************************************************************/
// kreiraj novi objekt i inicijaliziraj ga
nRF_hw_t *nRF_new(const char *name)
{
	// TODO
	// kako napravit npr int var`echo $name`;
	//printf("_new: %p\n", &gobj);

	static uint8_t counter;

	//printf("odje nRF_new()\n");
	//printf("argument: %s\n", name);

	nRF_hw_t obj1;
	nRF_constructor(&obj1);		// zapuni defaultnim vrijednostima
	obj1.name = (char *)name;	// XXX zasto ga imam kao const ako ga moram pretvorit :-/

	obj1.init = nRF_init;
	obj1.print = nRF_print;

	void *pointer = obj_array;
	printf("void pointer: %p\n", pointer);
	printf("napisi sta oces %p\n", &obj_array[counter]);

	memcpy(&obj_array[counter], &obj1, sizeof(obj1));
	printf("obj_array[counter] addr: %p\n", &obj_array[counter]);

	printf("obj.spi: %s\n", obj1.spi);
	printf("obj.cnt: %s\n", obj_array[counter].spi);

	if (counter >= 10)
	{
		counter = 0;
		printf("maksimalan broj nRF objekata pregazen, counter vracen u 0\n");
	}

	//return obj1;
	return &obj_array[counter++];
	//printf("adresa koju ce vratit %p\n", &gobj[counter]);
	//return &gobj[counter++];
}

void nRF_main()
{
}
