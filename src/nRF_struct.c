#include "nRF_struct.h"

/*
// local defines
#define PIN0	GPIO_Pin_0
#define PIN1	GPIO_Pin_1
#define PIN2	GPIO_Pin_2
#define PIN3	GPIO_Pin_3
#define PIN4	GPIO_Pin_4
#define PIN5	GPIO_Pin_5
#define PIN6	GPIO_Pin_6
#define PIN7	GPIO_Pin_7
#define PIN8	GPIO_Pin_8
#define PIN9	GPIO_Pin_9
#define PIN10	GPIO_Pin_10
#define PIN11	GPIO_Pin_11
#define PIN12	GPIO_Pin_12
#define PIN13	GPIO_Pin_13
#define PIN14	GPIO_Pin_14
#define PIN15	GPIO_Pin_15
*/

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

static int parse_spi(const char *arg)
//int parse_spi(nRF_t *arg)
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

//void gpio_init(char port, uint8_t pin, bool direction)
static uint8_t gpio_init(char port, uint8_t pin, direction_t direction)
{

	//printf("gpio_init dobio: port: %c, pin: %d, direction: %d\n", port, pin, direction);

	GPIO_InitTypeDef GPIO_InitStructure;

	// GPIO* su uvijek na APB2 sabirnici
	/*
	switch (port)
	{
		case 'A':
		case 'a':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			break;
		case 'B':
		case 'b':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
			break;
		case 'C':
		case 'c':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			break;
		default:
			printf("ovdje ne bi smio doc jer su provjere vec obavljene\n");
			break;
	}
	*/

	if (direction == OUT)
	{
		GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_Out_PP;
		//GPIO_InitStructure.GPIO_Pin	= NRF1_CSN_PIN;		// GPIO_Pin_5
		//GPIO_Init(NRF1_CSN_PORT, &GPIO_InitStructure);
	}
	else if (direction == IN)
	{
		GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IPD;
		//GPIO_InitStructure.GPIO_Pin	= NRF1_IRQ_PIN;
		//GPIO_Init(NRF1_IRQ_PORT, &GPIO_InitStructure);
	}
	else
	{
		printf("error gpio_init(): wrong direction: %d\n", direction);
		return EXIT_WRONG_GPIO_DIRECTION;
	}

	switch (pin)
	{
		case 0:
			//GPIO_InitStructure.GPIO_Pin	= PIN0;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
			break;
		case 1:
			//GPIO_InitStructure.GPIO_Pin	= PIN1;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
			break;
		case 2:
			//GPIO_InitStructure.GPIO_Pin	= PIN2;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
			break;
		case 3:
			//GPIO_InitStructure.GPIO_Pin	= PIN3;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
			break;
		case 4:
			//GPIO_InitStructure.GPIO_Pin	= PIN4;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
			break;
		case 5:
			//GPIO_InitStructure.GPIO_Pin	= PIN5;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
			break;
		case 6:
			//GPIO_InitStructure.GPIO_Pin	= PIN6;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
			break;
		case 7:
			//GPIO_InitStructure.GPIO_Pin	= PIN7;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
			break;
		case 8:
			//GPIO_InitStructure.GPIO_Pin	= PIN8;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
			break;
		case 9:
			//GPIO_InitStructure.GPIO_Pin	= PIN9;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
			break;
		case 10:
			//GPIO_InitStructure.GPIO_Pin	= PIN10;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
			break;
		case 11:
			//GPIO_InitStructure.GPIO_Pin	= PIN11;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
			break;
		case 12:
			//GPIO_InitStructure.GPIO_Pin	= PIN12;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
			break;
		case 13:
			//GPIO_InitStructure.GPIO_Pin	= PIN13;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
			break;
		case 14:
			//GPIO_InitStructure.GPIO_Pin	= PIN14;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
			break;
		case 15:
			//GPIO_InitStructure.GPIO_Pin	= PIN15;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
			break;
		default:
			printf("error gpio_init(): Wrong pin\n");
			return EXIT_WRONG_GPIO_PIN;
	}

	// istovremeno pokreni clock i init
	switch (port)
	{
		case 'A':
		case 'a':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			break;
		case 'B':
		case 'b':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			break;
		case 'C':
		case 'c':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			GPIO_Init(GPIOC, &GPIO_InitStructure);
			break;
		default:
			printf("ovdje ne bi smio doc jer su provjere vec obavljene\n");
			break;
	}
	return EXIT_SUCCESS;
}

// ocekuje da ce dobit nesto poput "CS", PA2
//int parse_gpio(const char *name, const char *arg)
static int parse_gpio(const char *name, const char *arg, direction_t direction)
{
	// u ovo ce zapisat samo ako je dobiven ispravni port i pin
	char port;
	uint8_t pin;

	char arg_port = arg[1];
	int arg_pin = atoi(&arg[2]);	// radi i za dvoznamenkaste brojeve

	if ((arg_port == 'A') ||
		(arg_port == 'a') ||
		(arg_port == 'B') ||
		(arg_port == 'b') ||
		(arg_port == 'C') ||
		(arg_port == 'c'))
	{
		port = arg_port;
	}
	else
	{
		printf("error nRF_init(): Wrong %s!\n", name);
		return EXIT_WRONG_GPIO_PORT;
	}

	if ((arg_pin < 0) || (arg_pin > 15))
	{
		// ARM board ima 16 bitne portove
		printf("error nRF_init(): Wrong %s pin: %d\n", name, arg_pin);
		return EXIT_WRONG_GPIO_PIN;
	}
	else if ((arg_port == 'C') && (arg_pin > 2))
	{
		printf("error nRF_init(): STM32F1x nema PC%d\n", arg_pin);
		return EXIT_WRONG_GPIO_PIN;
	}
	else
	{
		pin = arg_pin;
		//printf("parse_gpio() uspjesan: funkcija: %s, port: %c, pin: %d\n", name, port, pin);

		// znamo port i pin, pozovimo init
		gpio_init(port, pin, direction);
	}

	return EXIT_SUCCESS;
}

static int nRF_init(nRF_t *self)
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

static void nRF_constructor(nRF_t *self)
{
	// kao konstruktor, popuni neispravnim defaultnim vrijednostima
	// koje ce se kasnije provjeravat
	self->spi = "X0";
	self->cs  = "X0";
	self->ce  = "X0";
	self->irq = "X0";
}

static void nRF_print(nRF_t *self)
{
	printf("nRF_print():\n");
	printf("\time: %s\n", self->name);
	printf("\tSPI: %s\n", self->spi);
	printf("\tCS: %s\n", self->cs);
	printf("\tCE: %s\n", self->ce);
	printf("\tIRQ: %s\n", self->irq);
}

//nRF_t gobj[10];
nRF_t obj_array[10];
//int globalna = 2;

// javno
// kreiraj novi objekt i inicijaliziraj ga
nRF_t *nRF_new(const char *name)
{
	// TODO
	// kako napravit npr int var`echo $name`;
	//printf("_new: %p\n", &gobj);

	static uint8_t counter = 0;

	//printf("odje nRF_new()\n");
	//printf("argument: %s\n", name);

	nRF_t obj1;
	nRF_constructor(&obj1);		// zapuni defaultnim vrijednostima
	obj1.name = (char *)name;	// XXX zasto ga imam kao const ako ga moram pretvorit :-/

	/*
	nRF_t gobj[counter];
	printf("addr obj[counter]: %p\n", &gobj[counter]);
	//nRF_constructor(&obj[counter]);		// zapuni defaultnim vrijednostima
	//nRF_constructor(&gobj[counter]);		// zapuni defaultnim vrijednostima
	gobj[counter].name = (char *)name;	// XXX zasto ga imam kao const ako ga moram pretvorit :-/
	*/

	//printf("napravili smo objekt imena: %s\n", obj1.name);

	obj1.init = nRF_init;
	obj1.print = nRF_print;
	/*
	gobj[counter].init = nRF_init;
	gobj[counter].print = nRF_print;
	*/

	// XXX
	// napravit ovo da moze napravit vise objekata
	// mozda array?
	// XXX

	//counter++;
	// vrati adresu objekta

	void *pointer = obj_array;
	printf("void pointer: %p\n", pointer);
	//printf("napisi sta oces %p\n", obj_array);
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
