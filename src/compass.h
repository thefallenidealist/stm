// created 150117
#ifndef COMPASS_H
#define COMPASS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
//#include <math.h>
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
#include "i2c.h"

void compass_main(void);
void compass_read_continuous();
void compass_read_single();
void compass_main_burgi(void);

#define HMC5883L_ADDRESS            0x1E // this device only has one address
#define HMC5883L_DEFAULT_ADDRESS    (HMC5883L_ADDRESS<<1)
#define HMC5883L_I2C	I2C2
#define TRUE 1
#define FALSE 0


void HMC5883L_Initialize(void);
uint8_t HMC5883L_GetSampleAveraging(void);
void HMC5883L_SetSampleAveraging(uint8_t averaging);
uint8_t HMC5883L_GetDataRate(void);
void HMC5883L_SetDataRate(uint8_t rate);
uint8_t HMC5883L_GetMeasurementBias(void);
void HMC5883L_SetMeasurementBias(uint8_t bias);
uint8_t HMC5883L_GetGain(void);
void HMC5883L_SetGain(uint8_t gain);
uint8_t HMC5883L_GetMode(void);
void HMC5883L_SetMode(uint8_t newMode);
void HMC5883L_GetHeading(s16* Mag);
bool HMC5883L_GetLockStatus(void);
bool HMC5883L_GetReadyStatus(void);
void HMC5883L_WriteBits(uint8_t slaveAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
void HMC5883L_WriteBit(uint8_t slaveAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data);
void HMC5883L_ReadBits(uint8_t slaveAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data);
void HMC5883L_ReadBit(uint8_t slaveAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data);
void HMC5883L_I2C_Init(void);
void HMC5883L_I2C_ByteWrite(u8 slaveAddr, u8* pBuffer, u8 WriteAddr);
void HMC5883L_I2C_BufferRead(u8 slaveAddr, u8* pBuffer, u8 ReadAddr, u16 NumByteToRead);



void stupnjevi();
void procitaj();

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif	// COMPASS_H
