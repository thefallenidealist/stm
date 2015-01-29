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
	i2c_init(2, 100000);
}

/**************************************************************************************************
*  					bmp180_write(void)
**************************************************************************************************/
int8_t bmp180_write(uint8_t reg, uint8_t data)
{
	i2c_start(2);

	i2c_sendAddr_tx(2, BMP_ADDR_W);
	i2c_write(2, reg);
	i2c_write(2, data);

	i2c_stop(2);

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

	i2c_start(2);
	i2c_sendAddr_tx(2, BMP_ADDR_W);
	i2c_write(2, reg);

	i2c_restart(2);
	i2c_sendAddr_rx(2, BMP_ADDR_R);
	receivedH = i2c_read_ack(2);
	receivedL = i2c_read_nack(2);

	i2c_stop(2);

	received = (receivedH << 8) | (receivedL & 0xFF);

	//printf("DEBUG %s(): H: 0x%X %d \t L: 0x%X %d \t kombinirano: 0x%X %d\n", __func__, receivedH, receivedH, receivedL, receivedL, received, received);

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
	BMP180_B1 = bmp180_read(0xB6);
	BMP180_B2 = bmp180_read(0xB8);
	BMP180_MB = bmp180_read(0xBA);
	BMP180_MC = bmp180_read(0xBC);
	BMP180_MD = bmp180_read(0xBE);

	/*
	printf("AC1 %d\n", BMP180_AC1);
	printf("AC2 %d\n", BMP180_AC2);
	printf("AC3 %d\n", BMP180_AC3);
	printf("AC4 %d\n", BMP180_AC4);
	printf("AC5 %d\n", BMP180_AC5);
	printf("AC6 %d\n", BMP180_AC6);
	printf("B1 %d\n", BMP180_B1);
	printf("B2 %d\n", BMP180_B2);
	printf("MB %d\n", BMP180_MB);
	printf("MC %d\n", BMP180_MC);
	printf("MD %d\n", BMP180_MD);
	*/
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
	switch (OSS)
	{
		case 0:
			delay_ms(5);
			break;
		case 1:
			delay_ms(8);
			break;
		case 2:
			delay_ms(14);
			break;
		case 3:
			delay_ms(26);
			break;
		default:
			printf("%s(): Wrong OSS\n", __func__);
			break;
	}
	*/

	// KK-u bilo dosadno pa rece:
	if (OSS > 3)
	{
		printf("%s(): Wrong OSS\n", __func__);
	}
	else
	{
		//delay_ms(5 + 3 * (pow(2,OSS) - 1));
		delay_ms(5 + 3 * ((1 << OSS) - 1));
	}

	/*
	const uint8_t OSS_VAL[] = {5, 8, 14, 21};
	if (OSS < 4)
	{
		delay_ms(OSS_VAL[OSS]);
	}
	else
	{
			printf("%s(): Wrong OSS\n", __func__);
	}
	*/
	
	// UP = (MSB << 16 + LSB << 8 + XLSB) >> (8-OSS);
	//int16_t UP = bmp180_read(0xF6) >> (8-OSS);
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
	printf("%s() start\n", __func__);
	bmp180_init();
	bmp180_calibration();

	bmp180_print();
	printf("%s() end\n", __func__);
}
