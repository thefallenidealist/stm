
// INFO
// 3.3V, vec ima PU Rove

#include "wii.h"

#define WII_ADDR_W	0xA4
#define WII_ADDR_R	0xA5

void wii_init()
{
	i2c_init(2, 100000);	// ne radi na 400kHz

	// wii init
	i2c_start(2);
	i2c_sendAddr_tx(2, WII_ADDR_W);
	// Write 0xA4, 0xF0, 0x55 (address, register, data) 
	i2c_write(2, 0xF0);
	i2c_write(2, 0x55);

   	// Write 0xA4, 0xFB, 0x00 (address, register, data) 
	i2c_write(2, 0xFB);
	i2c_write(2, 0x00);
	i2c_stop(2);
}

void wii_read_start()
{
}

void wii_read()
{
	i2c_start(2);		// XXX ovdje zapne ponekad
	i2c_sendAddr_tx(2, WII_ADDR_W);
	i2c_write(2, 0x00);	// set pointer to 0
	i2c_stop(2);
	

	i2c_start(2);
	i2c_sendAddr_rx(2, WII_ADDR_R);
	//i2c_sendAddr_rx(2, WII_ADDR_W);	// ne jebe ga previse ako mu se posalje ova adresa
	uint8_t joystickX = i2c_read_ack(2);
	uint8_t joystickY = i2c_read_ack(2);
	uint8_t accelerometerXH = i2c_read_ack(2);
	uint8_t accelerometerYH = i2c_read_ack(2);
	uint8_t accelerometerZH = i2c_read_ack(2);
	uint8_t misc = i2c_read_nack(2);
	i2c_stop(2);

	// joystick Y sredina: 119-137
	// joystick X sredina: 139
	uint16_t accelerometerX = accelerometerXH<<2 | (misc & 0b11000000);
	uint16_t accelerometerY = accelerometerYH<<2 | (misc & 0b00110000);
	uint16_t accelerometerZ = accelerometerZH<<2 | (misc & 0b00001100);
	uint8_t  BC =        !((misc & 0b00000010) >> 1);
	uint8_t  BZ = 	      !(misc & 0b00000001);

	//printf("%s %d\n", __FILE__, __LINE__);
	printf("Wii read: accelerometer:%d accelerometerY:%d accelerometerZ:%d \t joystick_X:%d joystick_Y:%d \t BC:%d BZ:%d\n"
			, accelerometerX, accelerometerY, accelerometerZ, joystickX, joystickY, BC, BZ);
}
