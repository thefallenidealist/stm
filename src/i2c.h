// created 141205
#ifndef I2C_H
#define I2C_H

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"

#define I2C_TIMEOUT_MAX 0xFFFF


uint8_t i2c_start(void);
void i2c_stop(void);
uint8_t i2c_sendAddr(uint8_t addr);
// TODO read
uint8_t i2c_write(uint8_t data);

#endif
