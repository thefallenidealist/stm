// STM32F4 blinky blinky
// treperi 4 onboard LEDice sve brze pa onda sve sporije i tako u krug
#include "blinky.h"

// privatne varijable
uint8_t delay = 0;
uint8_t delay_max = 0;
bool delay_postavljen = 0;

typedef enum
{
	DELAY_FLAG_INC,
	DELAY_FLAG_DEC
} delay_flag_t;
delay_flag_t delay_flag;

// privatne funkcije
static void delay_op()
{
	if (delay_flag == DELAY_FLAG_INC)
	{
		delay++;
	}
	if (delay_flag == DELAY_FLAG_DEC)
	{
		delay--;
	}
	if (delay >= delay_max)
	{
		delay_flag = DELAY_FLAG_DEC;
	}
	if (delay < 1)
	{
		delay_flag = DELAY_FLAG_INC;
	}
}

// javne funkcije ispod
void blinky_blinky_setup()
{
	led_init("PD13");
	led_init("PD14");
	led_init("PD15");
	//led_init("PD12");
	led_init((char *)LED_GREEN);
	//led_init(LEDG);
}

void blinky_blinky(uint8_t arg)
{
	if (delay_postavljen == 0)
	{
		delay = arg;
		delay_max = arg;
		delay_postavljen = 1;
	}

	led("PD12", 2);
	delay_ms(delay);
	led("PD12", 2);
	led("PD13", 2);
	delay_ms(delay);
	led("PD13", 2);
	led("PD14", 2);
	delay_ms(delay);
	led("PD14", 2);
	led("PD15", 2);
	delay_ms(delay);
	led("PD15", 2);
	delay_op();

	//printf("blinky blinky delay: %d delay_flag: %d\n", delay, delay_flag);
}
