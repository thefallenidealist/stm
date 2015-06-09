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

// *************************************** private function prototypes ****************************
static int8_t bmp180_write(uint8_t reg, uint8_t data);
static int16_t bmp180_read(uint8_t reg);
static void bmp180_calibration(void);

/**************************************************************************************************
*  					bmp180_init(void)
**************************************************************************************************/
void bmp180_init(void)
{
	// INFO moj modul ima regulator na sebi, treba ga ustekat u 5V ili amputirat
	i2c_init(BMP_I2C_PORT, BMP_I2C_SPEED);
	delay_ms(10);	// start up time
	bmp180_calibration();
}

/**************************************************************************************************
*  					bmp180_write(void)
**************************************************************************************************/
static int8_t bmp180_write(uint8_t reg, uint8_t data)
{
	i2c_start	(BMP_I2C_PORT);
	i2c_sendAddr_tx(BMP_I2C_PORT, BMP_ADDR_W);
	i2c_write	(BMP_I2C_PORT, reg);
	i2c_write	(BMP_I2C_PORT, data);
	i2c_stop	(BMP_I2C_PORT);

	return 0;	// alles gut
}

/**************************************************************************************************
*  					bmp180_read(void)
**************************************************************************************************/
static int16_t bmp180_read(uint8_t reg)
{
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
/**************************************************************************************************
*  					read8(void)
**************************************************************************************************/
static int8_t read8(uint8_t reg)
{
	i2c_start	(BMP_I2C_PORT);
	i2c_sendAddr_tx(BMP_I2C_PORT, BMP_ADDR_W);
	i2c_write	(BMP_I2C_PORT, reg);

	i2c_restart	(BMP_I2C_PORT);
	i2c_sendAddr_rx(BMP_I2C_PORT, BMP_ADDR_R);
	uint8_t received = i2c_read_nack	(BMP_I2C_PORT);

	i2c_stop	(BMP_I2C_PORT);

	return received;
}

/**************************************************************************************************
*  					bmp180_calibration(void)
**************************************************************************************************/
static void bmp180_calibration(void)
{
	AC1 = bmp180_read(0xAA);
	AC2 = bmp180_read(0xAC);
	AC3 = bmp180_read(0xAE);
	AC4 = bmp180_read(0xB0);
	AC5 = bmp180_read(0xB2);
	AC6 = bmp180_read(0xB4);
	B1  = bmp180_read(0xB6);
	B2  = bmp180_read(0xB8);
	MB  = bmp180_read(0xBA);
	MC  = bmp180_read(0xBC);
	MD  = bmp180_read(0xBE);
}

/**************************************************************************************************
*  					bmp180_get_temperature()
**************************************************************************************************/
//int16_t bmp180_get_temperature(void)
int32_t bmp180_get_temperature(void)
{
	bmp180_write(0xF4, 0x2E);		// reci mu da naracuna temperaturu
	delay_ms(5);		// 4.5

	//int16_t UT = bmp180_read(0xF6);		// pokupi temperaturu
	int32_t UT = bmp180_read(0xF6);		// pokupi temperaturu
						// dovoljno samo ocitat ADC_H, automatski ce poslat i ADC_L

	// kompenziraj
	X1 = ((UT - AC6) * AC5) >> 15;
	X2 = (MC << 11) / (X1 + MD);
	B5 = X1 + X2;
	//uint16_t T = ((B5 + 8) >> 4);
	uint32_t T = ((B5 + 8) >> 4);

	return T;
}

/**************************************************************************************************
*  					bmp180_get_pressure()
**************************************************************************************************/
int32_t bmp180_get_pressure(void)
{
	uint8_t OSS = 3;	// oversampling OSS = 0..3
	bmp180_write(0xF4, 0x34 + (OSS << 6));	// pressure
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

	uint16_t UP0 = bmp180_read(0xF6);
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
	uint32_t pressure    = bmp180_get_pressure();

	// altitude = 44330 * ( 1 - (p/p0)^(1/5.255))
	float exponent = 1/5.255;
	float pp0 = ((float)pressure/101325);
	float b = pow(pp0, exponent);
	float altitude = 44330 * (1 - b);

	printf("BMP180:\t\t%d.%d °C\t%u.%u hPa\t%.1f m\n", temperature/10, temperature%10, pressure/100, (pressure%100)/10, altitude);
}

/**************************************************************************************************
*  					bmp180_example()
**************************************************************************************************/
void bmp180_example(void)
{
	bmp180_init();
	bmp180_print();

	/*
	// 160508 ajmo ponovo
	bmp180_calibration();

	uint8_t id = read8(0xD0);	// 0x55
	printf("BMP180 ID: 0x%X\n", id);

	// read uncompensated temperature value
	bmp180_write(0xF4, 0x2E);
	delay_ms(5);

	uint16_t MSB = bmp180_read(0xF6);
	//int8_t LSB = bmp180_read(0xF7);
	uint8_t LSB = 0xFF;

	int32_t UT = MSB << (8 + LSB);
	printf("LSB: %d, MSB: %d \t UT: %d\n", LSB, MSB, UT);


	// calculate true temperature
	//X1 = (UT - AC6) * AC5 / (int32_t)pow(2,15);
	float AC5p = (float)AC5 / (1 << 15);
	printf("AC5p: %.1f\n", AC5p);

	printf("\t\tdebug: UT: %d AC6: %d AC5: %d\n", UT, AC6, AC5);
	float X1a = (UT - AC6) * AC5 / AC5p;
	//X2 = MC * (uint32_t)pow(2, 11) / (X1 + MD);
	X2 = MC * (1 << 1) / (X1 + MD);
	B5 = X1a + X2;
	printf("\t\tdebug, X1: %d X2: %d B5: %d\n", X1a, X2, B5);
	int32_t T = (B5 + 8) / (1 << 4);

	printf("temperature: %d\n", T);
	*/
}


/**************************************************************************************************
*  					bmp180_get_temperature_float()
**************************************************************************************************/
/*
float bmp180_get_temperature_float()
{
	bmp180_write(0xF4, 0x2E);		// reci mu da naracuna temperaturu
	delay_ms(5);

	//int16_t UT = bmp180_read(0xF6);		// pokupi temperaturu
	int32_t UT = bmp180_read(0xF6);		// pokupi temperaturu
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
