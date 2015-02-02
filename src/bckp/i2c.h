// created 141205
#ifndef I2C_H
#define I2C_H

#include <stdio.h>
#include <stdint.h>

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

#define I2C_TIMEOUT_MAX 0xFFFF

int8_t	i2c_init	(uint8_t i2c_number, uint32_t i2c_speed);
int8_t	i2c_write	(uint8_t i2c_number, uint8_t slave_addr, uint8_t data);
int8_t	i2c_write2	(uint8_t i2c_number, uint8_t slave_addr, uint8_t reg, uint8_t data);
int8_t	i2c_read	(uint8_t i2c_number, uint8_t slave_addr);
// privatne funkcije
//int8_t	i2c_start	(uint8_t i2c_number);
//int8_t	i2c_start_force	(uint8_t i2c_number);
//int8_t	i2c_stop	(uint8_t i2c_number);
//int8_t	i2c_sendAddr_tx	(uint8_t i2c_number, uint8_t addr);
//int8_t	i2c_sendAddr_rx	(uint8_t i2c_number, uint8_t addr);
//int8_t	i2c_write_old	(uint8_t i2c_number, uint8_t data);
//int8_t	i2c_nack	(uint8_t i2c_number);
//int8_t	i2c_ack		(uint8_t i2c_number);

#endif
