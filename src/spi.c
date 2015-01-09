#include "spi.h"

uint8_t glcd_spi_send(uint8_t data8)
{
	/*
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, byte);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	//return SPI_I2S_ReceiveData(SPI1);
	return 0;
	*/
	spi1_send_receive(data8);
	return 0;
}

uint16_t glcd_spi_send16(uint16_t data16)
{
	/*
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, HalfWord);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	//return SPI_I2S_ReceiveData(SPI1);
	return 0;
	*/
	spi1_send_receive(data16);
	return 0;
}

uint8_t spi1_send_receive(uint8_t data8)
{
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, data8);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI1);
}
