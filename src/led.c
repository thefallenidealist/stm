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
	else
		printf("get_led_structure(): wrong port\n");

	switch (led_pin)
	{
		case 0:
		       	ledOut.pin = LED0_PIN;
			return ledOut;
			break;
		case 1:
		       	ledOut.pin = LED1_PIN;
			return ledOut;
			break;
		case 2:
		       	ledOut.pin = LED2_PIN;
			return ledOut;
			break;
		case 3:
		       	ledOut.pin = LED3_PIN;
			return ledOut;
			break;
		case 4:
		       	ledOut.pin = LED4_PIN;
			return ledOut;
			break;
		case 5:
		       	ledOut.pin = LED5_PIN;
			return ledOut;
			break;
		case 6:
		       	ledOut.pin = LED6_PIN;
			return ledOut;
			break;
		case 7:
		       	ledOut.pin = LED7_PIN;
			return ledOut;
			break;
		case 8:
		       	ledOut.pin = LED8_PIN;
			return ledOut;
			break;
		case 9:
		       	ledOut.pin = LED9_PIN;
			return ledOut;
			break;
		case 10:
		       	ledOut.pin = LED10_PIN;
			return ledOut;
			break;
		case 11:
		       	ledOut.pin = LED11_PIN;
			return ledOut;
			break;
		case 12:
		       	ledOut.pin = LED12_PIN;
			return ledOut;
			break;
		case 13:
		       	ledOut.pin = LED13_PIN;
			return ledOut;
			break;
		case 14:
		       	ledOut.pin = LED14_PIN;
			return ledOut;
			break;
		case 15:
		       	ledOut.pin = LED15_PIN;
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
	// XXX dobrocudna magija
	// kad je ova linija u kombinaciji sa 
	//void glcd_setX(uint16_t x0, uint16_t x1)		// XXX ovo napravi zajebe sa ekranom iako kasnije radi oke
	// tada GLCD-ov prvi _bg ima bijelih crta na crnoj pozadini iako novi _bg to rijesi
	// kocka zna iscrtat po liniju debljine 1px na mjesto gdje ne treba (i to u vrijeme kad kocka miruje)

	//if ( (structure.rcc != NULL) && (structure.port != NULL) && (structure.pin != NULL) )
	if ( (structure.rcc != (int)NULL) && (structure.port != NULL) && (structure.pin != (int)NULL) )
	{
		RCC_APB2PeriphClockCmd(structure.rcc, ENABLE);

		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Pin = structure.pin;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
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
	//char	*cled_pin = &led[2];
	//uint8_t led_pin = atoi(cled_pin);
	char	cled_pin = led[2];
	uint8_t led_pin = atoi(&cled_pin);

	led_init_structure(get_led_structure(led_port, led_pin));
}

/**************************************************************************************************
*  					led_set(void)						  *
**************************************************************************************************/
void led_set(led_structure structure, uint8_t status)
{
	//if( (structure.rcc != NULL) && (structure.port != NULL) && (structure.pin != NULL) )
	if ( (structure.rcc != (int)NULL) && (structure.port != NULL) && (structure.pin != (int)NULL) )
	{
		if ((status == 1) || (status == 0))
			GPIO_WriteBit(structure.port, structure.pin, status);
		else if (status == 2)	// toggle
		{
			if (GPIO_ReadInputDataBit(structure.port, structure.pin) == 0)
				GPIO_WriteBit(structure.port, structure.pin, 1);
			else
				GPIO_WriteBit(structure.port, structure.pin, 0);
		}
		else
			printf("led_set(): pogresan argument\n");
	}
}

/**************************************************************************************************
*  					led()							  *
**************************************************************************************************/
void led(char *led, uint8_t led_state)
{
	// XXX moje parsiranje djeluje da uspori iako ni Sys ni RTC stoperice to ne potvrdjuju :-/
	// TODO razne provjere
	char led_port	= led[1];
	char *cled_pin	= &led[2];
	uint8_t led_pin = atoi(cled_pin);

	if ((led_state > 2) || (led_state < 0))
	{
		printf("led(): wrong state\n");
		// return kurac;
	}

	led_set(get_led_structure(led_port, led_pin), led_state);
}
