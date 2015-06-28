#ifndef NRF_H
#define NRF_H

#ifdef __cplusplus
extern "C"
#endif

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "debug.h"
#include "gpio.h"
#include "spi.h"
#include "delay.h"
#include "convert.h"

#define NRF_SPI	1			// F1, F4		PA{5,6,7}
#define NRF_ADDRESS_WIDTH	5
#define NRF_FIFO_SIZE		32
#define NRF_PAYLOAD_SIZE	32

#ifdef STM32F1
	#define NRF_RX
	//#define NRF_TX
	#define NRF_SPI_PRESCALER 32
	#define NRF_CS	"PB0"
	#define NRF_CE	"PB2"
	#define NRF_IRQ	"PB1"	// EXTI1
#endif
#ifdef STM32F4
	#define NRF_TX
	//#define NRF_RX
	#define NRF_SPI_PRESCALER 64
	#define NRF_CS	"PA4"
	#define NRF_CE	"PA3"
	#define NRF_IRQ	"PA2"	// XXX, NC, treba lemit
#endif

typedef enum
{
	 TX = 0,
	PTX = 0,
	 RX = 1,
	PRX = 1,
	MODE_ERROR
} nRF_mode_t;

typedef struct
{
	uint8_t spi_port;
	//uint8_t spi_speed_MHz;	// TODO
	// max 10 MHz SPI
	uint16_t spi_prescaler;
	char	*cs;
	char	*ce;
	char	*irq;
	// ovo ispod i nije bas hw, al kjebat ga
	bool	dynamic_payload;
	char	RX_buffer[NRF_FIFO_SIZE+1];	// +1 for NULL char
} nRF_hw_t;

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
} nRF_delay_t;

// TODO uppercase?
typedef enum
{
	datarate_1Mbps	 = 0,
	datarate_2Mbps	 = 1,
	datarate_250kbps = 3	// INFO not implemented
} nRF_datarate_t;

typedef enum
{
	power_minus_18dBm = 0,
	power_minus_12dBm = 1,
	power_minus_6dBm  = 2,
	power_0dBm        = 3
} nRF_output_power_t;

typedef enum
{
	payload_pipe0 = 0,
	payload_pipe1 = 1,
	payload_pipe2 = 2,
	payload_pipe3 = 3,
	payload_pipe4 = 4,
	payload_pipe5 = 5,
	pipe_not_used = 6,
	RX_FIFO_empty = 7
} nRF_payload_pipe_t;

typedef enum
{
	// INFO pipe2 je vec zauzeto u unistd.h pa zato P2
	P0 = 0,
	P1 = 1,
	P2 = 2,
	P3 = 3,
	P4 = 4,
	P5 = 5
} nRF_pipe_t;

typedef enum
{
	CRC_LENGTH_1BTYE = 0,
	CRC_LENGTH_2BTYE = 1
} nRF_crc_length_t;

typedef enum
{
	NRF_SEND_IN_PROGRESS	= 0,	// TX_DS = 0, MAX_RT = 0
	NRF_SEND_FAILED			= 1,	// MAX_RT = 1
	NRF_SEND_SUCCESS		= 2,	// TX_DS = 1
	NRF_SEND_TIMEOUT		= 3,	// software timeout
	NRF_ACK					= 8,	// TODO preimenovat
	NRF_SEND_INVALID
} nRF_write_status_t;

extern nRF_hw_t *grf;	// pointer na objekt/struct

/*************************************************************************************************
				private function prototypes
*************************************************************************************************/
/*
static void 	ce				(nRF_hw_t *nRF0, state_t state)	__attribute__((unused));
static void 	cs				(nRF_hw_t *nRF0, state_t state);
static uint8_t 	read_reg		(nRF_hw_t *nRF0, uint8_t reg);
static void 	print_reg		(nRF_hw_t *nRF0, uint8_t reg);
static void		write_reg		(nRF_hw_t *nRF0, uint8_t reg);
static void print_address(nRF_hw_t *nRF0, uint8_t mode);
*/
// INFO static funkcije moraju bit inline ili __atribute__((unused)) da ne javi warning
static inline void nRF_clear_buffer(char *buffer);
//static uint8_t 	write_reg_full	(nRF_hw_t *nRF0, uint8_t reg, uint8_t value) __attribute__((unused));	// [-Wunused-function]
static void write_reg_full	(nRF_hw_t *nRF0, uint8_t reg, uint8_t value) __attribute__((unused));	// [-Wunused-function]
static inline void nRF_start_listening	(nRF_hw_t *nRF0);
static inline void nRF_stop_listening	(nRF_hw_t *nRF0);
static inline void nRF_flush_TX		(nRF_hw_t *nRF0);
static inline void nRF_flush_RX		(nRF_hw_t *nRF0);
//static inline void nRF_write_TX_FIFO(nRF_hw_t *nRF0, char *buffer, uint8_t length, bool dynamic_payload, uint8_t empty_payload);
static inline void nRF_write_TX_FIFO(nRF_hw_t *nRF0, char *buffer, uint8_t length, bool dynamic_payload, uint8_t empty_payload);
static inline void nRF_read_RX_FIFO	(nRF_hw_t *nRF0, uint8_t payload_size);
static inline void nRF_write_payload(nRF_hw_t *nRF0, char *buffer, uint8_t length);


/*************************************************************************************************
				public function prototypes
*************************************************************************************************/
int8_t	nRF_main(void);
int8_t 	nRF_hw_init(nRF_hw_t *nRF0);


void	nRF_set_address_width		(nRF_hw_t *nRF0, uint8_t width);
uint8_t nRF_get_address_width		(nRF_hw_t *nRF0);

int8_t	nRF_set_retransmit_delay		(nRF_hw_t *nRF0, nRF_delay_t delay);
uint16_t nRF_get_retransmit_delay_in_us	(nRF_hw_t *nRF0);
void 	nRF_set_retransmit_count		(nRF_hw_t *nRF0, uint8_t count);
uint8_t nRF_get_retransmit_count		(nRF_hw_t *nRF0);
uint8_t nRF_get_lost_packets			(nRF_hw_t *nRF0);
uint8_t nRF_get_retransmitted_packets	(nRF_hw_t *nRF0);

void 	nRF_set_channel		(nRF_hw_t *nRF0, uint8_t ch);
uint8_t nRF_get_channel		(nRF_hw_t *nRF0);

void 	nRF_set_datarate	(nRF_hw_t *nRF0, nRF_datarate_t datarate);
//uint8_t	nRF_get_datarate	(nRF_hw_t *nRF0);	// vrati uljepsano
nRF_datarate_t	nRF_get_datarate	(nRF_hw_t *nRF0);

bool 	nRF_is_RX_data_ready	(nRF_hw_t *nRF0);
bool 	nRF_is_TX_data_sent		(nRF_hw_t *nRF0);
bool 	nRF_is_TX_data_failed	(nRF_hw_t *nRF0);
bool 	nRF_is_TX_full			(nRF_hw_t *nRF0);	
bool	nRF_is_TX_full2			(nRF_hw_t *nRF0);
bool 	nRF_is_TX_empty			(nRF_hw_t *nRF0);
bool	nRF_is_RX_empty2		(nRF_hw_t *nRF0);
bool 	nRF_is_RX_empty			(nRF_hw_t *nRF0);
bool 	nRF_is_RX_full			(nRF_hw_t *nRF0);
bool	nRF_is_present			(nRF_hw_t *nRF0);
void 	nRF_clear_bits			(nRF_hw_t *nRF0);
void	nRF_clear_RX_data_ready(nRF_hw_t *nRF0);

int8_t  			nRF_enable_pipe		(nRF_hw_t *nRF0, nRF_pipe_t pipe);
nRF_payload_pipe_t 	nRF_get_payload_pipe(nRF_hw_t *nRF0);
void				nRF_print_enabled_pipe(nRF_hw_t *nRF0);

int8_t		nRF_set_RX_address		(nRF_hw_t *nRF0, nRF_pipe_t pipe, uint8_t address[]);
int8_t		nRF_set_TX_address		(nRF_hw_t *nRF0, uint8_t address[]);
void		nRF_print_RX_address	(nRF_hw_t *nRF0, nRF_pipe_t pipe);
void		nRF_print_TX_address	(nRF_hw_t *nRF0);

uint8_t		nRF_set_payload_size	(nRF_hw_t *nRF0, nRF_pipe_t pipe, uint8_t payload_size);
uint8_t		nRF_get_payload_size	(nRF_hw_t *nRF0, nRF_pipe_t pipe);

void 		nRF_power_on			(nRF_hw_t *nRF0);
void 		nRF_power_off			(nRF_hw_t *nRF0);
bool 		nRF_is_powered			(nRF_hw_t *nRF0);
void 		nRF_set_output_power	(nRF_hw_t *nRF0, nRF_output_power_t power);

void 		nRF_set_mode	(nRF_hw_t *nRF0, nRF_mode_t mode);
nRF_mode_t 	nRF_get_mode	(nRF_hw_t *nRF0);

int8_t 	nRF_set_CRC_length	(nRF_hw_t *nRF0, nRF_crc_length_t crc_length);
uint8_t	nRF_get_CRC_length	(nRF_hw_t *nRF0);
void 	nRF_enable_CRC		(nRF_hw_t *nRF0);
void 	nRF_disable_CRC		(nRF_hw_t *nRF0);

//bool	nRF_read_payload			(nRF_hw_t *nRF0);	// 1 ako je zapisao novi payload u buffer, 0 ako nije
bool	nRF_read					(nRF_hw_t *nRF0);	// 1 ako je zapisao novi payload u buffer, 0 ako nije
//void 	nRF_write_payload			(nRF_hw_t *nRF0, char *buffer, uint8_t length);
void 	nRF_write_payload_no_ack	(nRF_hw_t *nRF0, char *buffer, uint8_t length);
nRF_write_status_t nRF_write		(nRF_hw_t *nRF0, char *buffer, uint8_t length);

nRF_pipe_t 	nRF_get_enabled_pipe	(nRF_hw_t *nRF0);
void 		nRF_enable_auto_ack		(nRF_hw_t *nRF0, nRF_pipe_t pipe);
void 		nRF_disable_auto_ack	(nRF_hw_t *nRF0, nRF_pipe_t pipe);
void 		nRF_debug				(nRF_hw_t *nRF0);
uint8_t 	nRF_get_payload_width	(nRF_hw_t *nRF0);
//void		nRF_write_ack			(nRF_hw_t *nRF0);
void		nRF_write_ack			(nRF_hw_t *nRF0, char *buffer, uint8_t length);
char		*nRF_read_ack			(nRF_hw_t *nRF0);

void	nRF_enable_dynamic_payload			(nRF_hw_t *nRF0);
void	nRF_disable_dynamic_payload			(nRF_hw_t *nRF0);
void	nRF_enable_dynamic_payload_ack		(nRF_hw_t *nRF0);
void	nRF_disable_dynamic_payload_ack		(nRF_hw_t *nRF0);
void	nRF_enable_dynamic_pipe				(nRF_hw_t *nRF0, nRF_pipe_t pipe);
void	nRF_disable_dynamic_pipe			(nRF_hw_t *nRF0, nRF_pipe_t pipe);
uint8_t	nRF_get_dynamic_payload_length		(nRF_hw_t *nRF0);
void	nRF_enable_dynamic_payload_noack	(nRF_hw_t *nRF0);
void	nRF_disable_dynamic_payload_noack	(nRF_hw_t *nRF0);
bool	nRF_is_dynamic_payload_enabled		(nRF_hw_t *nRF0);


#ifdef __cplusplus
extern "C"
#endif	// __cplusplus
#endif	// NRF_H
