// created 150206

#define SHIFT_DATA	"PE7"
#define SHIFT_CLK	"PE8"
#define SHIFT_RCK	"PE9"


void dpot_init()
{
	led_init(SHIFT_DATA);
	led_init(SHIFT_CLK);
	led_init(SHIFT_RCK);
}

//void dpot(uint8_t state)
int dpot(uint8_t state)
{
	uint8_t pot_stanja[12][8] = {
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

	if ( (state > 11) || (state < 0) )
	{
		printf("pot: krivo stanje\n");
		//led(SHIFT_DATA, 0b00000011);	// ugasi sve
		/*
		led(SHIFT_DATA, 0b00000010);	// P0
		led(SHIFT_CLK, 1);
		led(SHIFT_CLK, 0);
		led(SHIFT_RCK, 1);
		led(SHIFT_RCK, 0);
		*/

		return 10;
	}


	for (int i=0; i<8; i++)
	{
		led(SHIFT_DATA, pot_stanja[state][i]);

		led(SHIFT_CLK, 1);
		led(SHIFT_CLK, 0);
	}
	led(SHIFT_RCK, 1);
	led(SHIFT_RCK, 0);

	return 0;
}
