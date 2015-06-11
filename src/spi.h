#ifndef SPI_H
#define SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined STM32F10X_MD || defined STM32F1
	#include "stm32f10x_rcc.h"
	#include "stm32f10x_gpio.h"
	#include "stm32f10x_spi.h"
#endif

#if defined STM32F4XX || defined STM32F4
	#include "stm32f4xx_rcc.h"
	#include "stm32f4xx_gpio.h"
	#include "stm32f4xx_spi.h"
	//#include "stm32f4xx_dma.h"
#endif

#include "debug.h"
/*
F4:
   SPI1	SCK		PA5
   		MISO	PA6
		MOSI	PA7
   SPI2	SCK		PB13
   		MISO	PB14
		MOSI	PB15
 */

// po default i F1 i F4 imaju iste SPI1 pinove
#define SPI1_PORT	GPIOA
#define SPI1_SCK	GPIO_Pin_5	// PA5
#define SPI1_MISO	GPIO_Pin_6
#define SPI1_MOSI	GPIO_Pin_7	// PA7
#ifdef STM32F4
#define SPI1_SCK_AF		GPIO_PinSource5
#define SPI1_MISO_AF	GPIO_PinSource6
#define SPI1_MOSI_AF	GPIO_PinSource7
#endif

int8_t 	spi_init			(uint8_t spi_port, uint16_t spi_prescaler);
void 	spi_write_fast		(uint8_t spi_port, uint8_t data8);
void 	spi_write16_fast	(uint8_t spi_port, uint16_t data16);
uint16_t spi_rw16			(uint8_t spi_port, uint16_t data16);
uint8_t	spi_rw				(uint8_t spi_port, uint8_t data8);

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif	// SPI_H
