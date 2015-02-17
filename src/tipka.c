#include "tipka.h"
//#include "led.h"

// TODO EXTI interrupt za citanje tipke
// XXX nikad ne udje u EXTI IRQ handler. Komanda koju treba izvrsit uspjesno se izvrsi iz maina. I debugger kaze da nikad ne udje. ISR ima ispravnu adresu
// kopirao kod iz ST primjera i kurton.
// TODO provjerit AHB/APB busove, to sam vjerojatno promasio

void tipka_init()
{
	// PA0 je tipka
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
	//RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);  // za EXTI

	GPIO_InitTypeDef GPIO_InitStruct;
    ///NVIC_InitTypeDef NVIC_InitStructure;
    //EXTI_InitTypeDef EXTI_InitStructure;

	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_Init(GPIOA, &GPIO_InitStruct);


	/*
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);   // PA0

    //EXTI_StructInit(&EXTI_InitStructure);
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    //EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;         //ERROR?
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);


    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    EXTI_GenerateSWInterrupt(EXTI_Line0);   // mozda treba
	*/
}

//uint8_t tipka_read(uint8_t tipka)
uint8_t tipka_read(void)
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
}


/*
extern uint8_t EXTI_flag;

void EXTI0_IRQHandler(void) // kao NVIC_IRQChannel
{
        EXTI_flag = 1;
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) // kao EXTI_Line
    {
        //Handle the interrupt
        GPIO_WriteBit(GPIOD, GPIO_Pin_12, 1);
        //led("PD12", 2);

        //printf("tipka IRQ\n");
        EXTI_flag = 1;

        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}
*/
