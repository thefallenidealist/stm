// created 141205
#include "i2c.h"

// TODO sredit bolje delayeve

void i2c_init(uint8_t i2c_number, uint32_t i2c_speed)
{
	//printf("\tDEBUG: i2c_init() start\n");

	// TODO SPI1 za F4
		// razne provjere jesu li argumenti oni koji trebaju bit
	// iscupan init iz barometra
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
	I2C_InitStruct.I2C_ClockSpeed = i2c_speed;
	//I2C_InitStruct.I2C_ClockSpeed = 100000;
	//I2C_InitStruct.I2C_ClockSpeed = 400000;
	//I2C_Cmd(I2C1, ENABLE);		// F1
	//I2C_Init(I2C1,&I2C_InitStruct);	// F1
	I2C_Cmd(I2C2, ENABLE);
	I2C_Init(I2C2,&I2C_InitStruct);
	//printf("\tDEBUG: i2c_init() end\n");
}

uint8_t i2c_start(uint8_t i2c_number)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;

	// generiraj start signal
	switch (i2c_number)
	{
		case 1:
			//while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
			//while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));	// ne smije bit za ponovni i2c_start za EEPROM
			I2C_GenerateSTART(I2C1, ENABLE);
			while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
			{
				if ((timeout--) == 0)
				{
				       return 10;
				}
			}
			break;
		case 2:
			while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));	// ne smije bit za ponovni i2c_start za EEPROM XXX
			I2C_GenerateSTART(I2C2, ENABLE);

			while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT))
			{
				if ((timeout--) == 0)
				{
				       return 10;
				}
			}
			break;
		default:
			printf("\tERROR: i2c_start(): Wrong I2C port\n");
			break;
	}

	return 0;
}

void i2c_stop(uint8_t i2c_number)
{
	// generiraj stop signal
	switch (i2c_number)
	{
		case 1:
			I2C_GenerateSTOP(I2C1, ENABLE);
			while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
			break;
		case 2:
			I2C_GenerateSTOP(I2C2, ENABLE);
			while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
			break;
		default:
			printf("\tERROR: i2c_stop(): Wrong I2C port\n");
			break;
	}
}

//uint8_t i2c_sendAddr(uint8_t i2c_number, uint8_t addr)
uint8_t i2c_sendAddr_tx(uint8_t i2c_number, uint8_t addr)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;
	// posalji adresu slavea sa kojim treba komunicirat

	switch (i2c_number)
	{
		case 1:
			I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Transmitter);
			while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
			{
				if ((timeout--) == 0)
				{
				       return 11;
				}
			}
			break;
		case 2:
			I2C_Send7bitAddress(I2C2, addr, I2C_Direction_Transmitter);
			while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
			{
				if ((timeout--) == 0)
				{
				       return 11;
				}
			}
			break;
		default:
			printf("\tERROR: i2c_stop(): Wrong I2C port\n");
			break;
	}

	return 0;
}

uint8_t i2c_sendAddr_rx(uint8_t i2c_number, uint8_t addr)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;
	// posalji adresu slavea sa kojim treba komunicirat

	switch (i2c_number)
	{
		case 1:
			I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Receiver);
			while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
			{
				if ((timeout--) == 0)
				{
				       return 11;
				}
			}
			break;
		case 2:
			I2C_Send7bitAddress(I2C2, addr, I2C_Direction_Receiver);
			while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
			{
				if ((timeout--) == 0)
				{
				       return 11;
				}
			}
			break;
		default:
			printf("\tERROR: i2c_stop(): Wrong I2C port\n");
			break;
	}

	return 0;
}

uint8_t i2c_write(uint8_t i2c_number, uint8_t data)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;

	switch (i2c_number)
	{
		case 1:
			I2C_SendData(I2C1, data);	// 8b
			while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
			{
				if ((timeout--) == 0)
				{
				       return 13;
				}
			}
			break;
		case 2:
			I2C_SendData(I2C2, data);	// 8b
			while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
			{
				if ((timeout--) == 0)
				{
				       return 13;
				}
			}
			break;
		default:
			printf("\tERROR: i2c_write(): Wrong I2C port\n");
			break;
	}

	return 0;
}

uint8_t i2c_nack(uint8_t i2c_number)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;

	switch (i2c_number)
	{
		case 1:
			I2C_AcknowledgeConfig(I2C2, DISABLE);	// NACK, ide prije reada
			while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED))
			{
				if ((timeout--) == 0)
				{
				       return 102;
				}
			}
			break;
		case 2:
			I2C_AcknowledgeConfig(I2C2, DISABLE);	// NACK, ide prije reada
			while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED))
			{
				if ((timeout--) == 0)
				{
				       return 102;
				}
			}
			break;
		default:
			printf("\tERROR: i2c_stop(): Wrong I2C port\n");
			break;
	}

	return 0;
}

uint8_t i2c_read(uint8_t i2c_number)
{
	// TODO fejlaj nakon nekog timeouta, nemoj zablokirat tri vjecnosti

	//uint8_t data;

	switch (i2c_number)
	{
		case 1:
			//return I2C_ReceiveData(I2C1);
			//return I2C_ReceiveData(I2C1);
			break;
		case 2:
			// XXX ne radi iako samo pozove funkciju
			// direktno pozivanje funkcije radi
			return I2C_ReceiveData(I2C2);			// vrati nulu
			//data = I2C_ReceiveData(I2C2);
			//printf("I2C je procitao: %d\n", data);	// ispise dobro, al zablokira kod return
			//delay_ms(10);
			//return data;
			break;
		default:
			printf("\tERROR: i2c_read(): Wrong I2C port\n");
			break;
	}

	//return 0;
	return 8;
}
