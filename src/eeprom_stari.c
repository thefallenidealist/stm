// created 140918
// *************************************** description ********************************************
// Atmel 24C256 I2C EEPROM driver
// *************************************** sys includes *******************************************
#include "eeprom_stari.h"
// *************************************** local includes *****************************************
// *************************************** defines ************************************************
// pretpostavka da su A1 i A0 = 0
#define EEPROM_ADDR_W	0xA0
#define EEPROM_ADDR_R	0xA1
#define I2C_TIMEOUT_MAX	0xFFFF
// *************************************** variables **********************************************
// *************************************** function prototypes ************************************
void eeprom_init();
uint8_t eeprom_write(uint16_t addr, uint8_t data);
uint8_t eeprom_read(uint16_t addr);
void eeprom_example();

/**************************************************************************************************
*  					eeprom_init()						  *
**************************************************************************************************/
void eeprom_init()
{
	// kopirano iz i2c.c i2c_init()

	GPIO_InitTypeDef GPIO_InitStruct;
	I2C_InitTypeDef I2C_InitStruct;

	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);	// F1
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
	//I2C_InitStruct.I2C_ClockSpeed = i2c_speed;
	I2C_InitStruct.I2C_ClockSpeed = 100000;
	//I2C_InitStruct.I2C_ClockSpeed = 400000;
	//I2C_Cmd(I2C2, ENABLE);		// F1
	//I2C_Init(I2C2,&I2C_InitStruct);	// F1
	I2C_Cmd(I2C2, ENABLE);
	I2C_Init(I2C2,&I2C_InitStruct);
	printf("init gotov\n");
}

/**************************************************************************************************
*  					eeprom_write()						  *
**************************************************************************************************/
	/*
uint8_t eeprom_write(uint16_t addr, uint8_t data)
{
	printf("eeprom write start\n");
	// zapisuje 8b na addr
	// TODO ujedinit bmp180_write i ovo, razlike opisane dolje
	uint32_t timeout = I2C_TIMEOUT_MAX;

	uint8_t addrH = addr >> 8;
	uint8_t addrL = addr * 0x00FF;

	// generiraj start signal
	while (I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C2, ENABLE);
	timeout = I2C_TIMEOUT_MAX;
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT))
	{
		if ((timeout--) == 0)
		       return 10;
	}

	// posalji adresu slavea sa kojim treba komunicirat
	I2C_Send7bitAddress(I2C2, EEPROM_ADDR_W, I2C_Direction_Transmitter);		// samo promijenio ADDR
	timeout = I2C_TIMEOUT_MAX;
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		if ((timeout--) == 0)
		       return 11;
	}

	// posalji adresu registra koji treba stimat
	I2C_SendData(I2C2, addrH);	// 8b						// mijenjano
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if ((timeout--) == 0)
		       return 12;
	}
	I2C_SendData(I2C2, addrL);	// 8b						// mijenjano
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if ((timeout--) == 0)
		       return 12;		// TODO promijenit 
	}

	// EEPROM sad ocekuje podatak za zapisan na odabranu adresu
	I2C_SendData(I2C2, data);	// 8b
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if ((timeout--) == 0)
		       return 13;
	}

	// gotovi smo zasad, generiraj stop
	I2C_GenerateSTOP(I2C2, ENABLE);
	while (I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));

	return 0;
}
*/

uint8_t eeprom_write(uint16_t addr, uint8_t data)
{
	// TODO provjere da ne zapisuje na adrese kojih nema
	// zapisuje 8b na addr

	uint8_t addrH = addr >> 8;
	uint8_t addrL = addr * 0x00FF;

	i2c_start(2);

	// posalji adresu slavea sa kojim treba komunicirat
	i2c_sendAddr_tx(2, EEPROM_ADDR_W);

	// posalji adresu registra koji treba stimat
	i2c_write(2, addrH);
	i2c_write(2, addrL);

	// EEPROM sad ocekuje podatak za zapisan na odabranu adresu
	i2c_write(2, data);

	// gotovi smo zasad, generiraj stop
	i2c_stop(2);

	//delay_ms(10);	// treba mu mali delay
	delay_ms(2);	// treba mu mali delay

	return 0;
}

/**************************************************************************************************
*  					eeprom_read()						  *
**************************************************************************************************/
uint8_t eeprom_read(uint16_t addr)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;
	uint8_t addrH = addr >> 8;
	uint8_t addrL = addr * 0x00FF;
	uint8_t data = 0;

	// start
	// wait until I2C2 is not busy any more
	/*
	while (I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C2, ENABLE);
	timeout = I2C_TIMEOUT_MAX;
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT))
	{
		if ((timeout--) == 0)
		       return 10;
	}
	*/
	i2c_start(2);


	// w addr
	I2C_Send7bitAddress(I2C2, EEPROM_ADDR_W, I2C_Direction_Transmitter);		// promijenjena dev adresa
	timeout = I2C_TIMEOUT_MAX;
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		if ((timeout--) == 0)
		       return 11;
	}
	//i2c_sendAddr_tx(2, EEPROM_ADDR_W);


	// w reg
	I2C_SendData(I2C2, addrH);	// 8b						// mijenjano
	timeout = I2C_TIMEOUT_MAX;
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if ((timeout--) == 0)
		       return 12;
	}

	I2C_SendData(I2C2, addrL);	// 8b						// mijenjano
	timeout = I2C_TIMEOUT_MAX;
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if ((timeout--) == 0)
		       return 12;	// TODO
	}
	//i2c_write(2, addrH);
	//i2c_write(2, addrL);

	// ponovo start
	I2C_GenerateSTART(I2C2, ENABLE);
	timeout = I2C_TIMEOUT_MAX;
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT))
	{
		if ((timeout--) == 0)
		       return 100;
	}

	// w addr
	I2C_Send7bitAddress(I2C2, EEPROM_ADDR_R, I2C_Direction_Receiver);		// promijenjena dev adresa
	timeout = I2C_TIMEOUT_MAX;
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
	{
		if ((timeout--) == 0)
		       return 101;
	}
	//i2c_sendAddr_rx(2, EEPROM_ADDR_R);


	// procitaj data 
	I2C_AcknowledgeConfig(I2C2, DISABLE);	// NACK, ide prije reada
	timeout = I2C_TIMEOUT_MAX;
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED))
	{
		if ((timeout--) == 0)
		       return 102;
	}
	//i2c_nack(2);	// NACK, ide prije reada

	data = I2C_ReceiveData(I2C2);

	/*
	I2C_GenerateSTOP(I2C2, ENABLE);
	while (I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
	*/
	i2c_stop(2);

	return data;
}

/**************************************************************************************************
*  					eeprom_example()					  *
**************************************************************************************************/
void eeprom_example()
{
	eeprom_init();
	uint8_t read;

	//uint8_t status = eeprom_write(0x1234, 123);
	//printf("EEPROM write status: %d\n", status);
	read = eeprom_read(0x1234);
	printf("EEPROM read: %d\n", read);
	read = eeprom_read(0x1235);
	printf("EEPROM read: %d\n", read);
}
