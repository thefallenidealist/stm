#include "compass.h"
#include <math.h>
#include "debug.h"

#define address 0x1E //0011110b, I2C 7bit address of HMC5883

#define HMC5883_ADDR_W	0x3C
#define HMC5883_ADDR_R	0x3D


/*
#if DEBUG == 2
	// prvi level, kad se poziva funkcija
	//#define DEBUG1		printf(ANSI_COLOR_YELLOW "calling: %s() in file: %s at line: %d\n" ANSI_COLOR_RESET, __func__, __FILE__, __LINE__);	// i nema nekog smisla
	#define DEBUG1		;

	#define DEBUG_START	printf(ANSI_COLOR_BLUE "INFO: %s() start in file: %s at line: %d\n" ANSI_COLOR_RESET, __func__, __FILE__, __LINE__);
	#define DEBUG_END	printf(ANSI_COLOR_BLUE "INFO: %s() end   in file: %s at line: %d\n" ANSI_COLOR_RESET, __func__, __FILE__, __LINE__);
#else
	#define DEBUG_START	;
	#define DEBUG_END	;
#endif
*/


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

int16_t X, Y, Z;
//uint16_t X, Y, Z;


void compass_get_id()
{
	DEBUG_START

	i2c_start(2);
	i2c_sendAddr_tx(2, HMC5883_ADDR_W);
	i2c_write(2, 10);	// id1 reg
	//i2c_stop(2);

	i2c_restart(2);
	//i2c_start(2);
	i2c_sendAddr_rx(2, HMC5883_ADDR_R);

	int8_t id1 = i2c_read_ack(2);
	int8_t id2 = i2c_read_ack(2);
	int8_t id3 = i2c_read_nack(2);

	i2c_stop(2);

	//printf("\t\t\t%s(): %c%c%c\n", __func__, id1, id2, id3);
	printf("compass id: %c%c%c\n", id1, id2, id3);	// treba vratit H43
	DEBUG_END
}

int8_t compass_init_single()
{
	DEBUG_START ;

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

	i2c_write(2, 0x00);
	i2c_write(2, 0x70);
	//i2c_write(2, 0x01);
	i2c_write(2, 0xA0);
	i2c_write(2, 0x00);	// novo

	i2c_stop(2);

	delay_ms(7);

	DEBUG_END;
	return 0;
}


int8_t compass_init_continuous()
{
	DEBUG_START ;

	/*
	1. Write CRA (00) – send 0x3C 0x00 0x70 (8-average, 15 Hz default, normal measurement) 
	2. Write CRB (01) – send 0x3C 0x01 0xA0 (Gain=5, or any other desired gain) 
	3. Write Mode (02) – send 0x3C 0x02 0x00 (Continuous-measurement mode) 
	4. Wait 6 ms or monitor status register or DRDY hardware interrupt pin 
	5. Loop 
		Send 0x3D 0x06 (Read all 6 bytes. If gain is changed then this data set is using previous gain) 
		Convert three 16-bit 2’s compliment hex values to decimal values and assign to X, Z, Y, respectively. 
		Send 0x3C 0x03 (point to first data register 03) 
		Wait about 67 ms (if 15 Hz rate) or monitor status register or DRDY hardware interrupt pin 
	End_loop 
	*/

	i2c_start(2);
	i2c_sendAddr_tx(2, HMC5883_ADDR_W);
	i2c_write(2, 0x00);
	i2c_write(2, 0x70);	// u nulti registar ide 0x70
	i2c_write(2, 0xA0);	// u prvi 0xA0
	i2c_write(2, 0x00); // u drugi 0x00
	i2c_stop(2);
	//delay_ms(6);
	delay_ms(7);

	DEBUG_END ;
	return 0;
}

void stupnjevi()
{
	DEBUG_START;

	float stupnjevi = 0.0;
	/*
	uint16_t raw_x = X;
	uint16_t raw_y = Y;
	uint16_t raw_z = Z;
	*/

	// Direction (y>0) = 90 - [arcTAN(x/y)]*180/¹
	if (Y > 0)
	//if (Z > 0)
	//if (raw_y > 0)
	{
		//stupnjevi = 90 - atan2(X,Z)*180 / 3.14159265;
		stupnjevi = 90 - atan2(X,Y)*180 / 3.14159265;
		//stupnjevi = 90 - atan2(raw_x, raw_y)*180 / 3.14159265;
	}
	// Direction (y<0) = 270 - [arcTAN(x/y)]*180/¹
	else
	{
		stupnjevi = 270 - atan2(X,Y)*180 / 3.14159265;
		//stupnjevi = 270 - atan2(X,Z)*180 / 3.14159265;
		//stupnjevi = 270 - atan2(raw_x, raw_y)*180 / 3.14159265;
	}
	if (Y == 0)
	//if (Z == 0)
	//if (raw_y == 0)
	{
		// Direction (y=0, x<0) = 180.0
		if (X < 0)
		//if (raw_x < 0)
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
	//printf("raw X: %x\t\t raw Y: %x\t\t raw Z: %x\t\t\t\tstupnjevi: %.2f\n", X, Y, Z, stupnjevi);
	//printf("raw X: %d\t raw Y: %d\t raw Z: %d\t\t\t\n", X, Y, Z);

	DEBUG_END;
}

/*

	float headingDegrees = atan2((double)Y,(double)X)* 180 / 3.14159265 + 180;
	printf("raw X: %d\t raw Y: %d\t raw Z: %d\t\t\t\tstupnjevi: %.2f \t %.2f\n", X, Y, Z, stupnjevi, headingDegrees);
*/

void compass_read_single()
{
	//DEBUG_START;
	/*
	3. For each measurement query: 
		Write Mode (02) – send 0x3C 0x02 0x01 (Single-measurement mode) 
		Wait 6 ms or monitor status register or DRDY hardware interrupt pin 
		Send 0x3D 0x06 (Read all 6 bytes. If gain is changed then this data set is using previous gain) 
		Convert three 16-bit 2’s compliment hex values to decimal values and assign to X, Z, Y, respectively. 
	*/

	i2c_start(2);
	i2c_sendAddr_tx(2, HMC5883_ADDR_W);
	i2c_write(2, 0x02);
	i2c_write(2, 0x01);
	delay_ms(6);
	//i2c_write(2, 0x09);	// x1
	i2c_write(2, 0x03);	// x1		// INFO idemo se zajebavat

	i2c_restart(2);
	i2c_sendAddr_rx(2, HMC5883_ADDR_R);
	
	int8_t x1 = i2c_read_ack(2);
	int8_t x2 = i2c_read_ack(2);
	int8_t z1 = i2c_read_ack(2);
	int8_t z2 = i2c_read_ack(2);
	int8_t y1 = i2c_read_ack(2);
	int8_t y2 = i2c_read_nack(2);
	i2c_stop(2);

	/*
	int16_t x = ((x1 << 8) | x2);
	int16_t y = ((y1 << 8) | y2);
	int16_t z = ((z1 << 8) | z2);
	*/
	// pokusaj, posto su ipak samo 12bitni
	/*
	int16_t x = ((x1 << 4) | x2);
	int16_t y = ((y1 << 4) | y2);
	int16_t z = ((z1 << 4) | z2);
	*/
	int16_t x = x1;
	int16_t y = y1;
	int16_t z = z1;

	// premjestit u globalne varijable
	X = x;
	Y = y;
	Z = z;

	printf("%s(): \tX: %d \tY: %d \tZ: %d \n", __func__, x, y, z);
	//DEBUG_END;
}

void compass_read_continuous()
{
	DEBUG_START;
				// kontinuirani

	/*
	5. Loop 
		Send 0x3D 0x06 (Read all 6 bytes. If gain is changed then this data set is using previous gain) 
		Convert three 16-bit 2’s compliment hex values to decimal values and assign to X, Z, Y, respectively. 
		Send 0x3C 0x03 (point to first data register 03) 
		Wait about 67 ms (if 15 Hz rate) or monitor status register or DRDY hardware interrupt pin 
	End_loop 
	*/
	i2c_start(2);
	i2c_sendAddr_tx(2, HMC5883_ADDR_W);
	//i2c_write(2, 0x03);
	i2c_write(2, 0x06);	// dokumentacija kaze 0x06
	i2c_stop(2);
	//delay_ms(67);
	//i2c_stop(2);

	i2c_start(2);
	i2c_sendAddr_rx(2, HMC5883_ADDR_R);
	/*
	int8_t x1 = i2c_read_ack(2);
	int8_t x2 = i2c_read_ack(2);
	int8_t z1 = i2c_read_ack(2);
	int8_t z2 = i2c_read_ack(2);
	int8_t y1 = i2c_read_ack(2);
	int8_t y2 = i2c_read_nack(2);
	*/
	 int8_t x1 = i2c_read_ack(2);
	uint8_t x2 = i2c_read_ack(2);
	 int8_t z1 = i2c_read_ack(2);
	uint8_t z2 = i2c_read_ack(2);
	 int8_t y1 = i2c_read_ack(2);
	uint8_t y2 = i2c_read_nack(2);
	i2c_stop(2);

	int16_t x = ((x1 << 8) | x2);
	int16_t y = ((y1 << 8) | y2);
	int16_t z = ((z1 << 8) | z2);


	// premjestit u globalne varijable
	X = x;
	Y = y;
	Z = z;

	//printf("%s(): \tX: %d \tY: %d \tZ: %d \n", __func__, x, y, z);
	//printf("%s(): X: %d %d \t Y: %d %d \t Z: %d %d\n", __func__, x1, x2, y1, y2, z1, z2);

	#define         PI                      3.14159265


	/*
	double xd, yd, ret, val;
 
	xd = (double) x;
	//yd = (double) y;
	yd = (double) z;
	val = 180.0 / PI;

	ret = (atan2 (yd,xd) * val)*100;
	*/

	double stupnjevi = 90 - atan2(X,Y)*180 / 3.14159265;


	//double stupnjevi = ((atan2 (yd,xd)) * 180/3.14159);
	//printf("stupnjevi: %f\n", stupnjevi);
	printf("%s(): X: %d %d \t Y: %d %d \t Z: %d %d, stupnjevi: %.2f\n", __func__, x1, x2, y1, y2,
			z1, z2, stupnjevi);


	i2c_start(2);
	i2c_sendAddr_tx(2, HMC5883_ADDR_W);
	i2c_write(2, 0x03);
	i2c_stop(2);
	delay_ms(67);

	DEBUG_END;
}

void compass_main()
{
	DEBUG_START
	//i2c_init(2, 100000);
	i2c_init(2, 200000);

	compass_init_single();
	//compass_init_continuous();

	//register_print(register_conf1.addr);
	//register_print(register_conf2.addr);


	compass_get_id();
	//compass_read_single();

	// compas single read
	i2c_start(2);
	i2c_sendAddr_tx(2, HMC5883_ADDR_W);
	i2c_write(2, 3);	// nastimaj pointer na register 3


	i2c_restart(2);
	i2c_sendAddr_rx(2, HMC5883_ADDR_R);

	int8_t x1 = i2c_read_ack(2);
	int8_t x2 = i2c_read_ack(2);
	int8_t z1 = i2c_read_ack(2);
	int8_t z2 = i2c_read_ack(2);
	int8_t y1 = i2c_read_ack(2);
	int8_t y2 = i2c_read_nack(2);
	i2c_stop(2);

	int16_t x, y, z;
	x = (x1 << 8) + x2;
	y = (y1 << 8) + y2;
	z = (z1 << 8) + z2;


	printf("compass: %d %d \t %d %d \t %d %d \n", x1, x2, y1, y2, z1, z2);
	printf("compass: %d %d %d\n", x, y, z);

#define SCALE 1.3	// default
	float x_scaled, y_scaled, z_scaled;
	x_scaled = (float)x * 1.3;
	y_scaled = (float)y * 1.3;
	z_scaled = (float)z * 1.3;
	printf("compass: %.1f %.1f %1.f\n", x_scaled, y_scaled, z_scaled);


    double angle = atan2((double)y,(double)x) * (180 / 3.14159265) + 180; // angle in degrees
    double angle_scaled = atan2((double)y,(double)x) * (180 / 3.14159265) + 180; // angle in degrees
	printf("compass: %.1f\n", angle);
	printf("compass: %.1f\n", angle_scaled);



	DEBUG_END
}
