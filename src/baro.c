// created 140916
// *************************************** description ********************************************
// BMP180 barometer/therometer driver
#include "baro.h"
// TODO bmp180 -> baro
// TODO ako nema divajsa a pozove se init, nemoj zalockat sve

// privatne globalne varijable
int16_t  BMP180_AC1;
int16_t  BMP180_AC2;
int16_t  BMP180_AC3;
uint16_t BMP180_AC4;
uint16_t BMP180_AC5;
uint16_t BMP180_AC6;
int16_t  BMP180_B1;
int16_t  BMP180_B2;
int16_t  BMP180_MB;
int16_t  BMP180_MC;
int16_t  BMP180_MD;
// tmp
int32_t  BMP180_X1;
int32_t  BMP180_X2;
int32_t  BMP180_X3;
int32_t  BMP180_B3;
uint32_t BMP180_B4;
int32_t  BMP180_B5;
int32_t  BMP180_B6;
uint32_t BMP180_B7;
int32_t  BMP180_T;
int32_t  BMP180_p;

/**************************************************************************************************
*  					bmp180_init(void)
**************************************************************************************************/
void bmp180_init(void)
{
	// INFO moj modul ima regulator na sebi, treba ga ustekat u 5V ili amputirat
	i2c_init(BMP_I2C_PORT, BMP_I2C_SPEED);
	bmp180_calibration();
}

/**************************************************************************************************
*  					bmp180_write(void)
**************************************************************************************************/
int8_t bmp180_write(uint8_t reg, uint8_t data)
{
	i2c_start(BMP_I2C_PORT);
	i2c_sendAddr_tx(BMP_I2C_PORT, BMP_ADDR_W);
	i2c_write(BMP_I2C_PORT, reg);
	i2c_write(BMP_I2C_PORT, data);
	i2c_stop(BMP_I2C_PORT);

	return 0;	// alles gut
}

/**************************************************************************************************
*  					bmp180_read(void)
**************************************************************************************************/
int16_t bmp180_read(uint8_t reg)
{
	uint16_t received = 0;
	uint8_t receivedH = 0;
	uint8_t receivedL = 0;

	i2c_start(BMP_I2C_PORT);
	i2c_sendAddr_tx(BMP_I2C_PORT, BMP_ADDR_W);
	i2c_write(BMP_I2C_PORT, reg);

	i2c_restart(BMP_I2C_PORT);
	i2c_sendAddr_rx(BMP_I2C_PORT, BMP_ADDR_R);
	receivedH = i2c_read_ack(BMP_I2C_PORT);
	receivedL = i2c_read_nack(BMP_I2C_PORT);

	i2c_stop(BMP_I2C_PORT);

	received = (receivedH << 8) | (receivedL & 0xFF);

	return received;
}

/**************************************************************************************************
*  					bmp180_calibration(void)
**************************************************************************************************/
void bmp180_calibration(void)
{
	BMP180_AC1 = bmp180_read(0xAA);
	BMP180_AC2 = bmp180_read(0xAC);
	BMP180_AC3 = bmp180_read(0xAE);
	BMP180_AC4 = bmp180_read(0xB0);
	BMP180_AC5 = bmp180_read(0xB2);
	BMP180_AC6 = bmp180_read(0xB4);
	BMP180_B1  = bmp180_read(0xB6);
	BMP180_B2  = bmp180_read(0xB8);
	BMP180_MB  = bmp180_read(0xBA);
	BMP180_MC  = bmp180_read(0xBC);
	BMP180_MD  = bmp180_read(0xBE);
}

/**************************************************************************************************
*  					bmp180_get_temperature()
**************************************************************************************************/
int16_t bmp180_get_temperature(void)
{
	bmp180_write(0xF4, 0x2E);		// reci mu da naracuna temperaturu
	delay_ms(5);

	int16_t UT = bmp180_read(0xF6);		// pokupi temperaturu
						// dovoljno samo ocitat ADC_H, automatski ce poslat i ADC_L

	// kompenziraj
	BMP180_X1 = ((UT - BMP180_AC6) * BMP180_AC5) >> 15;
	BMP180_X2 = (BMP180_MC << 11) / (BMP180_X1 + BMP180_MD);
	BMP180_B5 = BMP180_X1 + BMP180_X2;
	uint16_t T = ((BMP180_B5 + 8) >> 4);

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
	/*
	OSS		delay ms
	0		5
	1		8
	2		14
	3		26
	*/
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

	BMP180_B6 = BMP180_B5 - 4000;
	BMP180_X1 = (BMP180_B2 * ((BMP180_B6 * BMP180_B6) >> 12)) >> 11;
	BMP180_X2 = (BMP180_AC2 * BMP180_B6) >> 11;
	BMP180_X3 = BMP180_X1 + BMP180_X2;
	BMP180_B3 = (((BMP180_AC1 * 4 + BMP180_X3) << OSS) + 2) / 4;
	BMP180_X1 = (BMP180_AC3 * BMP180_B6) >> 13;
	BMP180_X2 = (BMP180_B1 * (BMP180_B6 * BMP180_B6 >> 12)) >> 16;
	BMP180_X3 = ((BMP180_X1 + BMP180_X2) + 2) / 4;
	BMP180_B4 = (BMP180_AC4 * (uint32_t)(BMP180_X3 + 32768)) >> 15;
	BMP180_B7 = ((uint32_t)(UP - BMP180_B3) * (50000 >> OSS));

	if (BMP180_B7 < 0x80000000)
	{
		BMP180_p = (BMP180_B7 * 2) / BMP180_B4;
	}
	else
	{ 
		BMP180_p = (BMP180_B7 / BMP180_B4) * 2;
	}

	BMP180_X1 = (BMP180_p >> 8) * (BMP180_p >> 8);
	BMP180_X1 = (BMP180_X1 * 3038) >> 16;
	BMP180_X2 = (-7357 * BMP180_p) >> 16;
	BMP180_p = BMP180_p + ((BMP180_X1 + BMP180_X2 + 3791) >> 4);

	return BMP180_p;
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
}
