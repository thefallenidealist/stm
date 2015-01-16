#include "spi.h"

uint8_t spi_rw(uint8_t data8)
{
	SPI1->DR = data8;
	while (!(SPI1->SR & SPI_I2S_FLAG_TXE));		// wait for TX
	while (!(SPI1->SR & SPI_I2S_FLAG_RXNE));	// wait for RX
	while (SPI1->SR & SPI_I2S_FLAG_BSY);		// wait until SPI is avaible

	return SPI1->DR;
}

uint16_t spi_rw16(uint16_t data16)
{
	SPI1->DR = data16;
	while (!(SPI1->SR & SPI_I2S_FLAG_TXE));		// wait for TX
	while (!(SPI1->SR & SPI_I2S_FLAG_RXNE));	// wait for RX
	while (SPI1->SR & SPI_I2S_FLAG_BSY);		// wait until SPI is avaible

	return SPI1->DR;
}
