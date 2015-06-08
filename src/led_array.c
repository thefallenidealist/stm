#include "led_array.h"

#define LED_ARRAY_PIN	"PA1"

void led_array_init(void)
{
	//gpio_init(LED_ARRAY_PIN, OUT);

}

//#include <stm32f10x.h>

void Delay(__IO uint32_t nCount) {
  while(nCount--) {
  }
}


#define TIM3_CCR1_Address 0x40000434	// physical memory address of Timer 3 CCR1 register

#define d2r (3.14159265/180)

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
DMA_InitTypeDef DMA_InitStructure;

/* Buffer that holds one complete DMA transmission
 * 
 * Ensure that this buffer is big enough to hold
 * all data bytes that need to be sent
 * 
 * The buffer size can be calculated as follows:
 * number of LEDs * 24 bytes + 42 bytes
 * 
 * This leaves us with a maximum string length of
 * (2^16 bytes per DMA stream - 42 bytes)/24 bytes per LED = 2728 LEDs
 */
uint16_t LED_BYTE_Buffer[100];	

/* this array holds the RGB values to represent 
 * a color wheel using 256 steps on each emitter
 * 256^3 = 16777216 colors
 */
/*
uint8_t eightbit[766][3] =
{
	{255, 0, 0},
	{254, 0, 1},
	{255, 0, 0},
};
*/

void Timer3_init(void)
{
	uint16_t PrescalerValue;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	/* GPIOA Configuration: TIM3 Channel 1 as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	/* Compute the prescaler value */
	PrescalerValue = (uint16_t) (SystemCoreClock / 24000000) - 1;
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 29; // 800kHz 
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	
	/* configure DMA */
	/* DMA clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	/* DMA1 Channel6 Config */
	DMA_DeInit(DMA1_Channel6);

	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)TIM3_CCR1_Address;	// physical address of Timer 3 CCR1
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)LED_BYTE_Buffer;		// this is the buffer memory 
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;						// data shifted from memory to peripheral
	DMA_InitStructure.DMA_BufferSize = 42;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					// automatically increase buffer index
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;							// stop DMA feed after buffer size is reached
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	DMA_Init(DMA1_Channel6, &DMA_InitStructure);
	
	/* TIM3 CC1 DMA Request enable */
	TIM_DMACmd(TIM3, TIM_DMA_CC1, ENABLE);
}

/* This function sends data bytes out to a string of WS2812s
 * The first argument is a pointer to the first RGB triplet to be sent
 * The seconds argument is the number of LEDs in the chain
 * 
 * This will result in the RGB triplet passed by argument 1 being sent to 
 * the LED that is the furthest away from the controller (the point where
 * data is injected into the chain)
 */
void WS2812_send(uint8_t (*color)[3], uint16_t len)
{
	uint8_t i,j;
	uint8_t led;
	uint16_t memaddr;
	uint16_t buffersize;

	buffersize = (len*24)+42;	// number of bytes needed is #LEDs * 24 bytes + 42 trailing bytes
	memaddr = 0;				// reset buffer memory index
	led = 0;					// reset led index

	// fill transmit buffer with correct compare values to achieve
	// correct pulse widths according to color values
	while (len)
	{	
		for (j = 0; j < 8; j++)					// GREEN data
		{
			if ( (color[led][1]<<j) & 0x80 )	// data sent MSB first, j = 0 is MSB j = 7 is LSB
			{
				LED_BYTE_Buffer[memaddr] = 17; 	// compare value for logical 1
			}
			else
			{
				LED_BYTE_Buffer[memaddr] = 9;	// compare value for logical 0
			}
			memaddr++;
		}
		
		for (j = 0; j < 8; j++)					// RED data
		{
			if ( (color[led][0]<<j) & 0x80 )	// data sent MSB first, j = 0 is MSB j = 7 is LSB
			{
				LED_BYTE_Buffer[memaddr] = 17; 	// compare value for logical 1
			}
			else
			{
				LED_BYTE_Buffer[memaddr] = 9;	// compare value for logical 0
			}
			memaddr++;
		}
		
		for (j = 0; j < 8; j++)					// BLUE data
		{
			if ( (color[led][2]<<j) & 0x80 )	// data sent MSB first, j = 0 is MSB j = 7 is LSB
			{
				LED_BYTE_Buffer[memaddr] = 17; 	// compare value for logical 1
			}
			else
			{
				LED_BYTE_Buffer[memaddr] = 9;	// compare value for logical 0
			}
			memaddr++;
		}
		
		led++;
		len--;
	}
	
	// add needed delay at end of byte cycle, pulsewidth = 0
	while(memaddr < buffersize)
	{
		LED_BYTE_Buffer[memaddr] = 0;
		memaddr++;
	}

	DMA_SetCurrDataCounter(DMA1_Channel6, buffersize); 	// load number of bytes to be transferred
	DMA_Cmd(DMA1_Channel6, ENABLE); 			// enable DMA channel 6
	TIM_Cmd(TIM3, ENABLE); 						// enable Timer 3
	while(!DMA_GetFlagStatus(DMA1_FLAG_TC6)); 	// wait until transfer complete
	TIM_Cmd(TIM3, DISABLE); 					// disable Timer 3
	DMA_Cmd(DMA1_Channel6, DISABLE); 			// disable DMA channel 6
	DMA_ClearFlag(DMA1_FLAG_TC6); 				// clear DMA1 Channel 6 transfer complete flag
}

int led_main(void)
{
	Timer3_init();
	
	int16_t i;
	
		uint8_t boje[] = {
			{255, 255, 255},	// 0 white
			{255, 255, 0},		// 1 narancasto
			{255, 0, 255},		// 2 red
			{0, 255, 255},		// 3 green
			{255, 0, 0},		// 4 
			{0, 255, 0},		// 5
			{0, 0, 255},		// 6
			{0, 0, 0},
		};
	while (1)
	{  
		/* first cycle through the colors on 2 LEDs chained together
		 * last LED in the chain will receive first sent triplet
		 * --> last LED in the chain will 'lead' 
		 */
		/*
		for (i = 0; i < 766; i += 2)
		{
			WS2812_send(&eightbit[i], 2);
			Delay(50000L);
		}
		*/
		
		/* cycle through the colors on only one LED
		 * this time only the first LED that data is 
		 * fed into will update
		 */
		/*
		for (i = 0; i < 766; i += 1)
		{
			WS2812_send(&eightbit[i], 1);
			Delay(50000L);
		}
		*/
		//for (int n = 1; n < 2; n++)
		int n = 1;	// broj aktivnih LEDica


		for (i = 0; i < 200; i += n)	// koliko ciklusa prije reseta
		{
			WS2812_send(&boje[2], 2);
			WS2812_send(&boje[3], 2);
			Delay(50000L);
		}
	}
}
