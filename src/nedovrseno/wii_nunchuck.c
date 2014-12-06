// 140918
// *************************************** description ********************************************
// *************************************** sys includes *******************************************
#include "stm32f10x_i2c.h"
#include "stm32f10x_i2c.c"
// *************************************** local includes *****************************************
// *************************************** defines ************************************************
#define WII_ADDR_W	0xA4
#define WII_ADDR_R	0xA5
#define I2C_TIMEOUT_MAX	0xFFFF
// *************************************** variables **********************************************
// *************************************** function prototypes ************************************
void wii_init();
uint8_t wii_write(uint8_t reg, uint8_t data);
uint64_t wii_read();
uint64_t wii_read0();
uint8_t wii_write0(uint8_t reg);
// *************************************** main ***************************************************


/**************************************************************************************************
*  					delay_init()						  *
**************************************************************************************************/
void wii_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	I2C_InitTypeDef I2C_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // SCL, SDA
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

	// pravi Wii init
	// http://www.wiibrew.org/wiki/Wiimote/Extension_Controllers/Nunchuck
	// Write 0xA4, 0xF0, 0x55 (address, register, data) 
	uint8_t status;
	//status = wii_write(0xF0, 0x55);
	status = wii_write(0x40, 0x00);
	printf("wii_init() w1 status: %d\n", status);
	delay_ms(1);
	// Write 0xA4, 0xFB, 0x00 (address, register, data)
	//status = wii_write(0xFB, 0x00);
	status = wii_write0(0x00);
	printf("wii_init() w2 status: %d\n", status);
}

uint8_t wii_write0(uint8_t reg)
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
	I2C_Send7bitAddress(I2C1, WII_ADDR_W, I2C_Direction_Transmitter);
	//I2C_Send7bitAddress(I2C1, 0x52, I2C_Direction_Transmitter);
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

	// gotovi smo zasad, generiraj stop
	I2C_GenerateSTOP(I2C1, ENABLE);
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	return 0;
}

uint8_t wii_write(uint8_t reg, uint8_t data)
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
	I2C_Send7bitAddress(I2C1, WII_ADDR_W, I2C_Direction_Transmitter);
	//I2C_Send7bitAddress(I2C1, 0x52, I2C_Direction_Transmitter);
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

	return 0;
}

uint64_t wii_read()
{
	/*
	nunchuck
	6 bytes		
	1. joystick JX
	2. joystick JY
	3. accelerometer AX[9..2]
	4. accelerometer AY[9..2]
	5. accelerometer AZ[9..2]
	    b 7..6     5..4     3..2   1  0
	6. AZ[1..0] AY[1..0] AX[1..0] BC BZ

	A* su 10b

	*/
	uint8_t JX = 0;
	uint8_t JY = 0;
	uint16_t AX = 0;
	uint16_t AY = 0;
	uint16_t AZ = 0;

	// read:
	// Write 0xA4, 0x00
	// Read 6 bytes from 0xA4 

	uint64_t data = 0;
	return data;
}

uint64_t wii_read0()
{
	uint32_t timeout = I2C_TIMEOUT_MAX;
	uint8_t received0 = 0;
	uint8_t received1 = 0;
	uint8_t received2 = 0;
	uint8_t received3 = 0;
	uint8_t received4 = 0;
	uint8_t received5 = 0;

	// start
	/*
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
	I2C_Send7bitAddress(I2C1, WII_ADDR_W, I2C_Direction_Transmitter);
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		if ((timeout--) == 0)
		       return 11;
	}
		// w reg
	I2C_SendData(I2C1, 0x00);	// 8b
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if ((timeout--) == 0)
		       return 12;
	}
	*/


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
	I2C_Send7bitAddress(I2C1, WII_ADDR_R, I2C_Direction_Receiver);
	//I2C_Send7bitAddress(I2C1, WII_ADDR_W, I2C_Direction_Receiver);
	//I2C_Send7bitAddress(I2C1, 0x52, I2C_Direction_Receiver);
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
	{
		if ((timeout--) == 0)
		       return 101;
	}




	delay_ms(20);


	// prvo ide ACK/NACK, pa onda citanje sa I2C
	//I2C_AcknowledgeConfig(I2C1, ENABLE);	// ACK
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
	{
		if ((timeout--) == 0)
		       return 102;
	}
	received0 = I2C_ReceiveData(I2C1);					// 0

	I2C_AcknowledgeConfig(I2C1, ENABLE);	// ACK
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
	{
		if ((timeout--) == 0)
		       return 103;
	}
	received1 = I2C_ReceiveData(I2C1);					// 1

	I2C_AcknowledgeConfig(I2C1, ENABLE);	// ACK
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
	{
		if ((timeout--) == 0)
		       return 104;
	}
	received2 = I2C_ReceiveData(I2C1);					// 2

	I2C_AcknowledgeConfig(I2C1, ENABLE);	// ACK
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
	{
		if ((timeout--) == 0)
		       return 105;
	}
	received3 = I2C_ReceiveData(I2C1);					// 3

	I2C_AcknowledgeConfig(I2C1, ENABLE);	// ACK
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
	{
		if ((timeout--) == 0)
		       return 106;
	}
	received4 = I2C_ReceiveData(I2C1);					// 4

	I2C_AcknowledgeConfig(I2C1, ENABLE);	// ACK
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
	{
		if ((timeout--) == 0)
		       return 107;
	}
	received5 = I2C_ReceiveData(I2C1);					// 5


	I2C_GenerateSTOP(I2C1, ENABLE);
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	//uint64_t received = (received0 << 40) + (received1 << 32) + (received2 << 24) + (received3 << 16) + (received4 << 8) + received5;
	printf("received0: %d\n", received0);
	printf("received1: %d\n", received1);
	printf("received2: %d\n", received2);
	printf("received3: %d\n", received3);
	printf("received4: %d\n", received4);
	printf("received5: %d\n", received5);

	//return received;
	return 0;


}
