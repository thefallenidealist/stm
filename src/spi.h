#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"

uint8_t glcd_spi_send(uint8_t data8);
uint16_t glcd_spi_send16(uint16_t data16);
uint8_t spi1_send_receive(uint8_t data8);
