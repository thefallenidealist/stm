// created 140916

// *************************************** description ********************************************
// *************************************** sys includes *******************************************
// *************************************** local includes *****************************************
// *************************************** variables **********************************************
// *************************************** function prototypes ************************************
// *************************************** main ***************************************************


#include "stm32f10x_i2c.h"
#include "stm32f10x_i2c.c"

#define BMP_ADDR_W	0xEE
#define BMP_ADDR_R	0xEF
#define I2C_TIMEOUT_MAX	0xFFFF

uint8_t I2C_read_ack(I2C_TypeDef* I2Cx)
{
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	uint32_t timeout = I2C_TIMEOUT_MAX;
	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) )
	{
		if ((timeout--) == 0)
		       return 20;
	}
	uint8_t data = I2C_ReceiveData(I2Cx);
	return data;
}

uint8_t I2C_read_nack(I2C_TypeDef* I2Cx)
{
  	I2C_AcknowledgeConfig(I2Cx, DISABLE);
	uint32_t timeout = I2C_TIMEOUT_MAX;
	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) )
	{
		if ((timeout--) == 0)
		       return 30;
	}
	uint8_t data = I2C_ReceiveData(I2Cx);
	return data;
}

/**************************************************************************************************
*  					bmp180_init()						  *
**************************************************************************************************/
void bmp180_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	I2C_InitTypeDef I2C_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // Pins 6(I2C1_SCL) and 9(I2C1_SDA)
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;

	GPIO_Init(GPIOB, &GPIO_InitStruct);

	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	//I2C_InitStruct.I2C_OwnAddress1 = 0x00;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStruct.I2C_ClockSpeed = 100000;
	//I2C_InitStruct.I2C_ClockSpeed = 400000;
	I2C_Cmd(I2C1, ENABLE);
	I2C_Init(I2C1,&I2C_InitStruct);
}

/**************************************************************************************************
*  					bmp180_write()						  *
**************************************************************************************************/
uint16_t bmp180_write(uint8_t reg, uint8_t data)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;

	// generiraj start signal
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C1, ENABLE);
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
	{
		if ((timeout--) == 0)
		       return 10;
	}

	// posalji adresu slavea sa kojim treba komunicirat
	I2C_Send7bitAddress(I2C1, BMP_ADDR_W, I2C_Direction_Transmitter);
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		if ((timeout--) == 0)
		       return 11;
	}

	// posalji adresu registra koji treba stimat
	I2C_SendData(I2C1, reg);	// 8b
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if ((timeout--) == 0)
		       return 12;
	}

	// posalji podatke u taj registar
	I2C_SendData(I2C1, data);	// 8b
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if ((timeout--) == 0)
		       return 13;
	}

	// gotovi smo zasad, generiraj stop
	I2C_GenerateSTOP(I2C1, ENABLE);
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	return 0;	// alles gut
}

/**************************************************************************************************
*  					bmp180_read()						  *
**************************************************************************************************/
//uint16_t bmp180_read(uint8_t reg, uint8_t howmany)
uint32_t bmp180_read(uint8_t reg, uint8_t howmany)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;
	uint32_t received = 0;
	uint8_t receivedH = 0;
	uint8_t receivedL = 0;
	uint8_t receivedX = 0;


	// start
	// wait until I2C1 is not busy any more
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C1, ENABLE);
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
	{
		if ((timeout--) == 0)
		       return 10;
	}

	// w addr
	I2C_Send7bitAddress(I2C1, BMP_ADDR_W, I2C_Direction_Transmitter);
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		if ((timeout--) == 0)
		       return 11;
	}

	// w reg
	I2C_SendData(I2C1, reg);	// 8b
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if ((timeout--) == 0)
		       return 12;
	}



	// receiver

	// restart
	I2C_GenerateSTART(I2C1, ENABLE);
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
	{
		if ((timeout--) == 0)
		       return 100;
	}
	// w addr
	I2C_Send7bitAddress(I2C1, BMP_ADDR_R, I2C_Direction_Receiver);
	//I2C_Send7bitAddress(I2C1, 0xEF, I2C_Direction_Receiver);
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
	{
		if ((timeout--) == 0)
		       return 101;
	}


	// ADC high
		// prvo ide ACK/NACK, pa onda citanje sa I2C
	I2C_AcknowledgeConfig(I2C1, ENABLE);	// ACK
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
	{
		if ((timeout--) == 0)
		       return 102;
	}
	receivedH = I2C_ReceiveData(I2C1);

	// ADC low
	I2C_AcknowledgeConfig(I2C1, DISABLE);	// NACK
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
	{
		if ((timeout--) == 0)
		       return 103;
	}
	receivedL = I2C_ReceiveData(I2C1);

	if(howmany == 3)
	{
		// ADC extra
		I2C_AcknowledgeConfig(I2C1, DISABLE);	// NACK
		timeout = I2C_TIMEOUT_MAX;
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
		{
			if ((timeout--) == 0)
			       return 103;
		}
		receivedX = I2C_ReceiveData(I2C1);
	}
	else
		receivedX = 0;

	I2C_GenerateSTOP(I2C1, ENABLE);
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	//received = (receivedH << 8) + receivedL;
	received = (receivedH << 16) + (receivedL << 8) + receivedX;

	return received;
}
























// EEPROM
int16_t	BMP180_AC1;
int16_t	BMP180_AC2;
int16_t	BMP180_AC3;
uint16_t BMP180_AC4;
uint16_t BMP180_AC5;
uint16_t BMP180_AC6;
int16_t	BMP180_B1;
int16_t	BMP180_B2;
int16_t	BMP180_MB;
int16_t	BMP180_MC;
int16_t	BMP180_MD;
// tmp
int32_t X1;
int32_t X2;
int32_t X3;
int32_t B3;
//int32_t B4;
uint32_t B4;
int32_t B5;
int32_t B6;
uint32_t B7;
int32_t T;
int32_t p;

/**************************************************************************************************
*  					bmp180_calibration()					  *
**************************************************************************************************/
void bmp180_calibration()
{
	BMP180_AC1 = bmp180_read(0xAA, 2);
	BMP180_AC2 = bmp180_read(0xAC, 2);
	BMP180_AC3 = bmp180_read(0xAE, 2);
	BMP180_AC4 = bmp180_read(0xB0, 2);
	BMP180_AC5 = bmp180_read(0xB2, 2);
	BMP180_AC6 = bmp180_read(0xB4, 2);
	BMP180_B1 = bmp180_read(0xB6, 2);
	BMP180_B2 = bmp180_read(0xB8, 2);
	BMP180_MB = bmp180_read(0xBA, 2);
	BMP180_MC = bmp180_read(0xBC, 2);
	BMP180_MD = bmp180_read(0xBE, 2);
}

/**************************************************************************************************
*  					bmp180_temperature()					  *
**************************************************************************************************/
uint16_t bmp180_temperature()
{
	bmp180_write(0xF4, 0x2E);		// reci mu da naracuna temperaturu
	delay_ms(5);

	//int16_t UT = bmp180_read(0xF6, 2);		// pokupi temperaturu
	int32_t UT = bmp180_read(0xF6, 2);		// pokupi temperaturu
						// dovoljno samo ocitat ADC_H, automatski ce poslat i ADC_L

	// kompenziraj
	X1 = ((UT - BMP180_AC6) * BMP180_AC5) >> 15;
	X2 = (BMP180_MC << 11) / (X1 + BMP180_MD);
	B5 = X1 + X2;
	//uint16_t T = ((B5 + 8) >> 4);
	uint32_t T = ((B5 + 8) >> 4);

	return T;
}

/**************************************************************************************************
*  					bmp180_pressure()					  *
**************************************************************************************************/
uint16_t bmp180_pressure()
{
	/*
	0x2E	temp		4.5 ms
	0x34	pressure OSS=0	4.5 ms
	0x74	pressure OSS=1	7.5 ms
	0xB4	pressure OSS=2	13.5 ms
	0xF4	pressure OSS=3	25.5 ms
	*/

	bmp180_write(0xF4, 0x74);	// tlak
	delay_ms(8);
	uint16_t OSS = 1;	// oversampling OSS = 0..3
	
	int32_t UP = bmp180_read(0xF6, 3) >> (8-OSS);

	B6 = B5 - 4000;
	X1 = (BMP180_B2 * ((B6 * B6) >> 12)) >> 11;
	X2 = (BMP180_AC2 * B6) >> 11;
	X3 = X1 + X2;
	B3 = (((((int32_t) BMP180_AC1) * 4 + X3) << OSS) + 2) >> 2;
	X1 = (BMP180_AC3 * B6) >> 13;
	X2 = (BMP180_B1 * ((B6 * B6) >> 12)) >> 16;
	X3 = ((X1 + X2) + 2) >> 2;
	B4 = (BMP180_AC4 * (uint32_t)(X3 + 32768)) >> 15;
	B7 = ((uint32_t) (UP - B3) * (50000 >> OSS));
	if (B7 < 0x80000000)
	{
		p = (B7 << 1) / B4;
	}
	else
	{ 
		p = (B7 / B4) << 1;
	}

	X1 = (p >> 8) * (p >> 8);
	X1 = (X1 * 3038) >> 16;
	X2 = (-7357 * p) >> 16;
	p = p + ((X1 + X2 + 3791) >> 4);

	return p;
}
