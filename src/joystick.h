// *************************************** description ********************************************
// created 140919
// driver za eBay joystick sa tipkom, uzican od Burgija
#ifndef JOYSTICK_H
#define JOYSTICK_H

#ifdef __cplusplus
extern "C" {
#endif

// *************************************** sys includes *******************************************
// gpio
//#include "stm32f10x_adc.h"
//#include "stm32f10x_adc.c"
// *************************************** local includes *****************************************
#include "adc1.h"
// *************************************** defines ************************************************

#ifdef STM32F10X_MD
	#define JX_RCC	RCC_APB2Periph_GPIOA
	#define JY_RCC	RCC_APB2Periph_GPIOA
	#define JS_RCC	RCC_APB2Periph_GPIOA
#endif
#ifdef STM32F4XX
	#define JX_RCC	RCC_AHB1Periph_GPIOA
	#define JY_RCC	RCC_AHB1Periph_GPIOA
	#define JS_RCC	RCC_AHB1Periph_GPIOA
#endif


#define JX_PORT	GPIOA
#define JY_PORT	GPIOA
#define JS_PORT	GPIOA
#define JX_PIN	GPIO_Pin_2
#define JY_PIN	GPIO_Pin_4
#define JS_PIN	GPIO_Pin_0

#define JOYSTICK_SENSITIVITY 10	// kad je joystick u 90% registrirat ce kao pomak
// *************************************** variables **********************************************
// *************************************** function prototypes ************************************
void joystick_init();
void joystick_gpio_init();
char joystick_read();

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif	// JOYSTICK_H
// TODO ovo sve presaltat na GPIO driver
