#include "gpio.h"

gpio_t gpio_tmp;	// TODO ovo ce trebat cuvat u multithread kodu

/*************************************************************************************************
  			gpio_real_init()
*************************************************************************************************/
static int8_t gpio_real_init(gpio_t *gpio0, direction_t direction)
{
	DEBUG_START;

	// prije ovoga je pozvan gpio_parse koji ce vratit NULL ako ne valja
	// _init() nece pozvat ovo ako je NULL

	/*
	if (gpio0 != NULL)	// vec je provjeren, al ajde
	{
	*/
		GPIO_InitTypeDef GPIO_InitStruct;

		GPIO_InitStruct.GPIO_Pin = gpio0->pin;

		if (direction == OUT)
		{
			GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
			GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
		}
		else if (direction == IN)
		{
			GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN;
			GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;	
		}
		else
		{
			ERROR("Wrong GPIO diretion\n");
			return EXIT_GPIO_WRONG_DIRECTION;
		}

		// TODO, na malom ARMu vjerojatno nije APB2
		RCC_APB2PeriphClockCmd(gpio0->rcc, ENABLE);
		GPIO_Init(gpio0->port, &GPIO_InitStruct);

		DEBUG_END;
		return EXIT_GPIO_SUCCESS;
	/*
	}
	else
	{
		DEBUG_END;
		return -1;
	}
	*/
}

/*************************************************************************************************
  			gpio_parse()
*************************************************************************************************/
static gpio_t *gpio_parse(const char *arg)
{
	DEBUG_START;

	char 	arg_port = arg[1];
	uint8_t arg_pin  = atoi(&arg[2]);	// radi i za dvoznamenkaste brojeve

	switch (arg_port)
	{
		case 'A':
		case 'a':
			gpio_tmp.rcc  = RCCA;
			gpio_tmp.port = GPIOA;
			break;
		case 'B':
		case 'b':
			gpio_tmp.rcc  = RCCB;
			gpio_tmp.port = GPIOB;
			break;
		case 'C':
		case 'c':
			gpio_tmp.rcc  = RCCC;
			gpio_tmp.port = GPIOC;
			break;
		case 'D':
		case 'd':
			gpio_tmp.rcc  = RCCD;
			gpio_tmp.port = GPIOD;
			break;
		case 'E':
		case 'e':
			gpio_tmp.rcc  = RCCE;
			gpio_tmp.port = GPIOE;
			break;
		default:
			ERROR("Wrong GPIO port\n");
			DEBUG_END;
			return NULL;
	}

	switch (arg_pin)
	{
		case 0:
			gpio_tmp.pin = GPIO_Pin_0;
			break;
		case 1:
			gpio_tmp.pin = GPIO_Pin_1;
			break;
		case 2:
			gpio_tmp.pin = GPIO_Pin_2;
			break;
		case 3:
			gpio_tmp.pin = GPIO_Pin_3;
			break;
		case 4:
			gpio_tmp.pin = GPIO_Pin_4;
			break;
		case 5:
			gpio_tmp.pin = GPIO_Pin_5;
			break;
		case 6:
			gpio_tmp.pin = GPIO_Pin_6;
			break;
		case 7:
			gpio_tmp.pin = GPIO_Pin_7;
			break;
		case 8:
			gpio_tmp.pin = GPIO_Pin_8;
			break;
		case 9:
			gpio_tmp.pin = GPIO_Pin_9;
			break;
		case 10:
			gpio_tmp.pin = GPIO_Pin_10;
			break;
		case 11:
			gpio_tmp.pin = GPIO_Pin_11;
			break;
		case 12:
			gpio_tmp.pin = GPIO_Pin_12;
			break;
		case 13:
			gpio_tmp.pin = GPIO_Pin_13;
			break;
		case 14:
			gpio_tmp.pin = GPIO_Pin_14;
			break;
		case 15:
			gpio_tmp.pin = GPIO_Pin_15;
			break;
		default:
			ERROR("Wrong GPIO pin\n");
			DEBUG_END;
			return NULL;
	}

	DEBUG_END;
	return &gpio_tmp;
}

/*************************************************************************************************
  						public functions
*************************************************************************************************/
/*************************************************************************************************
  			gpio_init()
*************************************************************************************************/
int8_t gpio_init(const char *arg, direction_t direction)
{
	DEBUG_START;

	if ( (direction != IN) && (direction != OUT) )
	{
		ERROR("GPIO wrong direction\n");
		return EXIT_GPIO_WRONG_DIRECTION;
	}

	gpio_t *gpio0 = gpio_parse(arg);

	if (gpio0 != NULL)
	{
		gpio_real_init(gpio0, direction);

		DEBUG_END;
		return EXIT_SUCCESS;
	}
	else
	{
		ERROR("GPIO parse failed\n");
		DEBUG_END;
		return -1;
	}
}

/*************************************************************************************************
  			gpio()
*************************************************************************************************/
int8_t gpio(const char *arg, state_t state)
{
	DEBUG_START;
	gpio_t *gpio0 = gpio_parse(arg);

	if (gpio0 != NULL)
	{
		if (state == TOGGLE)
		{
			if (GPIO_ReadInputDataBit(gpio0->port, gpio0->pin) == 0)
			{
				GPIO_WriteBit(gpio0->port, gpio0->pin, 1);
			}
			else
			{
				GPIO_WriteBit(gpio0->port, gpio0->pin, 0);
			}
		}
		else if (state == OFF)
		{
			GPIO_WriteBit(gpio0->port, gpio0->pin, 0);
		}
		else if (state == ON)
		{
			GPIO_WriteBit(gpio0->port, gpio0->pin, 1);
		}
		else
		{
			ERROR("GPIO wrong state\n");
			DEBUG_END;
			return -1;
		}
	}
	else
	{
		ERROR("GPIO parsing failed\n");
		DEBUG_END;
		return -1;
	}

	DEBUG_END;
	return 0;
}
/*************************************************************************************************
  			gpio_read()
*************************************************************************************************/
bool gpio_read(const char *arg)
{
	DEBUG_START;
	gpio_t *gpio0 = gpio_parse(arg);

	if (gpio0 != NULL)
	{
		DEBUG_END;
		return GPIO_ReadInputDataBit(gpio0->port, gpio0->pin);
	}
	else
	{
		ERROR("GPIO parse failed\n");
		// return something;
	}

	return 0;	// da se kompajler ne buni
}
