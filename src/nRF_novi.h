#ifndef NRF_H
#define NRF_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
//#include <stdlib.h> 	// atoi
#include <stdbool.h>

#include "debug.h"
#include "gpio.h"
#include "spi.h"
#include "delay.h"

typedef struct
{
	uint8_t spi_port;
	uint8_t spi_speed_MHz;	// TODO
	uint16_t spi_prescaler;
	char	*cs;
	char	*ce;
	char	*irq;
} nRF_hw_t;

void 	nRF_main();
int8_t 	nRF_init(nRF_hw_t *nRF0);

static uint8_t read_reg(nRF_hw_t *nRF0, uint8_t reg);
static void ce(nRF_hw_t *nRF0, state_t state);
static void cs(nRF_hw_t *nRF0, state_t state);
static void print_reg(nRF_hw_t *nRF0, uint8_t reg);
static uint8_t write_reg(nRF_hw_t *nRF0, uint8_t reg, uint8_t arg);



#endif
