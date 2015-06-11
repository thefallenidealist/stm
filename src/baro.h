// *************************************** description ********************************************
// BMP180 barometer/therometer driver
// INFO 5V divajs (ili amputirat jos koji dio)
// created 140916
// *************************************** sys includes *******************************************
#ifndef BARO_H
#define BARO_H

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
// settings
#define BMP_I2C_PORT	2
#define BMP_I2C_SPEED	100000

// *************************************** new data types ************************************
typedef enum
{
	Pa 		= 1,
	hPa 	= 2,
	mbar	= 2,
	kPa 	= 3
} barometer_conversion_t;

// *************************************** function prototypes ************************************
void 	bmp180_init				(void);
float	bmp180_get_temperature	(void);
float	bmp180_get_pressure		(barometer_conversion_t mjerilo);	// XXX prevest, fali rijec
float	bmp180_get_altitude		(void);
void	bmp180_print			(void);
void 	bmp180_example			(void);
void	bmp180_print_id			(void);

#endif
