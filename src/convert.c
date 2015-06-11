#include "convert.h"

/*************************************************************************************************
			dec2bcd()
*************************************************************************************************/
uint8_t dec2bcd(uint8_t dec)
{
	if (dec > 99)	// veci nece stat u 8b
	{
		return 0;
	}
	uint8_t bcd, bcdH, bcdL;

	// razlomi na single digit
	bcdH = dec/10;
	bcdL = dec%10;

	// pretvori nazad u 8b BCD
	bcd = bcdH<<4 | bcdL;

	return bcd;
}

/*************************************************************************************************
			dec2bin8
*************************************************************************************************/
void dec2bin8(uint8_t arg)
{
	uint8_t i=8;

	printf("%d = 0b", arg);
	while (i-- > 0)
	{
		printf("%d", (arg >> i) & 1);
	}
	printf("\n");
}


//uint8_t bin[8];
/*************************************************************************************************
			dec2bin8_str
*************************************************************************************************/
uint8_t *dec2bin8_str(uint8_t arg)
{
	static uint8_t bin[9];
	uint8_t i=8;
	while(i-- > 0)
	{
		// treba zapisat u naopakom redoslijedu, zato 7-i
		bin[7-i] = 48 + ((arg >> i) & 1);
	}
	bin[8] = '\0';	// dodaj NULL jer je string

	return bin;
}
