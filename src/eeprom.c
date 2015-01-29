// created 140918
// *************************************** description ********************************************
// Atmel 24C256 I2C EEPROM driver
#include "eeprom.h"

// moj je AT24C256	256K (32,768 x 8)

// TODO
// provjere sto su vratile i2c_*
// provjeravanje adrese, da ne pokusa zapisat izvan adresnog prostora ROMa

/**************************************************************************************************
*  					eeprom_init(void)					  *
**************************************************************************************************/
void eeprom_init(void)
{
	// XXX moje djubre ne radi na 5V iako bi morao
	/* datasheet kaze
	   100 kHz - 1.8V
	   400 kHz - 3.3V
	   1 MHz   - 5V
	 */
	//i2c_init(2, 400000);	// nop, nece da ga jebes, 3.3V
	//i2c_init(2, 300000);	// nop
	i2c_init(2, 200000);	// moze, na 3.3V
}

bool eeprom_addr_check(uint16_t addr)
{
	// najveca adresa je 32 768 = 0x8000
	// 2^16 je 64k

	if ((addr > 32768) || (addr < 0))
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

/**************************************************************************************************
*  					eeprom_write(void)					  *
**************************************************************************************************/
// zapisuje 8b data na 16b addr
// TODO uint -> int
uint8_t eeprom_write(uint16_t addr, uint8_t data)
{
	if (eeprom_addr_check(addr))
	{
		return -1;
	}

	uint8_t addrH = addr >> 8;
	uint8_t addrL = addr & 0x00FF;

	i2c_start(2);

	i2c_sendAddr_tx(2, EEPROM_ADDR_W);	// posalji adresu slavea sa kojim treba komunicirat
	i2c_write(2, addrH);	// posalji adresu registra u koji cemo pisat
	i2c_write(2, addrL);
	i2c_write(2, data);	// posalji podatak u registar

	i2c_stop(2);

	delay_ms(20);	// datasheet, page 5, max 20 ms write delay, after _stop()
			// radi i sa 5 ms
			// ako ga nema onda nece zapisat na adrese 0x2, 0x4, 0x6, 0x8

	return 0;
}

/**************************************************************************************************
*  					eeprom_read(void)					  *
**************************************************************************************************/
uint8_t eeprom_read(uint16_t addr)
{
	// TODO
	// kako ovdje znat jel return funkcije ono sto treba ili error

	if (eeprom_addr_check(addr))
	{
		return -1;
	}

	uint8_t addrH = addr >> 8;
	uint8_t addrL = addr & 0x00FF;
	uint8_t data = 0;

	i2c_start(2);
	i2c_sendAddr_tx(2, EEPROM_ADDR_W);
	i2c_write(2, addrH);
	i2c_write(2, addrL);
	// INFO nema nikakvog utjecaja _ack ili _nack
	//i2c_write_ack(2, addrH);
	//i2c_write_ack(2, addrL);

	i2c_restart(2);
	i2c_sendAddr_rx(2, EEPROM_ADDR_R);
	data = i2c_read_nack(2);

	i2c_stop(2);

	return data;
}

/**************************************************************************************************
*  					eeprom_example(void)					  *
**************************************************************************************************/
void eeprom_example(void)
{
	eeprom_init();

	uint8_t read;

	read = eeprom_read(0x1234);
	printf("EEPROM read: %d\n", read);
	read = eeprom_read(0x1235);
	printf("EEPROM read: %d\n", read);

	eeprom_write(0x1234, 123);
	eeprom_write(0x1235, 114);
	//eeprom_write(0x1236, 125);

	/*
	// ocisti
	for (uint16_t i=0; i<32768; i++)	// moj ima 32kB
	{
		//printf("treba zapisat adresu 0x%X %d\n", i, i);
		eeprom_write((uint16_t)i, 0x0);
	}
	*/
}
