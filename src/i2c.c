// created 141205

#include "i2c.h"

uint8_t i2c_start(void)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;
	// generiraj start signal
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C1, ENABLE);

	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
	{
		if ((timeout--) == 0)
		       return 10;
	}

	return 0;
}

void i2c_stop(void)
{
	I2C_GenerateSTOP(I2C1, ENABLE);
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
}

uint8_t i2c_sendAddr(uint8_t addr)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;
	// posalji adresu slavea sa kojim treba komunicirat
	I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		if ((timeout--) == 0)
		       return 11;
	}

	return 0;
}

// TODO read

uint8_t i2c_write(uint8_t data)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;

	I2C_SendData(I2C1, data);	// 8b
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if ((timeout--) == 0)
		       return 13;
	}

	return 0;
}
