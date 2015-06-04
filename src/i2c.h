// created 141205
#ifndef I2C_H
#define I2C_H

// TODO izvuc pinout vamo
// PB10, PB11	F4

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
#define I2C_PIN_SDA	// TODO
/*
F4 I2C2:
SDA	PB11
SCL	PB10
*/

int8_t	i2c_init	(uint8_t i2c_number, uint32_t i2c_speed);
int8_t i2c_write(uint8_t i2c_number, uint8_t data);

int8_t	i2c_start	(uint8_t i2c_number);
int8_t	i2c_start_wait	(uint8_t i2c_number);
int8_t	i2c_restart	(uint8_t i2c_number);
int8_t	i2c_stop	(uint8_t i2c_number);
// TODO sendAddr u write_addr
// TODO number u i2c_port
int8_t	i2c_sendAddr_tx	(uint8_t i2c_number, uint8_t addr);
int8_t	i2c_sendAddr_rx	(uint8_t i2c_number, uint8_t addr);
int8_t	i2c_nack	(uint8_t i2c_number);
int8_t	i2c_ack		(uint8_t i2c_number);

uint8_t i2c_read_ack(uint8_t i2c_number);
uint8_t i2c_read_nack(uint8_t i2c_number);

uint8_t i2c_write_ack(uint8_t i2c_number, uint8_t data);
uint8_t i2c_write_nack(uint8_t i2c_number, uint8_t data);

#endif

// XXX major zajeb: vrati npr 12 kad timeouta sto moze ispast kao da je procitao nesto sa I2C-a
