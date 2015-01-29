// STM32F4 blinky blinky
// treperi 4 onboard LEDice sve brze pa onda sve sporije i tako u krug
#include "blinky.h"

// TODO imena varijabli i jos puno toga

// privatne varijable
static uint8_t delay = 0;
static uint8_t delay_max = 0;
static bool delay_postavljen = 0;
static bool variable_delay = 0;
static uint8_t global_leds;

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

void blinky_blinky_init(uint8_t leds, bool arg)
{
	variable_delay = arg;
	global_leds = leds;

	if (leds == BLINKY_LED_ALL)
	{
		led_init("PD12");
		led_init("PD13");
		led_init("PD14");
		led_init("PD15");
	}
	if (leds == BLINKY_LED_GREEN)
	{
		led_init("PD12");
	}
	if (leds == BLINKY_LED_ORANGE)
	{
		led_init("PD13");
	}
	if (leds == BLINKY_LED_RED)
	{
		led_init("PD14");
	}
	if (leds == BLINKY_LED_BLUE)
	{
		led_init("PD15");
	}
}

void blinky_blinky(uint8_t arg)
{
	if (delay_postavljen == 0)
	{
		delay = arg;
		delay_max = arg;
		delay_postavljen = 1;
	}
	// TODO dijelit delay na onoliko LEDica koliko je postavljeno

	//printf("%s(): arg: %d \t delay_postavljen: %d \t global_leds = %d \t delay: %d \n", __func__, arg, delay_postavljen, global_leds, delay);

	if (global_leds == BLINKY_LED_GREEN)
	{
		led("PD12", 2);
		delay_ms(delay);
		led("PD12", 2);
		delay_ms(delay);
	}

	if (global_leds == BLINKY_LED_ORANGE)
	{
		led("PD13", 2);
		delay_ms(delay);
		led("PD13", 2);
		delay_ms(delay);
	}

	if (global_leds == BLINKY_LED_RED)
	{
		led("PD14", 2);
		delay_ms(delay);
		led("PD14", 2);
		delay_ms(delay);
	}

	if (global_leds == BLINKY_LED_BLUE)
	{
		led("PD15", 2);
		delay_ms(delay);
		led("PD15", 2);
		delay_ms(delay);
	}

	if (global_leds == BLINKY_LED_ALL)
	{
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
	}

	if (variable_delay == 1)
	{
		delay_op();
	}

	//printf("blinky blinky delay: %d delay_flag: %d\n", delay, delay_flag);
}
