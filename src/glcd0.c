// created 141225
#include <stdio.h>
#include <stdint.h>

typedef enum
{
	P1,
	P2,
	L1,
	L2
	// TODO mirrored
} lcd_orientation_t;

/*
typedef struct
{
	LED_port;
	LED_pin;
	DC_port;
	DC_pin;
	RESET_port;
	RESET_pin;
	CS_port;
	CS_pin;
} lcd_pins_t;
*/

typedef struct
{
	char  	 IC[50];
	uint16_t resolutionX;
	uint16_t resolutionY;
	uint8_t	 orientation;
} lcd_t;


void glcd_func()
{
	lcd_t glcd1;

	glcd1.resolutionX = 240;
	glcd1.resolutionY = 320;
	glcd1.orientation = P2;
}
