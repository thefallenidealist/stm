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
#include "convert.h"

// TODO zasad napravljeno da samo koristi pipe0

typedef enum
{
	TX  = 0,
	PTX = 0,
	RX  = 1,
	PRX = 1,
	MODE_ERROR
} nRF_mode_t;

typedef struct
{
	uint8_t spi_port;
	uint8_t spi_speed_MHz;	// TODO
	uint16_t spi_prescaler;
	char	*cs;
	char	*ce;
	char	*irq;
	// XXX zapravo ne pripada vamo, al mi se jos ne da mijenjt sve
	// TODO ovo sve ispod maknit i ako treba direktno citat sa divajsa
	//uint8_t address_width;

	// ipak trebaju zbog returna funkcija
	uint8_t	rx_address[6][6];	// 6 pajpova, sa po max 5 bajtova adrese (+ NULL)
	uint8_t tx_address[6];
	//uint8_t rx_payload_size[6];
} nRF_hw_t;

/*
typedef struct
{
	nRF_hw_t 	hw;
	nRF_mode_t	type;
	char		*address;
} nRF_t;
*/


typedef enum
{
	DELAY_250us  = 0,
	DELAY_500us  = 1,
	DELAY_750us  = 2,
	DELAY_1000us = 3,
	DELAY_1ms    = 3,
	DELAY_1250us = 4,
	DELAY_1500us = 5,
	DELAY_1750us = 6,
	DELAY_2000us = 7,
	DELAY_2ms    = 7,
	DELAY_2250us = 8,
	DELAY_2500us = 9,
	DELAY_2750us = 10,
	DELAY_3000us = 11,
	DELAY_3ms    = 11,
	DELAY_3250us = 12,
	DELAY_3500us = 13,
	DELAY_3750us = 14,
	DELAY_4000us = 15,
	DELAY_4ms    = 15
} delay_t;
// TODO nRF_ prefiks ispreda datatypeova

typedef enum
{
	datarate_1Mbps = 0,
	datarate_2Mbps = 1
} datarate_t;

typedef enum
{
	power_minus_18dBm = 0,
	power_minus_12dBm = 1,
	power_minus_6dBm  = 2,
	power_0dBm        = 3
} output_power_t;

// reg 0x06
// TODO preimenovat ovo
typedef enum
{
	avaible_pipe0 = 0,
	avaible_pipe1 = 1,
	avaible_pipe2 = 2,
	avaible_pipe3 = 3,
	avaible_pipe4 = 4,
	avaible_pipe5 = 5,
	pipe_not_used = 6,
	RX_FIFO_empty = 7
} data_pipe_t;

typedef enum
{
	// INFO pipe2 je vec zauzeto u unistd.h
	P0 = 0,
	P1 = 1,
	P2 = 2,
	P3 = 3,
	P4 = 4,
	P5 = 5
} pipe_t;

typedef enum
{
	CRC_LENGTH_1BTYE = 0,
	CRC_LENGTH_2BTYE = 1
} crc_length_t;

extern uint8_t reg_tmp[8];
extern uint8_t nRF_RX_buffer[32];
extern uint8_t nRF_TX_buffer[32];

/*************************************************************************************************
				private function prototypes
*************************************************************************************************/
static uint8_t read_reg(nRF_hw_t *nRF0, uint8_t reg);
static void ce(nRF_hw_t *nRF0, state_t state);
static void cs(nRF_hw_t *nRF0, state_t state);
static void print_reg(nRF_hw_t *nRF0, uint8_t reg);
//static uint8_t write_reg(nRF_hw_t *nRF0, uint8_t reg, uint8_t arg, uint8_t bits);
//static uint8_t write_reg(nRF_hw_t *nRF0, uint8_t reg, uint8_t arg);
//static uint8_t write_reg(nRF_hw_t *nRF0, uint8_t reg, uint8_t value[]);
static uint8_t write_reg(nRF_hw_t *nRF0, uint8_t reg);
static uint8_t write_reg_full(nRF_hw_t *nRF0, uint8_t reg, uint8_t value);
static uint8_t get_status(nRF_hw_t *nRF0);

/*************************************************************************************************
				public function prototypes
*************************************************************************************************/
void 	nRF_main();
int8_t 	nRF_hw_init(nRF_hw_t *nRF0);
// provjereno:
void nRF_set_address_width(nRF_hw_t *nRF0, uint8_t width);			// reg 0x03
uint8_t nRF_get_address_width(nRF_hw_t *nRF0);						// reg 0x03

void 	nRF_set_retransmit_delay(nRF_hw_t *nRF0, delay_t delay);		// reg 0x04
void 	nRF_set_retransmit_count(nRF_hw_t *nRF0, uint8_t count);		// reg 0x04
void 	nRF_set_channel(nRF_hw_t *nRF0, uint8_t ch);					// reg 0x05
uint8_t nRF_get_channel(nRF_hw_t *nRF0);
void 	nRF_set_data_rate(nRF_hw_t *nRF0, datarate_t datarate);		// reg 0x06
datarate_t nRF_get_data_rate(nRF_hw_t *nRF0);						// reg 0x06
void 	nRF_set_output_power(nRF_hw_t *nRF0, output_power_t power);	// reg 0x06

bool 	nRF_is_RX_data_ready(nRF_hw_t *nRF0);							// reg 0x06, b6
void 	nRF_clear_RX_data_ready(nRF_hw_t *nRF0);						// reg 0x06, b6
bool 	nRF_is_TX_data_sent(nRF_hw_t *nRF0);							// reg 0x06, b5
void 	nRF_clear_TX_data_sent(nRF_hw_t *nRF0);						// reg 0x07, b5
data_pipe_t nRF_pipe_available(nRF_hw_t *nRF0);						// reg 0x07, b321
bool 	nRF_is_TX_full(nRF_hw_t *nRF0);								// reg 0x07, b0

uint8_t *nRF_get_RX_address(nRF_hw_t *nRF0);						// reg 0x0A
int8_t 	 nRF_set_RX_address(nRF_hw_t *nRF0, uint8_t address[]);		// reg 0x0A
//int8_t nRF_set_RX_address(nRF_hw_t *nRF0, const unsigned char address[6]);	// reg 0x0A
int8_t   nRF_set_TX_address(nRF_hw_t *nRF0, uint8_t address[]);		// reg 0x10
//int8_t nRF_set_TX_address(nRF_hw_t *nRF0, const unsigned char address[6]);		// reg 0x10
uint8_t *nRF_get_TX_address(nRF_hw_t *nRF0);						// reg 0x10
int8_t   nRF_set_RX_payload_size(nRF_hw_t *nRF0, pipe_t pipe, uint8_t payload_size);	// reg 0x{11,12,13,14,15,16}
int8_t   nRF_get_RX_payload_size(nRF_hw_t *nRF0, pipe_t pipe);		// reg 0x{11,12,13,14,15,16}

uint8_t nRF_get_lost_packets(nRF_hw_t *nRF0);						// reg 0x08
uint8_t nRF_get_retransmitted_packets(nRF_hw_t *nRF0);				// reg 0x08

int8_t  nRF_enable_pipe(nRF_hw_t *nRF0, pipe_t pipe);				// reg 0x02
void nRF_enable_CRC(nRF_hw_t *nRF0);								// reg 0x00
void nRF_disable_CRC(nRF_hw_t *nRF0);								// reg 0x00
void nRF_power_on(nRF_hw_t *nRF0);
void nRF_power_off(nRF_hw_t *nRF0);
void nRF_set_mode(nRF_hw_t *nRF0, nRF_mode_t mode);					// INFO prvo postavit mode, pa onda power_on		rijeseno
nRF_mode_t nRF_get_mode(nRF_hw_t *nRF0);
bool nRF_powered(nRF_hw_t *nRF0);

int8_t 			nRF_set_CRC_length(nRF_hw_t *nRF0, crc_length_t crc_length);
crc_length_t 	nRF_get_CRC_length(nRF_hw_t *nRF0);

uint8_t *nRF_read_payload(nRF_hw_t *nRF0, uint8_t howmany);
void nRF_write_payload(nRF_hw_t *nRF0, uint8_t length);
uint8_t nRF_get_bit(nRF_hw_t *nRF0, uint8_t reg, uint8_t bit);




/*
   // standby-I
This is the mode the nRF24L01 returns to from TX or RX mode when CE is set low.
   */








#endif
