// created 140916
// *************************************** description ********************************************
// BMP180 barometer/therometer driver
#include "baro.h"
// TODO bmp180 -> baro
// TODO ako nema divajsa a pozove se init, nemoj zalockat sve

// privatne globalne varijable
static int16_t  AC1;
static int16_t  AC2;
static int16_t  AC3;
static uint16_t AC4;
static uint16_t AC5;
static uint16_t AC6;
static int16_t  B1;
static int16_t  B2;
static int16_t  MB;
static int16_t  MC;
static int16_t  MD;
// tmp
static int32_t  X1;
static int32_t  X2;
static int32_t  X3;
static int32_t  B3;
static uint32_t B4;
static int32_t  B5;
static int32_t  B6;
static uint32_t B7;

#define BMP_ADDR_R	0xEF
#define BMP_ADDR_W	0xEE

#define REG_XLSB	0xF8	// b7..3, not used in my driver
#define REG_LSB		0xF7
#define REG_MSB		0xF6
#define REG_CONTROL	0xF4
#define REG_RESET	0xE0
#define REG_ID		0xD0

#define CMD_GET_TEMPERATURE		0x2E
#define CMD_GET_PRESSURE_OSS0	0x34
#define CMD_GET_PRESSURE_OSS1	0x74
#define CMD_GET_PRESSURE_OSS2	0xB4
#define CMD_GET_PRESSURE_OSS3	0xF4

// *************************************** private function prototypes ****************************
static uint8_t	write		(uint8_t reg, uint8_t data);
static uint16_t read		(uint8_t reg);
static void 	calibration	(void);
static uint8_t	get_id		(void);

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
*  					get_id()
**************************************************************************************************/
static uint8_t get_id(void)
{
	uint8_t id = 0;
	i2c_start	(BMP_I2C_PORT);
	i2c_sendAddr_tx(BMP_I2C_PORT, BMP_ADDR_W);
	i2c_write	(BMP_I2C_PORT, REG_ID);
	i2c_restart	(BMP_I2C_PORT);
	i2c_sendAddr_rx(BMP_I2C_PORT, BMP_ADDR_R);
	id = i2c_read_nack	(BMP_I2C_PORT);
	i2c_stop	(BMP_I2C_PORT);

	return id;
}

/**************************************************************************************************
*  					bmp180_print_id()
**************************************************************************************************/
void bmp180_print_id(void)
{
	const uint8_t EXPECTED_ID = 0x55;
	uint8_t id = get_id();

	if (id == EXPECTED_ID)
	{
		printf("%s(): ID: 0x%X\n", id);
	}
	else
	{
		printf("%s(): ID: 0x%X, expected %d\n", __func__, id, EXPECTED_ID);
	}
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
}

/**************************************************************************************************
*  					bmp180_get_temperature()
**************************************************************************************************/
float bmp180_get_temperature(void)
{
	write(REG_CONTROL, CMD_GET_TEMPERATURE);
	delay_ms(5);		// 4.5

	// INFO uint16_t UT inace nece radit za temperature iznad 29.6°C (jer raw UT predje preko 32k)
	uint16_t UT = read(REG_MSB);

	float fUT = (float)UT;
	float X1, X2, B5, T;

	// kompenzacija
	X1 = (fUT - (float)AC6) * (float) AC5 / powf(2,15);
	X2 = (float)MC * powf(2,11) / (X1 + (float)MD);
	B5 = X1 + X2;
	T = (B5 + 8.0) / powf(2,4);
	T /= 10;	// jer mjeri u 0.1°C

	return T;
}

/**************************************************************************************************
*  					bmp180_get_pressure()
**************************************************************************************************/
float bmp180_get_pressure(barometer_conversion_t mjerilo)	// XXX prevest
{
	// Average sea-level pressure is 101.325 kPa (1013.25 hPa or mbar) or 29.92 inches (inHg) or 760 millimetres of mercury (mmHg).

	int32_t p = 0;
	const uint8_t OSS = 1;	// oversampling OSS = 0..3		// XXX ne radi kad je OSS 0
	uint8_t cmd_pressure = 0;

	switch (OSS)
	{
		case 0:
			cmd_pressure = CMD_GET_PRESSURE_OSS0;
			break;
		case 1:
			cmd_pressure = CMD_GET_PRESSURE_OSS1;
			break;
		case 2:
			cmd_pressure = CMD_GET_PRESSURE_OSS2;
			break;
		case 3:
			cmd_pressure = CMD_GET_PRESSURE_OSS3;
			break;
		default:
			printf("%s(): Wrong OSS, exiting now.\n", __func__);
			return 0.0;
	}

	write(REG_CONTROL, 0xF4 + (OSS << 6));	// pressure
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
		//printf("delay_ms: %d\n", (5 + 3 * ((1 << OSS) - 1)));
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
	p = p + ((X1 + X2 + 3791) >> 4);	// pressure in Pa

	float pressure = p;

	// XXX prevest
	switch (mjerilo)
	{
		case Pa:
			break;
		case hPa:
			pressure /= 100;
			break;
		case kPa:
			pressure /= 1000;
			break;
		default:	// kPa
			pressure /= 1000;
			break;
	}

	return pressure;
}

/**************************************************************************************************
*  					bmp180_get_altitude()
**************************************************************************************************/
float bmp180_get_altitude(void)
{
	// absolute altitude
	const float p0 = 1013.25; 		// pressure in hPa at sea level
		  float p  = bmp180_get_pressure(hPa);

	float altitude = 44330 * (1 - (powf((p/p0), (1/5.255))));

	return altitude;
	// dobro radi formula, iako Zupanja ispadne 700 m visine (92.8 kPa)
}

/**************************************************************************************************
*  					bmp180_print()
**************************************************************************************************/
void bmp180_print(void)
{		
	float temperature	= bmp180_get_temperature();
	float pressure		= bmp180_get_pressure(kPa);
	float altitude		= bmp180_get_altitude();

	printf("BMP180:\t\t%.1f °C \t %.1f kPa \t %.1f m\n", temperature, pressure, altitude);
}

/**************************************************************************************************
*  					bmp180_example()
**************************************************************************************************/
void bmp180_example(void)
{
	bmp180_init();
	//bmp180_print_id();	// communication test
	bmp180_print();
}
