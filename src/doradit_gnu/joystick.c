// *************************************** description ********************************************
// created 140919
// driver za eBay joystick sa tipkom, uzican od Burgija
// *************************************** sys includes *******************************************
// gpio
//#include "stm32f10x_adc.h"
//#include "stm32f10x_adc.c"
// *************************************** local includes *****************************************
#include "adc1.c"
// *************************************** defines ************************************************
#define JX_RCC	RCC_APB2Periph_GPIOA
#define JY_RCC	RCC_APB2Periph_GPIOA
#define JS_RCC	RCC_APB2Periph_GPIOA
#define JX_PORT	GPIOA
#define JY_PORT	GPIOA
#define JS_PORT	GPIOA
#define JX_PIN	GPIO_Pin_2
#define JY_PIN	GPIO_Pin_3
#define JS_PIN	GPIO_Pin_8
#define JOYSTICK_SENSITIVITY 10	// kad je joystick u 90% registrirat ce kao pomak
// *************************************** variables **********************************************
// *************************************** function prototypes ************************************
void joystick_init();
void joystick_gpio_init();
char joystick_read();

/**************************************************************************************************
*  					joystick_init()						  *
**************************************************************************************************/
void joystick_init()
{
	joystick_gpio_init();
	ADC_init();
}

/**************************************************************************************************
*  					joystick_gpio_init()					  *
**************************************************************************************************/
void joystick_gpio_init()
{
	RCC_APB2PeriphClockCmd(JX_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(JY_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(JS_RCC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;

	GPIO_InitStruct.GPIO_Pin = JX_PIN;
	GPIO_InitStruct.GPIO_Pin = JY_PIN;
	GPIO_InitStruct.GPIO_Pin = JS_PIN;

	GPIO_Init(JX_PORT, &GPIO_InitStruct);
	GPIO_Init(JY_PORT, &GPIO_InitStruct);
	GPIO_Init(JS_PORT, &GPIO_InitStruct);
}

/**************************************************************************************************
*  					joystick_read()						  *
**************************************************************************************************/
char joystick_read()
{
	// gledano da je konektor dolje
	// L:	Y = 4092
	// R:	Y = 0
	// U:	X = 0
	// D:	X = 4092
	uint16_t x_raw = ADC_read(2);	// TODO preko varijable/definea
	uint16_t y_raw = ADC_read(3);	// TODO preko varijable/definea
	uint16_t sw = GPIO_ReadInputDataBit(JS_PORT, JS_PIN);

	// 0..100
	uint8_t x = x_raw/40.96;
	uint8_t y = y_raw/40.96;

	if(y > 100-JOYSTICK_SENSITIVITY)
		return 'l';
	else if(y < JOYSTICK_SENSITIVITY)
		return 'r';
	else if(x < JOYSTICK_SENSITIVITY)
		return 'u';
	else if(x > 100-JOYSTICK_SENSITIVITY)
		return 'd';
	else if(sw == 1)
		return 'x';			// switch pressed
	else
		return 'o';			// center
}
