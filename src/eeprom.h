#ifndef EEPROM_H
#define EEPROM_H

// created 140918
// *************************************** description ********************************************
// Atmel 24C256 I2C EEPROM driver
// *************************************** sys includes *******************************************
#include <stdio.h>
#include "delay.h"
#include "i2c.h"

#ifdef STM32F10X_MD
	#include "stm32f10x_rcc.h"
	#include "stm32f10x_gpio.h"
	#include "stm32f10x_i2c.h"
#endif
#ifdef STM32F4XX
	#include "stm32f4xx_rcc.h"
	#include "stm32f4xx_gpio.h"
	#include "stm32f4xx_i2c.h"
#endif

// *************************************** local includes *****************************************
// *************************************** defines ************************************************
// pretpostavka da su A1 i A0 = 0
/*
#define EEPROM_ADDR_W	0xA0
#define EEPROM_ADDR_R	0xA1
*/
#define I2C_TIMEOUT_MAX	0xFFFF

// mali EEPROM sa RTC modula
// svi A pinovi su nula
#define EEPROM_ADDR_W	0b10100000
#define EEPROM_ADDR_R	0b10100001
// *************************************** variables **********************************************
// *************************************** function prototypes ************************************
void eeprom_init(void);
uint8_t eeprom_write(uint16_t addr, uint8_t data);
uint8_t eeprom_read(uint16_t addr);
void eeprom_example(void);

#endif
