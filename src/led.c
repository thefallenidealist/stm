// *************************************** description ********************************************
// KK madjija
// *************************************** sys includes *******************************************
#include "led.h"

// *************************************** variables **********************************************

// *************************************** function prototypes ************************************

/**************************************************************************************************
*  					get_led_structure(void)					  *
**************************************************************************************************/
led_structure get_led_structure(char led_port, int led_pin)
{

	// dobije char, npr PA	i int, npr 2
	//printf("%s(): arguments: port: %c, pin: %d\n", __func__, led_port, led_pin);

	led_structure ledOut = {};

	if ((led_port == 'A') || (led_port == 'a'))
	{
		ledOut.rcc = RCCA;
		ledOut.port = PORTA;
	}
	else if ((led_port == 'B') || (led_port == 'b'))
	{
		ledOut.rcc = RCCB;
		ledOut.port = PORTB;

	}
	else if ((led_port == 'C') || (led_port == 'c'))
	{
		ledOut.rcc = RCCC;
		ledOut.port = PORTC;

	}
	else if ((led_port == 'D') || (led_port == 'd'))
	{
		ledOut.rcc = RCCD;
		ledOut.port = PORTD;	// radi
	}
	else if ((led_port == 'E') || (led_port == 'e'))
	{
		ledOut.rcc = RCCE;
		ledOut.port = PORTE;	// radi
	}
	else
	{
		printf("get_led_structure(): wrong port\n");
	}

	switch (led_pin)
	{
		case 0:
		       	//ledOut.pin = LED0_PIN;
			ledOut.pin = GPIO_Pin_0;
			return ledOut;
			break;
		case 1:
		       	//ledOut.pin = LED1_PIN;
			ledOut.pin = GPIO_Pin_1;
			return ledOut;
			break;
		case 2:
		       	//ledOut.pin = LED2_PIN;
			ledOut.pin = GPIO_Pin_2;
			return ledOut;
			break;
		case 3:
		       	//ledOut.pin = LED3_PIN;
			ledOut.pin = GPIO_Pin_3;
			return ledOut;
			break;
		case 4:
		       	//ledOut.pin = LED4_PIN;
			ledOut.pin = GPIO_Pin_4;
			return ledOut;
			break;
		case 5:
		       	//ledOut.pin = LED5_PIN;
			ledOut.pin = GPIO_Pin_5;
			return ledOut;
			break;
		case 6:
		       	//ledOut.pin = LED6_PIN;
			ledOut.pin = GPIO_Pin_6;
			return ledOut;
			break;
		case 7:
		       	//ledOut.pin = LED7_PIN;
			ledOut.pin = GPIO_Pin_7;
			return ledOut;
			break;
		case 8:
		       	//ledOut.pin = LED8_PIN;
			ledOut.pin = GPIO_Pin_8;
			return ledOut;
			break;
		case 9:
		       	//ledOut.pin = LED9_PIN;
			ledOut.pin = GPIO_Pin_9;
			return ledOut;
			break;
		case 10:
		       	//ledOut.pin = LED10_PIN;
			ledOut.pin = GPIO_Pin_10;
			return ledOut;
			break;
		case 11:
		       	//ledOut.pin = LED11_PIN;
			ledOut.pin = GPIO_Pin_11;
			return ledOut;
			break;
		case 12:
		       	//ledOut.pin = LED12_PIN;
			ledOut.pin = GPIO_Pin_12;
			return ledOut;
			break;
		case 13:
		       	//ledOut.pin = LED13_PIN;
			ledOut.pin = GPIO_Pin_13;
			return ledOut;
			break;
		case 14:
		       	//ledOut.pin = LED14_PIN;
			ledOut.pin = GPIO_Pin_14;
			return ledOut;
			break;
		case 15:
		       	//ledOut.pin = LED15_PIN;
			ledOut.pin = GPIO_Pin_15;
			return ledOut;
			break;
		default:
			printf("get_led_structure(): wrong pin.\n");
			ledOut.rcc = (uint32_t)NULL;
			ledOut.port = NULL;
			ledOut.pin = (uint32_t)NULL;
			return ledOut;
			break;
	}
}

/**************************************************************************************************
*  					led_init_structure(void)					  *
**************************************************************************************************/
void led_init_structure(led_structure structure)
{
	if ( (structure.rcc != (int)NULL) && (structure.port != NULL) && (structure.pin != (int)NULL) )
	{

		GPIO_InitTypeDef GPIO_InitStruct;
#ifdef STM32F10X_MD
		RCC_APB2PeriphClockCmd(structure.rcc, ENABLE);// F1
		GPIO_InitStruct.GPIO_Pin = structure.pin;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;	// F1
#endif
#ifdef STM32F4XX
		RCC_AHB1PeriphClockCmd(structure.rcc, ENABLE);	// F4

		GPIO_InitStruct.GPIO_Pin = structure.pin; 	// XXX ne radi
		//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;	// radi
		//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_15;	// radi
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;	// F4
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;	// TODO
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
#endif
		GPIO_Init(structure.port, &GPIO_InitStruct);
		// zauzmi portove
		//busy((char)structure.port, (uint8_t)structure.pin);
	}
}

/**************************************************************************************************
*  					led_init(void)						  *
**************************************************************************************************/
void led_init(char *led)
{
	// TODO razne provjere

	char 	led_port = led[1];
	uint8_t led_pin = atoi(&led[2]);	// predaj adresu, da radi i za dvoznamenkaste

	//printf("%s(): arguments: led: %s\n", __func__, led);
	//printf("led_init(): arguments: led: %s\n", led);		// XXX zablokira

	led_init_structure(get_led_structure(led_port, led_pin));
}

/**************************************************************************************************
*  					led_set(void)						  *
**************************************************************************************************/
void led_set(led_structure structure, uint8_t status)
{
	if ( (structure.rcc != (int)NULL) && (structure.port != NULL) && (structure.pin != (int)NULL) )
	{
		if ((status == 1) || (status == 0))
		{
			GPIO_WriteBit(structure.port, structure.pin, status);
		}
		else if (status == 2)	// toggle
		{
			if (GPIO_ReadInputDataBit(structure.port, structure.pin) == 0)
			{
				GPIO_WriteBit(structure.port, structure.pin, 1);
			}
			else
			{
				GPIO_WriteBit(structure.port, structure.pin, 0);
			}
		}
		else
		{
			printf("led_set(): pogresan argument\n");
		}
	}
}

/**************************************************************************************************
*  					led()							  *
**************************************************************************************************/
// led("PA2", 1)
//void led(char *led, uint8_t led_state)
void led(const char *led, uint8_t led_state)
{
	// TODO razne provjere
	char led_port	= led[1];
	uint8_t led_pin = atoi(&led[2]);	// predaj adresu, da radi i za dvoznamenkaste

	if ((led_state > 2) || (led_state < 0))
	{
		printf("led(): wrong state\n");
		// return kurac;
	}

	led_set(get_led_structure(led_port, led_pin), led_state);
}
