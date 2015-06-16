#include "spi.h"

//void spi_write(uint8_t data8)
void spi_write_fast(uint8_t data8)
{
	// SPI write optimiziran za brzinu
	// ako ceka na RX i jel SPI dostupan onda mu treba 97-100 ms, ovako 54 ms
	SPI1->DR = data8;
	while (!(SPI1->SR & SPI_I2S_FLAG_TXE));		// wait for TX
}

//void spi_write16(uint16_t data16)
void spi_write16_fast(uint16_t data16)
{

	// tek za 1-2 ms brzi neko 2x pozivanje spi_write();

	//uint8_t dataL = data16 & 0xFF;
	//uint8_t dataH = data16 >> 8;

	//SPI1->DR = dataH;
	SPI1->DR = data16 >> 8;
	while (!(SPI1->SR & SPI_I2S_FLAG_TXE));		// wait for TX
	//SPI1->DR = dataL;
	SPI1->DR = data16 & 0xFF;
	while (!(SPI1->SR & SPI_I2S_FLAG_TXE));		// wait for TX
}

uint16_t spi_rw16(uint16_t data16)
{
	SPI1->DR = data16;
	while (!(SPI1->SR & SPI_I2S_FLAG_TXE));		// wait for TX
	while (!(SPI1->SR & SPI_I2S_FLAG_RXNE));	// wait for RX
	while (SPI1->SR & SPI_I2S_FLAG_BSY);		// wait until SPI is avaible

	return SPI1->DR;
}

uint8_t spi_rw(uint8_t data8)
{
	SPI1->DR = data8;
	while (!(SPI1->SR & SPI_I2S_FLAG_TXE));		// wait for TX
	while (!(SPI1->SR & SPI_I2S_FLAG_RXNE));	// wait for RX
	while (SPI1->SR & SPI_I2S_FLAG_BSY);		// wait until SPI is avaible

	return SPI1->DR;
}
