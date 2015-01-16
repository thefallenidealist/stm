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
	/* datasheet kaze
	   100 kHz - 1.8V
	   400 kHz - 3.3V
	   1 MHz   - 5V
	 */
	//i2c_init(2, 400000);	// ne ide brze

	// XXX cudno radi na 400 kHz, nekad procita dobro, nekad ne
	i2c_init(2, 100000);
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
	//printf("eeprom_write: addr %d 0x%X check: %d\n", addr, addr, eeprom_addr_check(addr));

	if (eeprom_addr_check(addr))
	{
		return -1;
	}

	uint8_t addrH = addr >> 8;
	uint8_t addrL = addr * 0x00FF;

	i2c_start(2);

	i2c_sendAddr_tx(2, EEPROM_ADDR_W);	// posalji adresu slavea sa kojim treba komunicirat
	i2c_write(2, addrH);	// posalji adresu registra u koji cemo pisat
	i2c_write(2, addrL);
	i2c_write(2, data);	// posalji podatak u registar

	i2c_stop(2);	// gotovi smo zasad, generiraj stop

	//delay_ms(2);	// treba mu mali delay
			// prebaceno prije _read(), izgleda da ovdje nije potrebno

	delay_ms(5);
	return 0;
}

/**************************************************************************************************
*  					eeprom_read(void)					  *
**************************************************************************************************/
uint8_t eeprom_read(uint16_t addr)
{
	if (eeprom_addr_check(addr))
	{
		return -1;
	}

	delay_ms(5);	// magic solver :)
			/*
			ako se ispod u main ispod _example() odmah pozove clock_print() i sve je 
			kompajlirano sa -O2 razjebe se, obicno samo ispise ispravno prvi puta nakon 
			reflasha, nakon reseta ili hw reseta vrati 161

			ne moze bit unutar _write() jer ne pomaze
			*/

	uint8_t addrH = addr >> 8;
	uint8_t addrL = addr * 0x00FF;
	uint8_t data = 0;

	i2c_start(2);

	i2c_sendAddr_tx(2, EEPROM_ADDR_W);	// w addr
	i2c_write(2, addrH);	// w reg
	i2c_write(2, addrL);

	// ponovo start
	//i2c_start(2);	// patchirani _start()
	// patchirani: Sjebano radi kad je "patchiran" a ovaj ovdje ispod ne smije imat while() ponovo prije 
	// generate start jer je I2C zauzet

	// TODO doradit ovo dolje 
	uint8_t timeout = 0xFF;
	I2C_GenerateSTART(I2C2, ENABLE);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT))
	{
		if ((timeout--) == 0)
		{
		       return 10;
		}
	}

	i2c_sendAddr_rx(2, EEPROM_ADDR_R);	// w addr
	i2c_nack(2);	// NACK, ide prije reada
	//i2c_read(2);			// XXX ne radi iako samo pozove funkciju ispod, ima dovoljno stacka
	data = I2C_ReceiveData(I2C2);	// XXX

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

	//uint8_t status = eeprom_write(0x1234, 123);
	//eeprom_write(0x1235, 222);
	//eeprom_write(0x1234, 111);
	//uint8_t status = eeprom_write(0x1234, 111);
	//printf("EEPROM write status: %d\n", status);
	//delay_ms(5);
	read = eeprom_read(0x1234);
	printf("EEPROM read: %d\n", read);
	read = eeprom_read(0x1235);
	printf("EEPROM read: %d\n", read);
}
