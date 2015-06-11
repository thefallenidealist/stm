// created 140916
// *************************************** description ********************************************
// BMP180 barometer/therometer driver
#include "baro.h"
// TODO bmp180 -> baro
// TODO ako nema divajsa a pozove se init, nemoj zalockat sve

// privatne globalne varijable
int16_t  AC1;
int16_t  AC2;
int16_t  AC3;
uint16_t AC4;
uint16_t AC5;
uint16_t AC6;
int16_t  B1;
int16_t  B2;
int16_t  MB;
int16_t  MC;
int16_t  MD;
// tmp
int32_t  X1;
int32_t  X2;
int32_t  X3;
int32_t  B3;
uint32_t B4;
int32_t  B5;
int32_t  B6;
uint32_t B7;
int32_t  T;
int32_t  p;

#define BMP180_REG_ID	0xD0
#define BMP180_CMD_START_TEMPERATURE_CONVERSION	0x2E

// *************************************** private function prototypes ****************************
static uint8_t	write		(uint8_t reg, uint8_t data);
static uint16_t read		(uint8_t reg);
static void 	calibration	(void);

/**************************************************************************************************
*  					bmp180_init(void)
**************************************************************************************************/
void bmp180_init(void)
{
	// INFO moj modul ima regulator na sebi, treba ga ustekat u 5V ili amputirat
	i2c_init(BMP_I2C_PORT, BMP_I2C_SPEED);
	delay_ms(10);	// start up time
	calibration();
}

/**************************************************************************************************
*  					write(void)
**************************************************************************************************/
static uint8_t write(uint8_t reg, uint8_t data)
{
	i2c_start	(BMP_I2C_PORT);
	i2c_sendAddr_tx(BMP_I2C_PORT, BMP_ADDR_W);
	i2c_write	(BMP_I2C_PORT, reg);
	i2c_write	(BMP_I2C_PORT, data);
	i2c_stop	(BMP_I2C_PORT);

	return 0;	// alles gut
}

/**************************************************************************************************
*  					read(void)
**************************************************************************************************/
static uint16_t read(uint8_t reg)
{
	// stari, cita i vraca uint sa I2C
	uint16_t received = 0;
	uint8_t receivedH = 0;
	uint8_t receivedL = 0;

	i2c_start	(BMP_I2C_PORT);
	i2c_sendAddr_tx(BMP_I2C_PORT, BMP_ADDR_W);
	i2c_write	(BMP_I2C_PORT, reg);

	i2c_restart	(BMP_I2C_PORT);
	i2c_sendAddr_rx(BMP_I2C_PORT, BMP_ADDR_R);
	receivedH = i2c_read_ack	(BMP_I2C_PORT);
	receivedL = i2c_read_nack	(BMP_I2C_PORT);

	i2c_stop	(BMP_I2C_PORT);

	received = (receivedH << 8) | (receivedL & 0xFF);

	return received;
}

/*
static int16_t read_int(uint8_t reg)
{
	uint16_t received = read(reg);
	int8_t MSB;
	uint8_t LSB;

	MSB = (int8_t)((received>> 8) & 0xFF);	// 16b->8b
	LSB = (received & 0xFF);
	//LSB = (uint8_t)(received & 0xFF);

	return ( (MSB << 8) | LSB);

}

static uint16_t read_uint(uint8_t reg)
{
	uint16_t received = read(reg);
	uint8_t MSB, LSB;

	MSB = (uint8_t)((received >> 8) & 0xFF);	// 16b->8b
	LSB = (uint8_t)(received & 0xFF);

	return ( (MSB << 8) | LSB);
}
*/

/**************************************************************************************************
*  					bmp180_print_id()
**************************************************************************************************/
void bmp180_print_id(void)
{
	i2c_start	(BMP_I2C_PORT);
	i2c_sendAddr_tx(BMP_I2C_PORT, BMP_ADDR_W);
	i2c_write	(BMP_I2C_PORT, BMP180_REG_ID);
	i2c_restart	(BMP_I2C_PORT);
	i2c_sendAddr_rx(BMP_I2C_PORT, BMP_ADDR_R);
	uint8_t id = i2c_read_nack	(BMP_I2C_PORT);
	i2c_stop	(BMP_I2C_PORT);

	printf("%s(): ID: 0x%X, should be 0x55\n", __func__, id);
}

/**************************************************************************************************
*  					calibration(void)
**************************************************************************************************/
static void calibration(void)
{
	AC1 = read(0xAA);
	AC2 = read(0xAC);
	AC3 = read(0xAE);
	AC4 = read(0xB0);
	AC5 = read(0xB2);
	AC6 = read(0xB4);
	B1  = read(0xB6);
	B2  = read(0xB8);
	MB  = read(0xBA);
	MC  = read(0xBC);
	MD  = read(0xBE);
	/*
	AC1 = read_int(0xAA);
	AC2 = read_int(0xAC);
	AC3 = read_int(0xAE);
	AC4 = read_uint(0xB0);
	AC5 = read_uint(0xB2);
	AC6 = read_uint(0xB4);
	B1  = read_int(0xB6);
	B2  = read_int(0xB8);
	MB  = read_int(0xBA);
	MC  = read_int(0xBC);
	MD  = read_int(0xBE);
	*/
}

/**************************************************************************************************
*  					bmp180_get_temperature()
**************************************************************************************************/
int16_t bmp180_get_temperature(void)
{
	write(0xF4, BMP180_CMD_START_TEMPERATURE_CONVERSION);
	delay_ms(5);		// 4.5

	//int16_t UT = read(0xF6);		// pokupi temperaturu
	uint16_t UT = read(0xF6);		// pokupi temperaturu				// jebo majku, bio je trik da ovo bude uint16_t, a ne int16_t
						// dovoljno samo ocitat ADC_H, automatski ce poslat i ADC_L

	//float fUT = (float)UT;
	double fUT = (double)UT;
	//float X1, X2, B5, T;
	double X1, X2, B5, T;

	/*
	// test onog iz datasheeta
	fUT = 27898;
	AC6 = 23153;
	AC5 = 32757;
	MC  = -8711;
	MD  = 2868;
	// treba ispast 150 (za 15.0°C, ispadne 150.5)
	*/


	// X1 = (UT - AC6) * AC5 / 2^15
	//X1 = (fUT - (float)AC6) * (float) AC5 / powf(2,15);
	X1 = (fUT - (double)AC6) * (double) AC5 / powf(2,15);

	// X2 = MC * 2^11 / (X1 + MD)
	//X2 = (float)MC * powf(2,11) / (X1 + (float)MD);
	X2 = (double)MC * pow(2,11) / (X1 + (double)MD);

	// B5 = X1 + X2;
	B5 = X1 + X2;

	// T = (B5 + 8) / 2^4
	//T = (B5 + 8.0) / powf(2,4);
	T = (B5 + 8.0) / pow(2,4);

	/*
	// valja
	UT:	 32534
	X1:  -39543.2   [6957.4]
	X2:  611.2      [-2415.7]
	B5:  -38932.1   [4541.7]
	T:   -2432.8    [284.4]

	// ne valja:
	UT: -32651
	X1:  7010.1     [6957.4]
	X2:  -2402.2    [-2415.7]
	B5:  4607.9     [4541.7]
	T:   288.5      [284.4]
	*/


	//printf("sizeof \n\tint32_t: %lu \n\tfloat: %lu\n\tdouble: %lu\n", sizeof(int32_t)*8, sizeof(float)*8, sizeof(double)*8);


	/*
	printf("\t\t\t\t UT: %d %.1f\n", UT, fUT);

	// u zagradi stvarne vrijednosti sa mojeg barometra, T = 28.4°C
	printf("AC6: %d \t[22769]\n", AC6);
	printf("AC5: %d \t[23349]\n", AC5);
	printf("MC:  %d \t[-11075]\n", MC);
	printf("\n");
	printf("X1:  %.1f \t[6957.4]\n", X1);
	printf("X2:  %.1f \t[-2415.7]\n", X2);
	printf("B5:  %.1f \t[4541.7]\n", B5);
	printf("T:   %.1f \t[284.4]\n", T);
	printf("\n");
	*/

	printf("T: float: %.1f \t int16_t: %d\n", T, (int16_t)T);




	return 0;
}

/**************************************************************************************************
*  					bmp180_get_pressure()
**************************************************************************************************/
int32_t bmp180_get_pressure(void)
{
	uint8_t OSS = 3;	// oversampling OSS = 0..3
	write(0xF4, 0x34 + (OSS << 6));	// pressure
						// shiftanje jer OSS ide u b7, b6 u registru
	// KK-u bilo dosadno pa rece:
	if (OSS > 3)
	{
		printf("%s(): Wrong OSS, exiting\n", __func__);
		return 0xFF;
	}
	else
	{
		delay_ms(5 + 3 * ((1 << OSS) - 1));
	}

	uint16_t UP0 = read(0xF6);
	// simulacija XLSB bita
	uint32_t UP = (UP0 << 8) >> (8 - OSS);

	B6 = B5 - 4000;
	X1 = (B2 * ((B6 * B6) >> 12)) >> 11;
	X2 = (AC2 * B6) >> 11;
	X3 = X1 + X2;
	B3 = (((AC1 * 4 + X3) << OSS) + 2) / 4;
	X1 = (AC3 * B6) >> 13;
	X2 = (B1 * (B6 * B6 >> 12)) >> 16;
	X3 = ((X1 + X2) + 2) / 4;
	B4 = (AC4 * (uint32_t)(X3 + 32768)) >> 15;
	B7 = ((uint32_t)(UP - B3) * (50000 >> OSS));

	if (B7 < 0x80000000)
	{
		p = (B7 * 2) / B4;
	}
	else
	{ 
		p = (B7 / B4) * 2;
	}

	X1 = (p >> 8) * (p >> 8);
	X1 = (X1 * 3038) >> 16;
	X2 = (-7357 * p) >> 16;
	p = p + ((X1 + X2 + 3791) >> 4);

	return p;
}

/**************************************************************************************************
*  					bmp180_print()
**************************************************************************************************/
void bmp180_print(void)
{		
	uint16_t temperature = bmp180_get_temperature();
	/*
	uint32_t pressure    = bmp180_get_pressure();

	// calculate altitude		TODO spesl funkcija
	// altitude = 44330 * ( 1 - (p/p0)^(1/5.255))
	float exponent = 1/5.255;
	float pp0 = ((float)pressure/101325);
	float b = pow(pp0, exponent);
	float altitude = 44330 * (1 - b);

	printf("BMP180:\t\t%d.%d °C\t%u.%u hPa\t%.1f m\n", temperature/10, temperature%10, pressure/100, (pressure%100)/10, altitude);
	*/
	printf("BMP180:\t\t%d.%d °C\n", temperature/10, temperature%10);
}

/**************************************************************************************************
*  					bmp180_example()
**************************************************************************************************/
void bmp180_example(void)
{
	bmp180_init();
	bmp180_print_id();
	bmp180_print();
}


/**************************************************************************************************
*  					bmp180_get_temperature_float()
**************************************************************************************************/
/*
float bmp180_get_temperature_float()
{
	write(0xF4, 0x2E);		// reci mu da naracuna temperaturu
	delay_ms(5);

	//int16_t UT = read(0xF6);		// pokupi temperaturu
	int32_t UT = read(0xF6);		// pokupi temperaturu
						// dovoljno samo ocitat ADC_H, automatski ce poslat i ADC_L

	// kompenziraj
	X1 = ((UT - AC6) * AC5) >> 15;
	X2 = (MC << 11) / (X1 + MD);
	B5 = X1 + X2;
	//uint16_t T = ((B5 + 8) >> 4);
	uint32_t T = ((B5 + 8) >> 4);

	float temperature = (float)T/10.0f;
	return temperature;
}
*/
