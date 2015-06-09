// INFO 5V divajs (ili amputirat jos koji dio)
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
// *************************************** local includes *****************************************
#include "delay.h"
#include "i2c.h"
// *************************************** defines ************************************************
#define BMP_ADDR_R	0xEF
#define BMP_ADDR_W	0xEE

// settings
#define BMP_I2C_PORT	2
#define BMP_I2C_SPEED	100000

// *************************************** function prototypes ************************************
void 	bmp180_init				(void);
//int8_t	bmp180_write			(uint8_t reg, uint8_t data);
//int16_t bmp180_read				(uint8_t reg);
//void	bmp180_calibration		(void);
//int16_t bmp180_get_temperature	(void);
int32_t	bmp180_get_temperature	(void);
int32_t bmp180_get_pressure		(void);
void	bmp180_print			(void);
void 	bmp180_example			(void);
float	bmp180_get_temperature_float	(void);

/*
   XXX ne moze ic iznad 29.6°C:
baro: 29.6°C
baro: 6310.3°C
*/


#endif
