#ifdef STM32F10X_MD
	#include "stm32f10x_spi.h"
#endif
#ifdef STM32F4XX
	#include "stm32f4xx_spi.h"
#endif

uint8_t spi_rw(uint8_t data8);
uint16_t spi_rw16(uint16_t data16);

