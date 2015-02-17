#ifndef EEPROM_H
#define EEPROM_H

// created 140918
// *************************************** description ********************************************
// Atmel 24C256 I2C EEPROM driver
// *************************************** sys includes *******************************************
#include <stdio.h>
#include <string.h> 	// memcpy
// *************************************** local includes *****************************************
#include "delay.h"
#include "i2c.h"

// *************************************** defines ************************************************
#define I2C_TIMEOUT_MAX	0xFFFF
// pretpostavka da su A1 i A0 = 0
/*
#define EEPROM_ADDR_W	0xA0
#define EEPROM_ADDR_R	0xA1
*/
// mali EEPROM sa RTC modula
// svi A pinovi su nula
#define EEPROM_ADDR_W	0b10100000
#define EEPROM_ADDR_R	0b10100001

#define EEPROM_MAX_DEVICES	4	// koliko ce EEPROMova bit odjednom zajedno
// *************************************** variables **********************************************
typedef struct
{
	uint16_t size_in_kB;	// INFO nece radit za manje od 1kB npr AT24C0{4,2,1}
	uint8_t  number;
	//uint8_t
} eeprom_t;

// *************************************** function prototypes ************************************
void eeprom_init(void);
uint8_t eeprom_write(uint16_t addr, uint8_t data);
uint8_t eeprom_read(uint16_t addr);
void eeprom_example(void);

#endif
