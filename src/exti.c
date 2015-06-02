#include "src/exti.h"

// privatni prototip, da se komapjler ne buni
void EXTI1_IRQHandler(void);


volatile uint8_t exti1_flag = 0;

void exti1_init(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

#ifdef STM32F1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,  ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);		// TODO hardcoded
#endif
#ifdef STM32F4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource1);	// TODO hardcoded
#endif

	gpio_init("PB1", IN_PD);

	EXTI_InitStruct.EXTI_Line = EXTI_Line1;				// TODO hardcoded
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	// sa kabelom kao prekidacem i nema nekog utjecaja izmedju triggera
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	//EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;		// TODO hardcoded
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line1);

		// my stuff:
		exti1_flag = 1;
	}
}
