// created 141205
#include "i2c.h"
#include "colors_ansi.h"

// TODO	return 255;
// TODO sredit bolje delayeve

// TODO
// oporavak od bus errora:
// void I2C_SoftwareResetCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)

enum
{
	I2C_EXIT_SUCCESS = 0,
	I2C_EXIT_WRONG_NUMBER,
	I2C_EXIT_TIMEOUT_START,
	I2C_EXIT_TIMEOUT_STOP,
	I2C_EXIT_TIMEOUT_ADDR_TX,
	I2C_EXIT_TIMEOUT_ADDR_RX,
	I2C_EXIT_TIMEOUT_STOPF,
	I2C_EXIT_TIMEOUT_BTF,
	I2C_EXIT_TIMEOUT_WRITE_BTF,
	I2C_EXIT_TIMEOUT_READ_BTF,
	I2C_EXIT_TIMEOUT_WRITE_STOPF,
	I2C_EXIT_TIMEOUT_READ_STOPF
};

/*************************************************************************************************
*					i2c_start()
*************************************************************************************************/
//static int8_t i2c_start(uint8_t i2c_number)
int8_t i2c_start(uint8_t i2c_number)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;

	switch (i2c_number)
	{
		case 1:
			while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
			// timeout? TODO
			I2C_GenerateSTART(I2C1, ENABLE);

			while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
			{
				if ((timeout--) == 0)
				{
					printf(ANSI_COLOR_RED "ERROR %s(%d) timeouted\n" ANSI_COLOR_RESET, __func__, i2c_number);
					return I2C_EXIT_TIMEOUT_START;
				}
			}
			break;
		case 2:
			while (I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));	
			// timeout? TODO
			I2C_GenerateSTART(I2C2, ENABLE);

			while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT))
			{
				if ((timeout--) == 0)
				{
					printf(ANSI_COLOR_RED "ERROR %s(%d) timeouted\n" ANSI_COLOR_RESET, __func__, i2c_number);
					return I2C_EXIT_TIMEOUT_START;
				}
			}
			break;
		default:
			printf(ANSI_COLOR_RED "ERROR: %s(): Wrong I2C port: %d\n" ANSI_COLOR_RESET, __func__, i2c_number);
			return I2C_EXIT_WRONG_NUMBER;
			//break;
	}
	//return EXIT_FAILURE;	// treba bit da se kompajler ne buni
	return 255;
}

/*************************************************************************************************
*					i2c_restart()
*************************************************************************************************/
//static int8_t i2c_restart(uint8_t i2c_number)
int8_t i2c_restart(uint8_t i2c_number)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;

	switch (i2c_number)
	{
		case 1:
			//while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
			// timeout? TODO
			I2C_GenerateSTART(I2C1, ENABLE);

			while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
			{
				if ((timeout--) == 0)
				{
					printf(ANSI_COLOR_RED "ERROR %s(%d) timeouted\n" ANSI_COLOR_RESET, __func__, i2c_number);
					return I2C_EXIT_TIMEOUT_START;
				}
			}
			break;
		case 2:
			//while (I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));	
			// timeout? TODO
			I2C_GenerateSTART(I2C2, ENABLE);

			while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT))
			{
				if ((timeout--) == 0)
				{
					printf(ANSI_COLOR_RED "ERROR %s(%d) timeouted\n" ANSI_COLOR_RESET, __func__, i2c_number);
					return I2C_EXIT_TIMEOUT_START;
				}
			}
			break;
		default:
			printf(ANSI_COLOR_RED "ERROR: %s(): Wrong I2C port: %d\n" ANSI_COLOR_RESET, __func__, i2c_number);
			return I2C_EXIT_WRONG_NUMBER;
			//break;
	}
	//return EXIT_FAILURE;	// treba bit da se kompajler ne buni
	return 255;
}

/*************************************************************************************************
*					i2c_stop()
*************************************************************************************************/
//static int8_t i2c_stop(uint8_t i2c_number)
 int8_t i2c_stop(uint8_t i2c_number)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;

	switch (i2c_number)
	{
		case 1:
			I2C_GenerateSTOP(I2C1, ENABLE);

			//while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY))
			while (I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF))
			{
				if ((timeout--) == 0)
				{
					printf(ANSI_COLOR_RED "ERROR %s(%d) timeouted BUSY ili STOPF\n" ANSI_COLOR_RESET, __func__, i2c_number);
					return I2C_EXIT_TIMEOUT_STOP;
				}
			}

			break;
		case 2:
			I2C_GenerateSTOP(I2C2, ENABLE);

			//while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY))
			while (I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF))		// radi iako je znao prije timeoutat
			{
				if ((timeout--) == 0)
				{
					printf(ANSI_COLOR_RED "ERROR %s(%d) timeouted BUSY ili STOPF\n" ANSI_COLOR_RESET, __func__, i2c_number);
					return I2C_EXIT_TIMEOUT_STOP;
				}
			}

			break;
		default:
			printf(ANSI_COLOR_RED "ERROR: %s(): Wrong I2C port: %d\n" ANSI_COLOR_RESET, __func__, i2c_number, i2c_number);
			return I2C_EXIT_WRONG_NUMBER;
			//break;
	}
	return 255;
}

/*************************************************************************************************
*					i2c_sendAddr_tx()
*************************************************************************************************/
//static int8_t i2c_sendAddr_tx(uint8_t i2c_number, uint8_t addr)
int8_t i2c_sendAddr_tx(uint8_t i2c_number, uint8_t addr)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;

	switch (i2c_number)
	{
		case 1:
			I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Transmitter);

			while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
			{
				if ((timeout--) == 0)
				{
					printf(ANSI_COLOR_RED "ERROR %s(%d) timeouted\n" ANSI_COLOR_RESET, __func__, i2c_number);
					return I2C_EXIT_TIMEOUT_ADDR_TX;
				}
			}

			break;
		case 2:
			I2C_Send7bitAddress(I2C2, addr, I2C_Direction_Transmitter);

			while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
			{
				if ((timeout--) == 0)
				{
					printf(ANSI_COLOR_RED "ERROR %s(%d) timeouted\n" ANSI_COLOR_RESET, __func__, i2c_number);
					return I2C_EXIT_TIMEOUT_ADDR_TX;
				}
			}

			break;
		default:
			printf(ANSI_COLOR_RED "ERROR: %s(): Wrong I2C port: %d\n" ANSI_COLOR_RESET, __func__, i2c_number);
			return I2C_EXIT_WRONG_NUMBER;
			//break;
	}
	return 255;
}

/*************************************************************************************************
*					i2c_sendAddr_rx()
*************************************************************************************************/
//static int8_t i2c_sendAddr_rx(uint8_t i2c_number, uint8_t addr)
int8_t i2c_sendAddr_rx(uint8_t i2c_number, uint8_t addr)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;

	switch (i2c_number)
	{
		case 1:
			I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Receiver);
			//while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_ADDR))	// XXX timeouta
			while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))	// vise ne timeouta, ali opet zapne negdje
			{
				if ((timeout--) == 0)
				{
					//printf("ERROR %s(%d) timeouted\n", __func__, i2c_number);
					printf(ANSI_COLOR_RED "ERROR %s(%d) timeouted\n" ANSI_COLOR_RESET, __func__, i2c_number);
					return I2C_EXIT_TIMEOUT_ADDR_RX;
				}
			}
			break;
		case 2:
			//i2c_ack(2);
			//i2c_start(2);
			I2C_Send7bitAddress(I2C2, addr, I2C_Direction_Receiver);
			//while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_ADDR))	// XXX timeouta
			while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))	// vise ne timeouta, ali opet zapne negdje
			{
				if ((timeout--) == 0)
				{
					//printf("ERROR %s(%d) timeouted\n", __func__, i2c_number);
					printf(ANSI_COLOR_RED "ERROR %s(%d) timeouted\n" ANSI_COLOR_RESET, __func__, i2c_number);
					return I2C_EXIT_TIMEOUT_ADDR_RX;
				}
			}
			break;
		default:
			//printf("ERROR %s(%d) wrong I2C port: %d\n", __func__, i2c_number, i2c_number);
			printf(ANSI_COLOR_RED "ERROR: %s(): Wrong I2C port: %d\n" ANSI_COLOR_RESET, __func__, i2c_number);
			return I2C_EXIT_WRONG_NUMBER;
			//break;
	}
	return 255;
}

/*************************************************************************************************
*					i2c_nack()
*************************************************************************************************/
//static int8_t i2c_nack(uint8_t i2c_number)
int8_t i2c_nack(uint8_t i2c_number)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;

	switch (i2c_number)
	{
		case 1:
			I2C_AcknowledgeConfig(I2C1, DISABLE);
			while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
			{
				if ((timeout--) == 0)
				{
					// TODO
				       return 102;
				}
			}
			break;
		case 2:
			I2C_AcknowledgeConfig(I2C2, DISABLE);
			while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED))
			{
				if ((timeout--) == 0)
				{
					// TODO
				       return 102;
				}
			}
			break;
		default:
			printf(ANSI_COLOR_RED "ERROR: %s(): Wrong I2C port: %d\n" ANSI_COLOR_RESET, __func__, i2c_number);
			return I2C_EXIT_WRONG_NUMBER;
			break;
	}

	return 0;
}

/*************************************************************************************************
*					i2c_ack()
*************************************************************************************************/
//static int8_t i2c_ack(uint8_t i2c_number)
 int8_t i2c_ack(uint8_t i2c_number)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;

	switch (i2c_number)
	{
		case 1:
			I2C_AcknowledgeConfig(I2C1, ENABLE);
			I2C_NACKPositionConfig(I2C2, I2C_NACKPosition_Current);	// mozda treba
			while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
			{
				if ((timeout--) == 0)
				{
					// TODO
				       return 102;
				}
			}
			break;
		case 2:
			I2C_AcknowledgeConfig(I2C2, ENABLE);
			I2C_NACKPositionConfig(I2C2, I2C_NACKPosition_Current);	// mozda treba
			/*
			while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED))
			{
				if ((timeout--) == 0)
				{
					// TODO
				       return 102;
				}
			}
			*/
			break;
		default:
			printf(ANSI_COLOR_RED "ERROR: %s(): Wrong I2C port: %d\n" ANSI_COLOR_RESET, __func__, i2c_number);
			return I2C_EXIT_WRONG_NUMBER;
			//break;
	}

	return 0;
}




/*************************************************************************************************
*					public functions
*/
/*************************************************************************************************
*					i2c_read()
*************************************************************************************************/
int8_t i2c_init(uint8_t i2c_number, uint32_t i2c_speed)
{
	if (i2c_number > 2)
	{
		printf(ANSI_COLOR_RED "ERROR %s(%d) wrong I2C port: %d\n" ANSI_COLOR_RESET, __func__, i2c_number, i2c_number);
		return I2C_EXIT_WRONG_NUMBER;
	}

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

	//return EXIT_SUCCESS;
	return 0;	// da se ne ukljucuje stdlib koji ima EXIT_SUCCESS
}

/*************************************************************************************************
*					i2c_write()
*************************************************************************************************/
int8_t i2c_write(uint8_t i2c_number, uint8_t slave_addr, uint8_t data)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;

	switch (i2c_number)
	{
		case 1:
			i2c_ack(1);
			i2c_start(1);
			i2c_sendAddr_tx(1, slave_addr);
			I2C_SendData(I2C1, data);
			while (!I2C_GetFlagStatus(I2C1, I2C_FLAG_BTF))
			{
				if ((timeout--) == 0)
				{
					printf(ANSI_COLOR_RED "ERROR %s(%d, 0x%x, 0x%x) timeouted BTF\n" ANSI_COLOR_RESET, __func__, i2c_number, slave_addr, data);
					return I2C_EXIT_TIMEOUT_WRITE_BTF;
				}
			}
			i2c_stop(1);
			break;
		case 2:
			i2c_ack(2);
			i2c_start(2);
			i2c_sendAddr_tx(2, slave_addr);
			I2C_SendData(I2C2, data);
			while (!I2C_GetFlagStatus(I2C2, I2C_FLAG_BTF))
			{
				if ((timeout--) == 0)
				{
					printf(ANSI_COLOR_RED "ERROR %s(%d, 0x%x, 0x%x) timeouted BTF\n" ANSI_COLOR_RESET, __func__, i2c_number, slave_addr, data);
					return I2C_EXIT_TIMEOUT_WRITE_BTF;
				}
			}
			/*o
			  // XXX timeouta
			I2C_GenerateSTOP(I2C2, ENABLE);
			while (!I2C_GetFlagStatus(I2C2, I2C_FLAG_STOPF))
			{
				if ((timeout--) == 0)
				{
					//printf("ERROR %s(%d) timeouted STOPF\n", __func__, i2c_number);
					// timeouta XXX
					//printf(ANSI_COLOR_RED "ERROR %s(%d, 0x%x, 0x%x) timeouted STOPF\n" ANSI_COLOR_RESET, __func__, i2c_number, slave_addr, data);
					printf(ANSI_COLOR_RED "ERROR %s(%d, 0x%x, 0x%x) timeouted STOPF\n" ANSI_COLOR_RESET, __func__,
						       	i2c_number, slave_addr, data);
					//timeout = I2C_TIMEOUT_MAX;
					return I2C_EXIT_TIMEOUT_WRITE_STOPF;
				}
			}
			*/
			i2c_stop(2);	// radi oke
			break;
		default:
			printf(ANSI_COLOR_RED "ERROR: %s(): Wrong I2C port: %d\n" ANSI_COLOR_RESET, __func__, i2c_number);
			return I2C_EXIT_WRONG_NUMBER;
			//break;
	}

	return 255;
}

/*************************************************************************************************
*					i2c_write2()
*************************************************************************************************/
// kad treba u istom prolazu npr poslat adresu slavea, registar i podatak za upisat u taj registar
int8_t i2c_write2(uint8_t i2c_number, uint8_t slave_addr, uint8_t reg, uint8_t data)
{
	uint32_t timeout = I2C_TIMEOUT_MAX;

	switch (i2c_number)
	{
		case 2:
			i2c_start(2);
			i2c_sendAddr_tx(2, slave_addr);
			I2C_SendData(I2C2, reg);
			//while (--number_of_bytes_to_send)
			// posalji prvi
			while (!I2C_GetFlagStatus(I2C2, I2C_FLAG_BTF))
			{
				if ((timeout--) == 0)
				{
					//printf("ERROR %s(%d) timeouted BTF\n", __func__, i2c_number);
					printf(ANSI_COLOR_RED "ERROR %s(%d) timeouted BTF\n" ANSI_COLOR_RESET, __func__, i2c_number);
					return I2C_EXIT_TIMEOUT_WRITE_BTF;
				}
			}
			// posalji drugi
			I2C_SendData(I2C2, data);
			//while (!I2C_GetFlagStatus(I2C2, I2C_FLAG_BTF));
			while (!I2C_GetFlagStatus(I2C2, I2C_FLAG_BTF))
			{
				if ((timeout--) == 0)
				{
					//printf("ERROR %s(%d) timeouted BTF\n", __func__, i2c_number);
					printf(ANSI_COLOR_RED "ERROR %s(%d) timeouted BTF\n" ANSI_COLOR_RESET, __func__, i2c_number);
					return I2C_EXIT_TIMEOUT_WRITE_BTF;
				}
			}
			/*
			I2C_GenerateSTOP(I2C2, ENABLE);
			while (!I2C_GetFlagStatus(I2C2, I2C_FLAG_STOPF))
			{
				if ((timeout--) == 0)
				{
					printf("ERROR %s(%d) timeouted STOPF\n", __func__, i2c_number);
					return I2C_EXIT_TIMEOUT_WRITE_STOPF;
				}
			}
			*/
			i2c_stop(2);
			break;
		default:
			printf("ERROR %s(%d) wrong I2C port: %d\n", __func__, i2c_number, i2c_number);
			printf(ANSI_COLOR_RED "ERROR %s(%d) wrong I2C port: %d\n" ANSI_COLOR_RESET, __func__, i2c_number, i2c_number);
			//printf(ANSI_COLOR_RED "ERROR: %s(): Wrong I2C port: %d\n" ANSI_COLOR_RESET, __func__, i2c_number);
			return I2C_EXIT_WRONG_NUMBER;
			//break;
	}

	return 255;
}

/*************************************************************************************************
*					i2c_read()
*************************************************************************************************/
int8_t i2c_read(uint8_t i2c_number, uint8_t slave_addr)
{
	uint8_t received;

	switch (i2c_number)
	{
		case 1:
			// TODO
			break;
		case 2:
			i2c_start(2);
			i2c_sendAddr_rx(2, slave_addr);
			i2c_nack(2);
			i2c_stop(2);	// tutorial tako kaze
			while(!I2C_GetFlagStatus(I2C2, I2C_FLAG_RXNE));	// cekaj da primi sve
			// TODO timeout
			received = I2C_ReceiveData(I2C2);
			while(I2C_GetFlagStatus(I2C2, I2C_FLAG_STOPF));	// cekaj na nesta
			// TODO timeout
			return received;
		default:
			printf(ANSI_COLOR_RED "ERROR: %s(): Wrong I2C port: %d\n" ANSI_COLOR_RESET, __func__, i2c_number);
			return I2C_EXIT_WRONG_NUMBER;
			//break;
	}
	return 255;
}

/*************************************************************************************************
*					i2c_readN()
*************************************************************************************************/
int8_t i2c_readN(uint8_t i2c_number, uint8_t slave_addr, uint8_t howmany, uint8_t *array)
{
	uint8_t received;
	uint8_t counter = 0;
	uint32_t timeout = I2C_TIMEOUT_MAX;

	switch (i2c_number)
	{
		case 1:
			// TODO
			break;
		case 2:
			i2c_start(2);
			i2c_sendAddr_rx(2, slave_addr);
			i2c_nack(2);
			//i2c_stop(2);	// tutorial tako kaze

			while (--howmany)
			{

				timeout = I2C_TIMEOUT_MAX;
				printf("unutar %s() howmany: %d counter: %d\n", __func__, howmany, counter);

				while (!I2C_GetFlagStatus(I2C2, I2C_FLAG_RXNE))	// cekaj da primi sve
				if ((timeout--) == 0)
				{
					printf(ANSI_COLOR_RED "ERROR %s(%d) timeouted RXNE\n" ANSI_COLOR_RESET, __func__, i2c_number);
					//return I2C_EXIT_TIMEOUT_READ_STOPF;
					return -1;
				}

				received = I2C_ReceiveData(I2C2);
				array[counter++] = received;
				//array[counter++] = counter;
				//return received;
			}

			i2c_stop(2);
				while (I2C_GetFlagStatus(I2C2, I2C_FLAG_STOPF))
				if ((timeout--) == 0)
				{
					printf(ANSI_COLOR_RED "ERROR %s(%d) timeouted STOPF\n" ANSI_COLOR_RESET, __func__, i2c_number);
					//return I2C_EXIT_TIMEOUT_READ_STOPF;
					return -1;
				}
			return 0;
		default:
			printf(ANSI_COLOR_RED "ERROR: %s(): Wrong I2C port: %d\n" ANSI_COLOR_RESET, __func__, i2c_number);
			return I2C_EXIT_WRONG_NUMBER;
			//break;
	}
	return 255;
}
