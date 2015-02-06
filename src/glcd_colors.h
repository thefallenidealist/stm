#ifndef GLCD_COLORS_H
#define GLCD_COLORS_H

// ove boje ne pasu za DMA
// pasu za obicni SPI, BGR=1
#define black	0x0000	// 
#define white	0xFFFF	// RGB
#define red		0xF800	// R
#define green	0x07E0	// G
#define blue	0x001F	// B
#define yellow	0xFFE0  // RG
#define cyan	0x07FF	// GB
#define magenta	0xF81F	// RB
#define gray	0x0821	// 00001 000001 00001


/*
// GLCD MSB first, BGR=0, ARM little endian
// sad pase i za obicni SPI i za DMA
// XXX ovo je sjebano, crvena ovakva je crvena, al ne pravo crvena, ostale su boje razjebane
#define black	0x0000	// 
#define white	0xFFFF	// RGB
#define red		0x00F8	// R
//#define green	0xE007	// G	XXX
#define green	0x07E0	// G
//#define blue	0x1F00	// B	XXX
#define blue	0x001F	// B
// ...
#define yellow	0xE0FF  // RG
#define cyan	0xFF07	// GB
#define magenta	0x1FF8	// RB
#define gray	0x2108	// 00001 000001 00001
*/


#endif
