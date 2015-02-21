#ifndef SPI_H
#define SPI_H

#ifdef STM32F10X_MD
	#include "stm32f10x_spi.h"
#endif

#ifdef STM32F4XX
	#include "stm32f4xx_spi.h"
	#include "stm32f4xx_dma.h"
#endif

#include "debug.h"
/*
   SPI1	SCK		PA5
   		MISO	PA6
		MOSI	PA7
   SPI2	SCK		PB13
   		MISO	PB14
		MOSI	PB15
 */

int8_t 	spi_init	(uint8_t spi_port, uint16_t spi_prescaler);
void 	spi_write_fast(uint8_t spi_port, uint8_t data8);
void 	spi_write16_fast(uint8_t spi_port, uint16_t data16);
uint16_t spi_rw16(uint8_t spi_port, uint16_t data16);
uint8_t	spi_rw(uint8_t spi_port, uint8_t data8);

#endif
