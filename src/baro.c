// created 140916
// *************************************** description ********************************************
// BMP180 barometer/therometer driver
// *************************************** sys includes *******************************************
#include "baro.h"
// *************************************** local includes *****************************************
// *************************************** defines ************************************************
// *************************************** function prototypes ************************************
// *************************************** variables **********************************************
// EEPROM
// TODO bmp180 -> baro
// TODO ako nema divajsa a pozove se init, nemoj zalockat sve
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
*  					bmp180_init(void)						  *
**************************************************************************************************/
void bmp180_init(void)
{
	//i2c_init(100000);	// TODO isprobat
	/*
	// vise-manje isti init kao za eeprom
	GPIO_InitTypeDef GPIO_InitStruct;
	I2C_InitTypeDef I2C_InitStruct;

	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);	// F1
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);	// F4

	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// F1
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	// F4

	// F4
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_I2C2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_I2C2);

	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // SCL, SDA
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; // SCL, SDA		// F4
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;	// F1
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;	// F4
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;	// F4
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;	// TODO

	GPIO_Init(GPIOB, &GPIO_InitStruct);

	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	//I2C_InitStruct.I2C_OwnAddress1 = 0x00;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStruct.I2C_ClockSpeed = 100000;
	//I2C_InitStruct.I2C_ClockSpeed = 400000;
	//I2C_Cmd(I2C1, ENABLE);		// F1
	//I2C_Init(I2C1,&I2C_InitStruct);	// F1
	I2C_Cmd(I2C2, ENABLE);
	I2C_Init(I2C2,&I2C_InitStruct);
	*/
}

/**************************************************************************************************
*  					bmp180_write(void)						  *
**************************************************************************************************/
uint16_t bmp180_write(uint8_t reg, uint8_t data)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;

	// generiraj start signal
	while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C1, ENABLE);
	timeout = I2C_TIMEOUT_MAX;
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
	{
		if ((timeout--) == 0)
		       return 10;
	}

	// posalji adresu slavea sa kojim treba komunicirat
	I2C_Send7bitAddress(I2C1, BMP_ADDR_W, I2C_Direction_Transmitter);
	timeout = I2C_TIMEOUT_MAX;
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		if ((timeout--) == 0)
		       return 11;
	}

	// posalji adresu registra koji treba stimat
	I2C_SendData(I2C1, reg);	// 8b
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if ((timeout--) == 0)
		       return 12;
	}

	// posalji podatke u taj registar
	I2C_SendData(I2C1, data);	// 8b
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if ((timeout--) == 0)
		       return 13;
	}

	// gotovi smo zasad, generiraj stop
	I2C_GenerateSTOP(I2C1, ENABLE);
	while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	return 0;	// alles gut
}

/**************************************************************************************************
*  					bmp180_read(void)						  *
**************************************************************************************************/
//uint16_t bmp180_read(uint8_t reg)
int16_t bmp180_read(uint8_t reg)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;
	uint16_t received = 0;
	uint8_t receivedH = 0;
	uint8_t receivedL = 0;


	// start
	// wait until I2C1 is not busy any more
	while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C1, ENABLE);
	timeout = I2C_TIMEOUT_MAX;
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
	{
		if ((timeout--) == 0)
		       return 10;
	}

	// w addr
	I2C_Send7bitAddress(I2C1, BMP_ADDR_W, I2C_Direction_Transmitter);
	timeout = I2C_TIMEOUT_MAX;
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		if ((timeout--) == 0)
		       return 11;
	}

	// w reg
	I2C_SendData(I2C1, reg);	// 8b
	timeout = I2C_TIMEOUT_MAX;
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if ((timeout--) == 0)
		       return 12;
	}

	// receiver
	// restart
	I2C_GenerateSTART(I2C1, ENABLE);
	timeout = I2C_TIMEOUT_MAX;
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
	{
		if ((timeout--) == 0)
		       return 100;
	}
	// w addr
	I2C_Send7bitAddress(I2C1, BMP_ADDR_R, I2C_Direction_Receiver);
	timeout = I2C_TIMEOUT_MAX;
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
	{
		if ((timeout--) == 0)
		       return 101;
	}

	// ADC high
		// prvo ide ACK/NACK, pa onda citanje sa I2C
	I2C_AcknowledgeConfig(I2C1, ENABLE);	// ACK
	timeout = I2C_TIMEOUT_MAX;
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
	{
		if ((timeout--) == 0)
		       return 102;
	}
	receivedH = I2C_ReceiveData(I2C1);

	// ADC low
	I2C_AcknowledgeConfig(I2C1, DISABLE);	// NACK
	timeout = I2C_TIMEOUT_MAX;
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
	{
		if ((timeout--) == 0)
		       return 103;
	}
	receivedL = I2C_ReceiveData(I2C1);

	I2C_GenerateSTOP(I2C1, ENABLE);
	while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	received = (receivedH << 8) + receivedL;

	return received;
}

/**************************************************************************************************
*  					bmp180_calibration(void)					  *
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
	printf("%d\n", BMP180_AC1);
	printf("%d\n", BMP180_AC2);
	printf("%d\n", BMP180_AC3);
	printf("%d\n", BMP180_AC4);
	printf("%d\n", BMP180_AC5);
	printf("%d\n", BMP180_AC6);
	printf("%d\n", BMP180_B1);
	printf("%d\n", BMP180_B2);
	printf("%d\n", BMP180_MB);
	printf("%d\n", BMP180_MC);
	printf("%d\n", BMP180_MD);
	*/
}

/**************************************************************************************************
*  					bmp180_temperature(void)					  *
**************************************************************************************************/
uint16_t bmp180_temperature(void)
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
*  					bmp180_pressure(void)					  *
**************************************************************************************************/
uint32_t bmp180_pressure(void)
{
	uint8_t OSS = 3;	// oversampling OSS = 0..3
	bmp180_write(0xF4, 0x34 + (OSS << 6));	// pressure
						// shiftanje jer OSS ide u b7, b6 u registru
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
			break;
	}
	
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

void bmp180_print(void)
{		
	uint16_t temperature = bmp180_temperature();
	uint32_t pressure    = bmp180_pressure();

	// altitude = 44330 * ( 1 - (p/p0)^(1/5.255))
	float exponent = 1/5.255;
	float pp0 = ((float)pressure/101325);
	float b = pow(pp0, exponent);
	float altitude = 44330 * (1 - b);

	printf("BMP180:\t\t%d.%d °C\t%u.%u hPa\t%.1f m\n", temperature/10, temperature%10, pressure/100, (pressure%100)/10, altitude);
}

void bmp180_example(void)
{
	bmp180_init();
	bmp180_calibration();

	bmp180_print();
}
