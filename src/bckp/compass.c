#include "compass.h"
#include <math.h>

#define address 0x1E //0011110b, I2C 7bit address of HMC5883

#define HMC5883_ADDR_W	0x3C
#define HMC5883_ADDR_R	0x3D
// automatski updatea register pointer (koji ne moze bit procitan preko I2C)

// 0x3C, 0x0A	za citanje reg 10

/* mjerenje
    
For each “measurement”, the ASIC: 
1. Sends a “Set” pulse 
2. Takes one measurement (Mset) 
3. Sends a “Reset” pulse 
4. Takes another measurement (Mreset) 
5. Puts the following result in sensor’s data output register:   
 
  Output = [Mset – Mreset] / 2 
*/

// default: single measurement mode

/*
	Registers:
Address Name 				Access 
00 	Configuration Register A	Read/Write 
01	Configuration Register B	Read/Write 
02 	Mode Register 			Read/Write 
03 	Data Output X MSB Register 	Read 
04 	Data Output X LSB Register 	Read 
05 	Data Output Z MSB Register 	Read 
06 	Data Output Z LSB Register 	Read 
07 	Data Output Y MSB Register 	Read 
08 	Data Output Y LSB Register 	Read 
09 	Status Register 		Read 
10 	Identification Register A 	Read 
11 	Identification Register B 	Read 
12 	Identification Register C 	Read 
*/

// neopisana mjesta u registrima su 0

typedef struct 
{
	uint8_t addr;
	uint8_t MA1;	// Select number of samples averaged (1 to 8) per measurement output. 
	uint8_t MA0;	//	 00 = 1(Default); 01 = 2; 10 = 4; 11 = 8  
	uint8_t DO2;	// Data Output Rate Bits [Hz]	default: 100
	uint8_t DO1;	// 	000 - 0.75	001 - 1.5	010 - 3
	uint8_t DO0;	//	011 - 7.5	100 - 15	101 - 30	110 - 75
	uint8_t MS1;	// Measurement Mode 	defalt: 00
	uint8_t MS0;	//	00 - Normal	... tl;dr: page 12, Table 6
} register_conf1_t;
register_conf1_t register_conf1 = {0x00, 6,5,4,3,2,1,0};

typedef struct
{
	uint8_t addr;
	uint8_t GN2;	// Gain Configuration	default: 001
	uint8_t GN1;	// 	tl;dr, page 13, Table 9
	uint8_t GN0;
} register_conf2_t;
register_conf2_t register_conf2 = {0x01, 7,6,5};

typedef struct
{
	uint8_t addr;
	uint8_t HS;	// high speed  3400kHz. 
	uint8_t MD1;	// Mode Select		default: 01
	uint8_t MD0;	//	00 - continous, 01 - single
			//	10, 11 - idle
} register_mode_t;
register_mode_t register_mode = {0x02, 7,1,0};

typedef struct
{
	uint8_t addr;
	uint8_t X7;
	uint8_t X6;
	uint8_t X5;
	uint8_t X4;
	uint8_t X3;
	uint8_t X2;
	uint8_t X1;
	uint8_t X0;
} register_x1_t;	// RO
register_x1_t register_x1 = {0x03, 7,6,5,4,3,2,1,0};

typedef struct
{
	uint8_t addr;
	uint8_t X15;
	uint8_t X14;
	uint8_t X13;
	uint8_t X12;
	uint8_t X11;
	uint8_t X10;
	uint8_t X9;
	uint8_t X8;
} register_x2_t;	// RO
register_x2_t register_x2 = {0x04, 7,6,5,4,3,2,1,0};

typedef struct
{
	uint8_t addr;
	uint8_t Y7;
	uint8_t Y6;
	uint8_t Y5;
	uint8_t Y4;
	uint8_t Y3;
	uint8_t Y2;
	uint8_t Y1;
	uint8_t Y0;
} register_y1_t;	// RO
register_y1_t register_y1 = {0x05, 7,6,5,4,3,2,1,0};

typedef struct
{
	uint8_t addr;
	uint8_t Y15;
	uint8_t Y14;
	uint8_t Y13;
	uint8_t Y12;
	uint8_t Y11;
	uint8_t Y10;
	uint8_t Y9;
	uint8_t Y8;
} register_y2_t;	// RO
register_y2_t register_y2 = {0x06, 7,6,5,4,3,2,1,0};

typedef struct
{
	uint8_t addr;
	uint8_t Z7;
	uint8_t Z6;
	uint8_t Z5;
	uint8_t Z4;
	uint8_t Z3;
	uint8_t Z2;
	uint8_t Z1;
	uint8_t Z0;
} register_z1_t;	// RO
register_z1_t register_z1 = {0x07, 7,6,5,4,3,2,1,0};

typedef struct
{
	uint8_t addr;
	uint8_t Z15;
	uint8_t Z14;
	uint8_t Z13;
	uint8_t Z12;
	uint8_t Z11;
	uint8_t Z10;
	uint8_t Z9;
	uint8_t Z8;
} register_z2_t;	// RO
register_z2_t register_z2 = {0x08, 7,6,5,4,3,2,1,0};

typedef struct
{
	uint8_t addr;
	uint8_t LOCK;	/* Data output register lock.  This bit is set when: 
			1.some but not all for of the six data output registers have 
			been read, 
			2. Mode register has been read.   
			When this bit is set, the six data output registers are locked 
			and any new data will not be placed in these register until 
			one of these conditions are met: 
			1.all six bytes have been read, 2. the mode register is 
			changed, 
			3. the measurement configuration (CRA) is changed, 
			4. power is reset.
			*/
	uint8_t RDY;	/* Ready Bit.  Set when data is written to all six data registers.  
			Cleared when device initiates a write to the data output 
			registers and after one or more of the data output registers 
			are written to.  When RDY bit is clear it shall remain cleared 
			for a 250 μs.  DRDY pin can be used as an alternative to 
			the status register for monitoring the device for 
			measurement data. 
			*/
} register_status_t;	// RO
register_status_t register_status = {0x09, 1,0};

typedef struct
{
	uint8_t addr;
} register_identification1_t;
register_identification1_t register_identification1 = {0x0A};

typedef struct
{
	uint8_t addr;
} register_identification2_t;
register_identification2_t register_identification2 = {0x0B};

typedef struct
{
	uint8_t addr;
} register_identification3_t;
register_identification3_t register_identification3 = {0x0C};





//uint8_t register_read(uint8_t reg)
int8_t register_read(uint8_t reg)
{
	//printf("\tINFO: %s() start in file: %s at line: %d\n", __func__, __FILE__, __LINE__);
	uint8_t received = 0;

	/*
	i2c_ack(2);
	i2c_start(2);
	i2c_sendAddr_tx(2, HMC5883_ADDR_W);	// send slave address
	i2c_write_old(2, reg);	// posalji adresu registra
	i2c_stop(2);
	*/

	i2c_write(2, HMC5883_ADDR_W, reg);	// novi

	/*
	// restart as receiver
	i2c_start_force(2);
	i2c_sendAddr_rx(2, HMC5883_ADDR_R);
	i2c_nack(2);
	//i2c_ack(2);
	received = I2C_ReceiveData(I2C2);
	i2c_stop(2);
	*/

	received = i2c_read(2, HMC5883_ADDR_R);	// novi

	//printf("\tINFO: %s() end in file: %s at line: %d\n", __func__, __FILE__, __LINE__);
	return received;
}

int8_t register_write(uint8_t reg, uint8_t data)
{
	//printf("\tINFO: %s() start in file: %s at line: %d\n", __func__, __FILE__, __LINE__);

	/*
	// XXX ovome treba restart da prodje
	i2c_start(2);
	i2c_sendAddr_tx(2, HMC5883_ADDR_W);

	i2c_write_old(2, reg);
	i2c_write_old(2, data);
	//i2c_ack(2);	// mora bit inace se zablokira kod citanja ID registara
	i2c_stop(2);
	*/

	//i2c_write2(2, HMC5883_ADDR_W, reg, data);
	i2c_write2(3, HMC5883_ADDR_W, reg, data);

	// XXX ne radi novi vrite
	/*
	i2c_write(2, HMC5883_ADDR_W, reg);
	i2c_write(2, HMC5883_ADDR_W, data);
	*/

	//printf("\tINFO: %s() end in file: %s at line: %d\n", __func__, __FILE__, __LINE__);
	return 0;
}

void register_print(uint8_t reg)
{
	//printf("\tINFO: %s() start in file: %s at line: %d\n", __func__, __FILE__, __LINE__);
	uint8_t received;
	received = register_read(reg);

	printf("register: 0x%x = 0x%x\n", reg, received);
	printf("\td7: %d\n", (received >> 7) & 1);
	printf("\td6: %d\n", (received >> 6) & 1);
	printf("\td5: %d\n", (received >> 5) & 1);
	printf("\td4: %d\n", (received >> 4) & 1);
	printf("\td3: %d\n", (received >> 3) & 1);
	printf("\td2: %d\n", (received >> 2) & 1);
	printf("\td1: %d\n", (received >> 1) & 1);
	printf("\td0: %d\n", (received >> 0) & 1);
	//printf("\tINFO: %s() end in file: %s at line: %d\n", __func__, __FILE__, __LINE__);
}

void compass_get_id()
{
	//printf("\tINFO: %s() start in file: %s at line: %d\n", __func__, __FILE__, __LINE__);
	uint8_t id1 = register_read(register_identification1.addr);
	uint8_t id2 = register_read(register_identification2.addr);
	uint8_t id3 = register_read(register_identification3.addr);

	printf("compass id: %c%c%c\n", id1, id2, id3);	// treba vratit H43
	printf("\tINFO: %s() end in file: %s at line: %d\n", __func__, __FILE__, __LINE__);
}

int8_t compass_init()
{
	//printf("\tINFO: %s() start in file: %s at line: %d\n", __func__, __FILE__, __LINE__);
	// single measurement
	//i2c_start(2);
	//i2c_sendAddr_tx(2, HMC5883_ADDR_W);
	// 1. Write CRA (00) – send 0x3C 0x00 0x70 (8-average, 15 Hz default or any other rate, normal measurement) 
	register_write(register_conf1.addr, 0x70);

	// 2. Write CRB (01) – send 0x3C 0x01 0xA0 (Gain=5, or any other desired gain) 
	//register_write(register_conf2.addr, 0xA0);	// gain je 101
	register_write(register_conf2.addr, (1 << register_conf2.GN2) | (1 << register_conf2.GN1) | (1 << register_conf2.GN0));	// gain je 111

	// neka se nadje
	register_write(0x03, 0x01);	// single

	/*
	// rucno sve
	i2c_start(2);
	i2c_write(2, HMC5883_ADDR_W);
	i2c_write(2, 0x00);
	i2c_write(2, 0x70);
	i2c_stop(2);

	i2c_start(2);
	i2c_write(2, HMC5883_ADDR_W);
	i2c_write(2, 0x01);
	i2c_write(2, 0xA0);
	i2c_stop(2);

	i2c_start(2);
	i2c_write(2, HMC5883_ADDR_W);
	i2c_write(2, 0x02);
	i2c_write(2, 0x00);	// cont
	i2c_stop(2);
	*/

	//printf("\tINFO: %s() end in file: %s at line: %d\n", __func__, __FILE__, __LINE__);
	return 0;
}

int16_t raw_x, raw_y, raw_z;

void compass_read()
{
	printf("\tINFO: %s() start in file: %s at line: %d\n", __func__, __FILE__, __LINE__);
	/*
	3. For each measurement query: 
	Write Mode (02) – send 0x3C 0x02 0x01 (Single-measurement mode) 
	Wait 6 ms or monitor status register or DRDY hardware interrupt pin 
	Send 0x3D 0x06 (Read all 6 bytes. If gain is changed then this data set is using previous gain) 
	Convert three 16-bit 2’s compliment hex values to decimal values and assign to X, Z, Y, respectively.
	*/

	register_write(register_mode.addr, 0x01);
	delay_ms(7);
	int8_t x1 = register_read(0x03);
	int8_t x2 = register_read(0x04);
	int8_t y1 = register_read(0x05);
	int8_t y2 = register_read(0x06);
	int8_t z1 = register_read(0x07);
	int8_t z2 = register_read(0x08);

	printf("%s(): X: %d %d Y: %d %d Z: %d %d\n", __func__, x1, x2, y1, y2, z1, z2);

	// MSB iz x1 oznacava smjer
	/*
	uint8_t smjer_x = (x1 >> 7) & 1;
	uint8_t smjer_y = (y1 >> 7) & 1;
	uint8_t smjer_z = (z1 >> 7) & 1;
	printf("smjerovi: x: %d    y: %d    z: %d\n", smjer_x, smjer_y, smjer_z);

	// ostatak kad se odsijece predznak
	uint8_t x1a = x1 & 0b1111111;
	printf("x1a: %d\n", x1a);
	*/

	/*
	int16_t x = (x1<<8) + x2;
	int16_t y = (y1<<8) + y2;
	int16_t z = (z1<<8) + z2;
	*/
	//printf("%s(): X: %d Y: %d Z: %d\n", __func__, x, y, z);


	float stupnjevi = 0.0;
	//x = 2047;
	//y = 0;

	/*
	if (y > 0)
	{
		stupnjevi = 90 - atan2(x,y)*180 / 3.14159265;
	}
	else
	{
		stupnjevi = 270 - atan2(x,y)*180 / 3.14159265;
	}
	if (y == 0)
	{
		if (x < 0)
		{
			stupnjevi = 180.0;
		}
		else
		{
			stupnjevi = 0.0;
		}
	}
	*/

	/*
	// kazu da su x i y obrnuti
	if (x > 0)
	{
		stupnjevi = 90 - atan2(y,x)*180 / 3.14159265;
	}
	else
	{
		stupnjevi = 270 - atan2(y,x)*180 / 3.14159265;
	}
	if (x == 0)
	{
		if (y < 0)
		{
			stupnjevi = 180.0;
		}
		else
		{
			stupnjevi = 0.0;
		}
	}
	*/
	printf("\t\t\t\t\t\t stupnjevi: %.2f\n", stupnjevi);
	printf("\tINFO: %s() end in file: %s at line: %d\n", __func__, __FILE__, __LINE__);

}

void compass_main()
{
	i2c_init(2, 100000);

	//compass_init();
	printf("INFO: %s() in file: %s at line: %d\n", __func__, __FILE__, __LINE__);

	register_print(register_conf1.addr);
	register_print(register_conf2.addr);
	//register_print(register_mode.addr);
	//register_print(register_x1.addr);
	//register_print(register_x2.addr);
	//register_print(register_status.addr);

	register_write(0x00, 0x14);	// prodje od 2. put

	compass_get_id();

	//compass_read();

	//printf("kompas vratio: %d\n", reg_read);
}
