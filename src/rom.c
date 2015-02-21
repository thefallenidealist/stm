#include "rom.h"

/*************************************************************************************************
  						low level, hw
*************************************************************************************************/
void rom_write_i2c(int addr, int data)
{
	printf("%s() writing %d to addr %d\n", __func__, data, addr);
	// uint8_t eeprom_write(uint16_t addr, uint8_t data)
	eeprom_write(addr, data);	// TODO imena funkcija
}

void rom_write_spi(int addr, int data)
{
	printf("%s() writing %d to addr %d\n", __func__, data, addr);
	// TODO
}

void rom_write_default(int addr, int data)
{
	printf("\t\t\t\t%s(): Please select the right protocol\n", __func__);
}

int rom_read_i2c(int addr)
{
	printf("%s() reading from addr %d\n", __func__, addr);
	return 101;
}

int rom_read_spi(int addr)
{
	printf("%s() reading from addr %d\n", __func__, addr);
	return 102;
}

int rom_read_default(int addr)
{
	//printf("%s() reading from %d\n", __func__, addr);
	printf("\t\t\t\t%s(): Please select the right protocol\n", __func__);
	return -1;
}

/*************************************************************************************************
*************************************************************************************************/

void (*write_table[])(int addr, int data) = {rom_write_default, rom_write_spi, rom_write_i2c};	// tablica sa write funkcijama
int (*read_table[])(int addr)			  = {rom_read_default,  rom_read_spi,  rom_read_i2c};	// tablica sa read funkcijama

// globalno polje odakle ce vracat adrese, malloc je za curice
rom_t rom_array[MAX_ROMS] = {};
unsigned int created_roms = 0;
/*************************************************************************************************
*************************************************************************************************/
void rom_constructor(rom_t *self)
{
	printf("%s()\n", __func__);

	// popuni defaultnim vrijednostima
	self->capacity_kB = 0;
	self->protocol = 0;
	self->write = write_table[WRONG_PROTOCOL];
	self->read  = read_table[WRONG_PROTOCOL];
	self->initialized = 0;

	printf("\n");
}

void rom_print(rom_t *self)
{
	printf("%s()\n", __func__);

	if (self->initialized == 1)
	{
		printf("capacity: %d kB\n", self->capacity_kB);
		printf("protocol: %d\n", self->protocol);
		printf("write func: \n");
		self->write(0, 0);	// samo radi demonstracije
		self->read(0);		// samo radi demonstracije
	}
	else
	{
		printf("ERROR: Please setup ROM before printing\n");
	}

	printf("\n");
}

void rom_init(rom_t *self)
{
	printf("%s()\n", __func__);

	// provjeri koji je protokol i preusmjeri ga na pravu funkciju
	self->write = write_table[self->protocol];
	self->read  = read_table[self->protocol];

	// provjeri jel ima nepostavljeni atribut
	if (self->protocol == 0)
	{
		printf("ERROR: please setup protocol for ROM\n");
	}
	if (self->capacity_kB == 0)
	{
		printf("ERROR: please set capacity for ROM\n");
	}
	else	// sve je oke
	{
		self->initialized = 1;
	}

	printf("\n");
}


/*
rom_t *rom_create(protocol_t protocol, int kB)
{
	rom_t *new_rom = &rom_array[created_roms++];

	new_rom->protocol = protocol;
	new_rom->capacity_kB = kB;

	// CP iz rom_init
	// provjeri koji je protokol i preusmjeri ga na pravu funkciju
	new_rom->write = write_table[new_rom->protocol];
	new_rom->read  = read_table[new_rom->protocol];

	// provjeri jel ima nepostavljeni atribut
	if (new_rom->protocol == 0)
	{
		printf("ERROR: please setup protocol for ROM\n");
	}
	if (new_rom->capacity_kB == 0)
	{
		printf("ERROR: please set capacity for ROM\n");
	}
	else	// sve je oke
	{
		new_rom->initialized = 1;
	}

	return new_rom;
}
*/

void rom_example()
{

	rom_t	moj_rom;
	rom_constructor(&moj_rom);
	//rom_print(&moj_rom);

	printf("Idemo setupirat ROM\n");
	moj_rom.capacity_kB = 4;
	moj_rom.protocol = I2C;
	rom_init(&moj_rom);

	rom_print(&moj_rom);
}
