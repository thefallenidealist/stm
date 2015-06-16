#include "compass.h"
#include <math.h>

#include "colors_ansi.h"

#define address 0x1E //0011110b, I2C 7bit address of HMC5883

#define HMC5883_ADDR_W	0x3C
#define HMC5883_ADDR_R	0x3D


#if DEBUG == 2
	// prvi level, kad se poziva funkcija
	//#define DEBUG1		printf(ANSI_COLOR_YELLOW "calling: %s() in file: %s at line: %d\n" ANSI_COLOR_RESET, __func__, __FILE__, __LINE__);	// i nema nekog smisla
	#define DEBUG1		;

	#define DEBUG2_START	printf(ANSI_COLOR_BLUE "INFO: %s() start in file: %s at line: %d\n" ANSI_COLOR_RESET, __func__, __FILE__, __LINE__);
	#define DEBUG2_END	printf(ANSI_COLOR_BLUE "INFO: %s() end   in file: %s at line: %d\n" ANSI_COLOR_RESET, __func__, __FILE__, __LINE__);
#else
	#define DEBUG2_START	;
	#define DEBUG2_END	;
#endif


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



































int16_t X, Y, Z;
//uint16_t X, Y, Z;


int8_t register_read(uint8_t reg)
{
	//printf("\tINFO: %s() start in file: %s at line: %d\n", __func__, __FILE__, __LINE__);
	DEBUG2_START
	uint8_t received = 0;

	i2c_write(2, HMC5883_ADDR_W, reg);	// novi
	received = i2c_read(2, HMC5883_ADDR_R);	// novi

	DEBUG2_END
	return received;
}

int8_t register_write(uint8_t reg, uint8_t data)
{
	DEBUG2_START

	i2c_write2(2, HMC5883_ADDR_W, reg, data);

	DEBUG2_END
	return 0;
}

void register_print(uint8_t reg)
{
	DEBUG2_START
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

	DEBUG2_END
}

void compass_get_id()
{
	DEBUG2_START
	uint8_t id1 = register_read(register_identification1.addr);
	uint8_t id2 = register_read(register_identification2.addr);
	uint8_t id3 = register_read(register_identification3.addr);

	printf("compass id: %c%c%c\n", id1, id2, id3);	// treba vratit H43
	DEBUG2_END
}

int8_t compass_init()
{
	DEBUG2_START

	 
	/*
	Below is an example of a (power-on) initialization process for “single-measurement mode”: 
	 
	1. Write CRA (00) – send 0x3C 0x00 0x70 (8-average, 15 Hz default or any other rate, normal measurement) 
	2. Write CRB (01) – send 0x3C 0x01 0xA0 (Gain=5, or any other desired gain) 
	3. For each measurement query: 
		Write Mode (02) – send 0x3C 0x02 0x01 (Single-measurement mode) 
		Wait 6 ms or monitor status register or DRDY hardware interrupt pin 
		Send 0x3D 0x06 (Read all 6 bytes. If gain is changed then this data set is using previous gain) 
		Convert three 16-bit 2’s compliment hex values to decimal values and assign to X, Z, Y, respectively. 
	*/

	i2c_start(2);
	i2c_sendAddr_tx(2, HMC5883_ADDR_W);

	I2C_SendData(I2C2, 0x00);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C2, 0x70);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	i2c_stop(2);

	i2c_start(2);
	i2c_sendAddr_tx(2, HMC5883_ADDR_W);
	I2C_SendData(I2C2, 0x01);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C2, 0xA0);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	i2c_stop(2);

	printf("init kraj\n");

	DEBUG2_END
	return 0;
}

void stupnjevi()
{
	float stupnjevi = 0.0;

	// Direction (y>0) = 90 - [arcTAN(x/y)]*180/¹
	if (Y > 0)
	{
		stupnjevi = 90 - atan2(X,Y)*180 / 3.14159265;
	}
	// Direction (y<0) = 270 - [arcTAN(x/y)]*180/¹
	else
	{
		stupnjevi = 270 - atan2(X,Y)*180 / 3.14159265;
	}
	if (Y == 0)
	{
		// Direction (y=0, x<0) = 180.0
		if (X < 0)
		{
			stupnjevi = 180.0;
		}
		// Direction (y=0, x>0) = 0.0
		else
		{
			stupnjevi = 0.0;
		}
	}

	printf("raw X: %d\t raw Y: %d\t raw Z: %d\t\t\t\tstupnjevi: %.2f\n", X, Y, Z, stupnjevi);
}

/*

	float headingDegrees = atan2((double)Y,(double)X)* 180 / 3.14159265 + 180;
	printf("raw X: %d\t raw Y: %d\t raw Z: %d\t\t\t\tstupnjevi: %.2f \t %.2f\n", X, Y, Z, stupnjevi, headingDegrees);
*/


#define I2C2_SLAVE_ADDRESS7 0x1E //address for magnetometer

void init_single()
{
	// Write CRA (00) – send 0x3C 0x00 0x70 (8-average, 15 Hz default or any other rate, normal measurement) 
	//register_write(0x00, 0x70);
	// Write CRB (01) – send 0x3C 0x01 0xA0 (Gain=5, or any other desired gain) 
	//register_write(0x01, 0xA0);

	/*
	I2C_GenerateSTART(I2C2, ENABLE);
	while(!I2C_GetFlagStatus(I2C2, I2C_FLAG_SB));
	//I2C_Send7bitAddress(I2C2, I2C2_SLAVE_ADDRESS7<<1, I2C_Direction_Transmitter);
	I2C_Send7bitAddress(I2C2, 0x3C, I2C_Direction_Transmitter);	// hardcoded addr XXX

	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	I2C_SendData(I2C2, 0x02);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2C2, 0x00);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_GenerateSTOP(I2C2, ENABLE);
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_STOPF));
	*/

	I2C_GenerateSTART(I2C2, ENABLE);
	while(!I2C_GetFlagStatus(I2C2, I2C_FLAG_SB));
	//I2C_Send7bitAddress(I2C2, I2C2_SLAVE_ADDRESS7<<1, I2C_Direction_Transmitter);
	I2C_Send7bitAddress(I2C2, 0x3C, I2C_Direction_Transmitter);	// hardcoded addr XXX
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C2, 0x00);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2C2, 0x70);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C2, 0x01);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2C2, 0xA0);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTOP(I2C2, ENABLE);
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_STOPF));
}


void Receive(uint8_t Address, uint8_t Register)
{
    u8 XMSB,XLSB,YMSB,YLSB,ZMSB,ZLSB; /* variables to store temporary values in */

    /*left align address*/
    Address = Address<<1;
    /*re-enable ACK bit incase it was disabled last call*/
    I2C_AcknowledgeConfig(I2C2, ENABLE);
    /* Test on BUSY Flag */
    while (I2C_GetFlagStatus(I2C2,I2C_FLAG_BUSY));
    /* Enable the I2C peripheral */
/*======================================================*/
    I2C_GenerateSTART(I2C2, ENABLE);
    /* Test on start flag */
    while (!I2C_GetFlagStatus(I2C2,I2C_FLAG_SB));
    /* Send device address for write */
    //I2C_Send7bitAddress(I2C2, Address, I2C_Direction_Transmitter);
    I2C_Send7bitAddress(I2C2, 0x3D, I2C_Direction_Transmitter);

    /* Test on master Flag */
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    /* Send the device's internal address to write to */
    I2C_SendData(I2C2,Register);
    /* Test on TXE FLag (data sent) */
    while (!I2C_GetFlagStatus(I2C2,I2C_FLAG_TXE));
/*=====================================================*/
      /* Send START condition a second time (Re-Start) */
    I2C_GenerateSTART(I2C2, ENABLE);
    /* Test start flag */
    while (!I2C_GetFlagStatus(I2C2,I2C_FLAG_SB));
    /* Send address for read */
    I2C_Send7bitAddress(I2C2, Address, I2C_Direction_Receiver);
    /* Test Receive mode Flag */
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    /* load in all 6 registers */
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
    XMSB = I2C_ReceiveData(I2C2);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
    XLSB = I2C_ReceiveData(I2C2);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
    YMSB = I2C_ReceiveData(I2C2);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
    YLSB = I2C_ReceiveData(I2C2);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
    ZMSB = I2C_ReceiveData(I2C2);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
    ZLSB = I2C_ReceiveData(I2C2);
    
    /*enable NACK bit */
    I2C_NACKPositionConfig(I2C2, I2C_NACKPosition_Current);
    I2C_AcknowledgeConfig(I2C2, DISABLE);
    
    /* Send STOP Condition */
    I2C_GenerateSTOP(I2C2, ENABLE);
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_STOPF)); // stop bit flag
    
    /*sort into 3 global variables*/
    X = ((XMSB<<8) | XLSB);
    Y = ((YMSB<<8) | YLSB);
    Z = ((ZMSB<<8) | ZLSB);

    //printf("X: %d %d\t Y: %d %d\t Z: %d %d \t\t\t\t\tX: %d\t Y: %d\t Z: %d\n", XMSB, XLSB, YMSB, YLSB, ZMSB, ZLSB, X, Y, Z);
    //printf("compass rx: %d %d %d\n", X, Y, Z);

}

void compass_main()
{
	DEBUG2_START
	i2c_init(2, 100000);

	compass_init();
	//init_single();

	register_print(register_conf1.addr);
	register_print(register_conf2.addr);


	//compass_get_id();
	//compass_read();

	DEBUG2_END
}
