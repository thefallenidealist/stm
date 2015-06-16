// dobij u hex 16b RGB565
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint16_t rgb565(uint8_t arg_red, uint8_t arg_green, uint8_t arg_blue)
{
	uint8_t r = arg_red   & 0b11111000;	// R5
	uint8_t g = arg_green & 0b11111100;	// G6
	uint8_t b = arg_blue  & 0b11111000;	// B5

	uint16_t rgb565 = (r << 8) | (g << 3) | (b >> 3);
	//printf("%s(): R: %d, G: %d, B: %d, RGB565: %d: 0x%04X\n", __func__, r, g, b, rgb565, rgb565);

	return rgb565;
}

uint16_t rgb565_percent(uint8_t arg_red, uint8_t arg_green, uint8_t arg_blue)
{
	// 5b max: 248, 6b max: 252

	uint8_t r = arg_red*2.48; 		// 100 postaje 248
	uint8_t g = arg_green*2.52; 	// 100 postaje 252
	uint8_t b = arg_blue*2.48;

	uint16_t rgb565 = (r << 8) | (g << 3) | (b >> 3);
	printf("%s(): R: %d, G: %d, B: %d, RGB565: %d: 0x%04X\n", __func__, r, g, b, rgb565, rgb565);

	return rgb565;
}

uint16_t rev(uint16_t arg)
{
	// prebaci iz big endian u little endian format

	uint8_t argH = (arg >> 8) & 0xFF;
	uint8_t argL = (arg >> 0) & 0xFF;
	uint16_t swapped = (argL << 8) + argH;

	//printf("argH: 0x%02X\n", argH);
	//printf("argL: 0x%02X\n", argL);
	//printf("swapped: 0x%04X\n", swapped);

	return swapped;
}

int main(int argc, char *argv[])
{
	if (argc <= 3)
	{
		//printf("Error: Please enter red, blue and green in 0..255 range\n");
		printf("Usage: %s red[0..255] green[0.255] blue[0..255]\n", argv[0]);
	}
	else
	{
		size_t red   = atoi(argv[1]);
		size_t green = atoi(argv[2]);
		size_t blue  = atoi(argv[3]);

		if ( (red > 255) || (green > 255) || (blue > 255) )
		{
			printf("Warning: Colors overflows uint8_t\n");
		}

		uint16_t rgb565BE = rgb565(red, green, blue);
		uint16_t rgb565LE = rev(rgb565BE);

		printf("RGB565 BE: 0x%04X\n", rgb565BE);
		printf("RGB565 LE: 0x%04X\n", rgb565LE);
	}

	return 0;
}
