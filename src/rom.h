// CReated 150214
#ifndef ROM_H
#define ROM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include "i2c.h"
#include "eeprom.h" 	// TODO zasad se zove ovako

/*************************************************************************************************
  						low level, hw
*************************************************************************************************/
void rom_write_i2c(int addr, int data);
void rom_write_spi(int addr, int data);
void rom_write_default(int addr, int data);
int rom_read_i2c(int addr);
int rom_read_spi(int addr);
int rom_read_default(int addr);
/*************************************************************************************************
*************************************************************************************************/
typedef enum 
{
	WRONG_PROTOCOL = 0,
	SPI,
	I2C
} protocol_t;

/*
void (*write_table[])(int addr, int data) = {rom_write_default, rom_write_spi, rom_write_i2c};	// tablica sa write funkcijama
int (*read_table[])(int addr)			  = {rom_read_default,  rom_read_spi,  rom_read_i2c};	// tablica sa read funkcijama
*/

typedef struct
{
	int capacity_kB;
	uint32_t size_bits;	// construktor ce popunit ostale
	uint32_t size_kB;
	uint32_t size_MB;
	int protocol;
	void (*write)(int, int);
	int  (*read) (int);
	//int  (*init) (int);	// TODO
	void (*create)(void);
	int  (*get_size)(void);
	int initialized;
} rom_t;

// globalno polje odakle ce vracat adrese, malloc je za curice
#define MAX_ROMS 5

//rom_t rom_array[MAX_ROMS] = {};

//unsigned int created_roms = 0;
/*************************************************************************************************
*************************************************************************************************/
void rom_constructor(rom_t *self);
void rom_print(rom_t *self);
void rom_init(rom_t *self);
void rom_example();

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif	// ROM_H
