#ifndef BARO_H
#define BARO_H

// created 140916
// *************************************** description ********************************************
// BMP180 barometer/therometer driver
// *************************************** sys includes *******************************************
#include <stdio.h>
#include <math.h>
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
#include "delay.h"
// *************************************** local includes *****************************************
// *************************************** defines ************************************************
#define BMP_ADDR_W	0xEE
#define BMP_ADDR_R	0xEF
#define I2C_TIMEOUT_MAX	0xFFFF
// *************************************** function prototypes ************************************
void bmp180_init(void);
uint16_t bmp180_write(uint8_t reg, uint8_t data);
int16_t bmp180_read(uint8_t reg);
void bmp180_calibration(void);
uint16_t bmp180_temperature(void);
uint32_t bmp180_pressure(void);
void bmp180_print(void);
void bmp180_example(void);

#endif
