// created 150206

#include "dpot.h"

#define SHIFT_DATA	"PE7"
#define SHIFT_CLK	"PE8"
#define SHIFT_RCK	"PE9"

// dpot SMD live ima 2xCD4051 
#define POT_WIDTH	8		// koliko bitova treba za cijeli pot	2{CBA} + 1{CBA} + 2E + 1E = 8
//#define POT_WIDTH	12

/*
 * shift datasheet:
 * Data is shifted on the positive-going transitions of the shift register clock input (SHCP, pin 11, SCK)
 *
 * The data in each register is transferred to the storage register on a positive-going 
 * transition of the storage register clock input (STCP, pin 12, RCK). 
 *
 * storage register has 8 parallel 3-state bus driver outputs. Data in the storage register 
 * appears at the output whenever the output enable input (OE, pin 13) is LOW.
 * INFO: moj OE je hardcoded u GND
 *
 * 3 stages: [ 8-stage shift-register ]		->	[ 8-bit storage register ]		->  [ 3-state outputs (Qn) ]
 *               ^   ^    ^							 ^									 ^
 *              DS  SHCP 'MR			 Q7S		STCP								'OE
 * pins:        14   11  10               9          12                                  13
 * eagle:		SER SCK  SCL			 QH*		RCK									  G
 * hardcoded:			 Vcc															Gnd
*/

void dpot_init(void)
{
	gpio_init(SHIFT_DATA, OUT);
	gpio_init(SHIFT_CLK,  OUT);
	gpio_init(SHIFT_RCK,  OUT);
}

int dpot(pot_state_t state)
{
	if ( (state < P0_0) || (state >= P_INVALID))
	{
		printf("pot: krivo stanje\n");
		return 1;
	}

	const uint8_t pot_stanja[12][POT_WIDTH] = {
	//   C2 B2 A2 C1 B1 A1 E2 E1			// mjerenja za 330 ohma [kOhm]
		{0, 0, 0, 0, 0, 0, 1, 0},	// P0	0.17
		{0, 0, 0, 0, 0, 1, 1, 0},	// P1
		{0, 0, 0, 0, 1, 0, 1, 0},	// P2
		{0, 0, 0, 0, 1, 1, 1, 0},	// P3
		{0, 0, 0, 1, 0, 0, 1, 0},	// P4
		{0, 0, 0, 1, 0, 1, 1, 0},	// P5
		{0, 0, 0, 1, 1, 0, 1, 0},	// P6
		{0, 0, 0, 1, 1, 1, 1, 0},	// P7
	// XXX hw zajeb, C2 nije spojeno
		{0, 0, 0, 0, 0, 0, 0, 1},	// P8
		{0, 0, 1, 0, 0, 0, 0, 1},	// P9
		{0, 1, 0, 0, 0, 0, 0, 1},	// P10
		{0, 1, 1, 0, 0, 0, 0, 1}};	// P11

	/*
	 // TODO:
	const uint8_t POT_STANJA[24][POT_WIDTH] = {
		// E	   3C B A  2C B A  1C B A
		{1,1,0,		0,0,0,	0,0,0,	0,0,0},		// 0.0
		{1,1,0,		0,0,0,	0,0,0,	0,0,1},		// 0.5
		{1,1,0,		0,0,0,	0,0,0,	0,1,0},		// 1.0
		{1,1,0,		0,0,0,	0,0,0,	0,1,1},		// 1.5
		{1,1,0,		0,0,0,	0,0,0,	1,0,0},		// 2.0
		{1,1,0,		0,0,0,	0,0,0,	1,0,1},		// 2.5
		{1,1,0,		0,0,0,	0,0,0,	1,1,0},		// 3.0
		{1,1,0,		0,0,0,	0,0,0,	1,1,1},		// 3.5

		{1,0,1,		0,0,0,	0,0,0,	0,0,0},		// 4.0
		{1,0,1,		0,0,0,	0,0,1,	0,0,0},		// 4.5
		{1,0,1,		0,0,0,	0,1,0,	0,0,0},		// 5.0
		{1,0,1,		0,0,0,	0,1,1,	0,0,0},		// 5.5
		{1,0,1,		0,0,0,	1,0,0,	0,0,0},		// 6.0
		{1,0,1,		0,0,0,	1,0,1,	0,0,0},		// 6.5
		{1,0,1,		0,0,0,	1,1,0,	0,0,0},		// 7.0
		{1,0,1,		0,0,0,	1,1,1,	0,0,0},		// 7.5

		{0,1,1,		0,0,0,	0,0,0,	0,0,0},		// 8.0
		{0,1,1,		0,0,1,	0,0,0,	0,0,0},		// 8.5
		{0,1,1,		0,1,0,	0,0,0,	0,0,0},		// 9.0
		{0,1,1,		0,1,1,	0,0,0,	0,0,0},		// 9.0
		{0,1,1,		1,0,0,	0,0,0,	0,0,0},		// 10.0
		{0,1,1,		1,0,1,	0,0,0,	0,0,0},		// 10.5
		{0,1,1,		1,1,0,	0,0,0,	0,0,0},		// 11.0
		{0,1,1,		1,1,1,	0,0,0,	0,0,0},		// visak
		};
		*/

	// INFO	 TI CD4051 koristio na "dpot SMD lite", rade za +- 20V
	// TODO prepravit hardver da ide EEE CBA CBA CBA
	// TODO mozda stavit otpornik izmedju O{1,2,3} i OUT


	for (int i=0; i<POT_WIDTH; i++)		// zapisi citavu vrijednost za jedan pot
	{
		gpio_write(SHIFT_DATA, pot_stanja[state][i]);	

		// nakon zapisivanja svakog bita, toggleaj CLK
		gpio_write(SHIFT_CLK, 1);
		gpio_write(SHIFT_CLK, 0);
	}

	// nakon zapisivanja svih 8 bitova u shift, togglaj RCK da se odlatcha
	gpio_write(SHIFT_RCK, 1);
	gpio_write(SHIFT_RCK, 0);

	return 0;
}
