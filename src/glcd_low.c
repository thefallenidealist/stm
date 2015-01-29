// GLCD uC specifican dio

#include "glcd_low.h"

void glcd_io_init(void)
{
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// TODO stavit *GPIOB kao varijablu	// F1
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	// TODO stavit *GPIOB kao varijablu	// F4

	// TODO ovo je samo za slucaj da su svi na istom portu
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GLCD_LED_PIN | GLCD_DC_PIN | GLCD_RESET_PIN | GLCD_CS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	// F4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//F4
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	// F4
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	// F4
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	// F4
	GPIO_Init(GPIOD, &GPIO_InitStructure);	// TODO var F4
}

void glcd_spi_init(void)
{
	spi_init();
	//spi2_init();
}


/*
//inline static void glcd_cs_low(void)
void glcd_cs_low(void)
{
	GPIO_WriteBit(GLCD_CS_PORT, GLCD_CS_PIN, 0);
}

//inline static void glcd_cs_high(void)
void glcd_cs_high(void)
{
	GPIO_WriteBit(GLCD_CS_PORT, GLCD_CS_PIN, 1);
}

//inline static void glcd_dc_low(void)
void glcd_dc_low(void)
{
	GPIO_WriteBit(GLCD_DC_PORT, GLCD_DC_PIN, 0);
}

//inline static void glcd_dc_high(void)
void glcd_dc_high(void)
{
	GPIO_WriteBit(GLCD_DC_PORT, GLCD_DC_PIN, 1);
}
void glcd_led_off(void)
{
	GPIO_WriteBit(GLCD_LED_PORT, GLCD_LED_PIN, 0);
}
void glcd_led_on(void)
{
	GPIO_WriteBit(GLCD_LED_PORT, GLCD_LED_PIN, 1);
}
void glcd_rst_off(void)
{
	GPIO_WriteBit(GLCD_RESET_PORT, GLCD_RESET_PIN, 1);
}
void glcd_rst_on(void)
{
	GPIO_WriteBit(GLCD_RESET_PORT, GLCD_RESET_PIN, 0);
}
*/
