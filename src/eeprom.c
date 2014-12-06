// created 140918
// *************************************** description ********************************************
// Atmel 24C256 I2C EEPROM driver
// *************************************** sys includes *******************************************
// *************************************** local includes *****************************************
#include "eeprom.h"
// *************************************** defines ************************************************
// *************************************** variables **********************************************
// *************************************** function prototypes ************************************
/**************************************************************************************************
*  					eeprom_init()						  *
**************************************************************************************************/
void eeprom_init()
{
	// TODO isti init kao i za barometar
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
}

/**************************************************************************************************
*  					eeprom_write()						  *
**************************************************************************************************/
uint8_t eeprom_write(uint16_t addr, uint8_t data)
{
	// zapisuje 8b na addr
	// TODO ujedinit bmp180_write i ovo, razlike opisane dolje
	uint32_t timeout = I2C_TIMEOUT_MAX;

	uint8_t addrH = addr >> 8;
	uint8_t addrL = addr * 0x00FF;

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
	I2C_Send7bitAddress(I2C1, EEPROM_ADDR_W, I2C_Direction_Transmitter);		// samo promijenio ADDR
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		if ((timeout--) == 0)
		       return 11;
	}

	// posalji adresu registra koji treba stimat
	I2C_SendData(I2C1, addrH);	// 8b						// mijenjano
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if ((timeout--) == 0)
		       return 12;
	}
	I2C_SendData(I2C1, addrL);	// 8b						// mijenjano
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if ((timeout--) == 0)
		       return 12;		// TODO promijenit 
	}

	// EEPROM sad ocekuje podatak za zapisan na odabranu adresu
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
	I2C_Send7bitAddress(I2C1, EEPROM_ADDR_W, I2C_Direction_Transmitter);		// promijenjena dev adresa
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		if ((timeout--) == 0)
		       return 11;
	}

	
	// w reg
	I2C_SendData(I2C1, addrH);	// 8b						// mijenjano
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if ((timeout--) == 0)
		       return 12;
	}
	I2C_SendData(I2C1, addrL);	// 8b						// mijenjano
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if ((timeout--) == 0)
		       return 12;	// TODO
	}


	// ponovo start
	I2C_GenerateSTART(I2C1, ENABLE);
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
	{
		if ((timeout--) == 0)
		       return 100;
	}
	// w addr
	I2C_Send7bitAddress(I2C1, EEPROM_ADDR_R, I2C_Direction_Receiver);		// promijenjena dev adresa
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
	{
		if ((timeout--) == 0)
		       return 101;
	}

	// procitaj data 
	I2C_AcknowledgeConfig(I2C1, DISABLE);	// NACK, ide prije reada
	timeout = I2C_TIMEOUT_MAX;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
	{
		if ((timeout--) == 0)
		       return 102;
	}
	data = I2C_ReceiveData(I2C1);

	I2C_GenerateSTOP(I2C1, ENABLE);
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	return data;
}

/**************************************************************************************************
*  					eeprom_example()					  *
**************************************************************************************************/
void eeprom_example()
{
	uint8_t status = eeprom_write(0x1234, 123);
	printf("EEPROM write status: %d\n", status);
	delay_ms(2);	// XXX treba
	uint8_t read = eeprom_read(0x1234);
	printf("EEPROM read: %d\n", read);
}
