// XXX STM32F4, ubio sam USART1 RX (nikad ne udje u interrupt)
#include "usart.h"

// *************************************** variables **********************************************
volatile rx_event_t usart1_rx_event = RX_PRINTED;
volatile rx_event_t usart2_rx_event = RX_PRINTED;
volatile rx_event_t usart3_rx_event = RX_PRINTED;
volatile char usart1_rx_string_arr[USART_MAX_LENGTH] = {};
volatile char usart2_rx_string_arr[USART_MAX_LENGTH] = {};
volatile char usart3_rx_string_arr[USART_MAX_LENGTH] = {};

char testbuffer[] = "Ovo je testni buffer za USART TX IRQ\n";

//extern void usart_cmd(char *cmd, char *arg);



/************************************************************************************************
*  				USART1_init()							*
*************************************************************************************************/
void USART1_init(uint32_t speed)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	// 1 RCC init
	//RCC_APB2PeriphClockCmd(USART1_GPIO_RCC, ENABLE);	// F1	F4


	// GPIO clock
	//RCC_APB2PeriphClockCmd(USART1_RCC, ENABLE);	// F1
	//RCC_AHB1PeriphClockCmd(USART1_RCC, ENABLE);	// F4	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	// 3 GPIO

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
	//GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	//GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // GPIOB
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;	// GPIOA
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// F1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		// F4
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	//GPIO_Init(USART1_GPIO, &GPIO_InitStructure);
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//GPIO_Init(GPIOA, &GPIO_InitStructure);

	//GPIO_InitStructure.GPIO_Pin = USART1_RX_Pin;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// moze i IPD/IPU		// F1
	////GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;						// F4
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		// F4
	//GPIO_Init(USART1_GPIO, &GPIO_InitStructure);


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	USART_InitStructure.USART_BaudRate = speed;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		// CTS and RTS are not used
	USART_Init(USART1, &USART_InitStructure);
	//USART_Cmd(USART1, ENABLE);				// Enable USART1

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);	// mora bit ispod USART1 ENABLE

	// 2 NVIC
	// Enable the USART1 Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//void __enable_irq(void);

	USART_Cmd(USART1, ENABLE);				// Enable USART1
}

/************************************************************************************************
*  				USART2_init()							*
*************************************************************************************************/
void USART2_init(uint32_t speed)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	// 1 RCC init
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	// 3 GPIO
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		// F4
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	USART_InitStructure.USART_BaudRate = speed;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		// CTS and RTS are not used
	USART_Init(USART2, &USART_InitStructure);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	//USART_ITConfig(USART2, USART_IT_TXE, ENABLE);	// mora bit ispod USART2 ENABLE

	// 2 NVIC
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART2, ENABLE);
}
/*
void USART2_init(uint32_t speed)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// 1 RCC init
	RCC_APB2PeriphClockCmd(USART2_GPIO_RCC, ENABLE);
	//rcc_AHBPeriphClockCmd(USART2_GPIO_RCC, ENABLE);
	RCC_APB1PeriphClockCmd(USART2_RCC, ENABLE);
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	// DMA clock
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		// moguce da i ne treba

	// 2 NVIC
	// Enable the USART2 Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//USART_ITConfig(USART2, USART_IT_TXE, ENABLE);	// XXX razjebe sve
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	// 3 GPIO
	// Configure USART2 Tx (PA9) as alternate function push-pull
	GPIO_InitStructure.GPIO_Pin = USART2_TX_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	// picka mu mater'na!
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(USART2_GPIO, &GPIO_InitStructure);
	// Configure USART2 Rx (PA10) as input floating
	GPIO_InitStructure.GPIO_Pin = USART2_RX_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// moze i IPD/IPU
	GPIO_Init(USART2_GPIO, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = speed;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);
	USART_Cmd(USART2, ENABLE);
}
*/

/************************************************************************************************
*  				USART3_init()							*
*************************************************************************************************/
/*
void USART3_init(uint32_t speed)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	// 1 RCC init
	RCC_APB2PeriphClockCmd(USART3_GPIO_RCC, ENABLE);
	RCC_APB1PeriphClockCmd(USART3_RCC, ENABLE);

	// 2 NVIC
	// Enable the USART3 Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//USART_ITConfig(USART3, USART_IT_TXE, ENABLE);	// XXX razjebe sve
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	// 3 GPIO
	GPIO_InitStructure.GPIO_Pin = USART3_TX_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(USART3_GPIO, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = USART3_RX_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART3_GPIO, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = speed;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);
	USART_Cmd(USART3, ENABLE);
}
*/

/************************************************************************************************
*  				USART1_IRQHandler()						*
*************************************************************************************************/
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		/*
		   // samo proslijedi
		usart1_rx_event = RX_IN_PROGRESS;
		uint16_t rx_char = USART_ReceiveData(USART1);
		printf("USART1 RX: %d\n", rx_char);
			usart1_rx_event = RX_DONE;
			*/


		usart1_rx_event = RX_IN_PROGRESS;
		static uint8_t counter = 0; // this counter is used to determine the string length

		char rx_char = USART_ReceiveData(USART1);

		/*
		   ne isprazni buffer, ali usart_puts ce slat samo dok ne dobije \0
		   usart_puts mora poslat \n da ono cemu salje zna kad je kraj
		   */

		if ((rx_char != '\n') && (counter < USART_MAX_LENGTH-1))
		{
			//printf("counter: %d\n", counter);	// onda ne uspije sve primit
			usart1_rx_string_arr[counter] = rx_char;
			counter++;
			/*
			   // XXX ne radi
			if (counter > USART_MAX_LENGTH-1)
			{
				printf("USART1 RX je dobio previse znakova error\n");
			}
			*/
		}
		else
		{
			//printf("USART1 else: USART1 RX gotov\n");
			// obrisi ostatak buffera
			for (int i=counter; i<USART_MAX_LENGTH-1; i++)
			{
				usart1_rx_string_arr[i] = '\0';
			}
			counter = 0;
			usart1_rx_event = RX_DONE;

			printf("trebam pozvat parse()\n");
			usart_parse();
		}
	}

	/*

	static int counter=0;
	// interrupt treba testirat da zna jel RX ili TX u pitanju
	if (USART_GetITStatus(USART1, USART_IT_TXE) == SET)
	{
		// stalno zaglavi ovdje
		//printf("USART1 TX IRQ\n");	// stalno salje

		   // neat pizdarijica svijetli ko Betlehem, u terminalu nista
		USART_SendData(USART1, testbuffer[counter++]);

		//printf("counter: %d\n", counter);
		if (counter >= (sizeof(testbuffer)-1))
		{
			counter = 0;
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
		}
	}
	*/

	USART_ClearITPendingBit(USART1, USART_IT_ERR);
}

/************************************************************************************************
*  				USART3_IRQHandler()						*
*************************************************************************************************/
/*
void USART3_IRQHandler(void)
{
	//if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		usart3_rx_event = RX_IN_PROGRESS;
		static uint8_t counter = 0; // this counter is used to determine the string length

		if (USART_GetFlagStatus(USART3, USART_FLAG_FE) == SET)
		{
			USART_ClearFlag(USART3, USART_FLAG_FE);
			printf("FE\n");
			// nikad ne dodje ovamo iako datašit kaze:
			// When a break character is received, the USART handles it as a framing error.
		}
		if (USART_GetFlagStatus(USART3, USART_FLAG_ORE) == SET)
		{
			//static int ore_counter = 0;
			USART_ClearFlag(USART3, USART_FLAG_ORE);
			//printf("ORE overun: %d\n", ++ore_counter);
			// doknacno dodje vamo kad WLAN modul vrati komandu nazad
		}
		if (USART_GetFlagStatus(USART3, USART_FLAG_LBD) == SET)
		{
			USART_ClearFlag(USART3, USART_FLAG_LBD);
			printf("Line break\n");
			// ne dodje vamo
		}

		char rx_char = USART_ReceiveData(USART3);
		printf("%c", rx_char);
		//printf("zapisujem %c na mjesto %d\n", rx_char, counter);
		usart3_rx_string_arr[counter++] = rx_char;

		//usart3_rx_string_arr[counter++] = USART_ReceiveData(USART3);

		// samo zapisi u buffer, bez obzira sta je
		//usart3_rx_string_arr[counter++] = rx_char;

		// komentar
		if ( ( (rx_char != '\n') && (rx_char != '\r') ) && (counter < USART_MAX_LENGTH-1) )
		//if (counter < USART_MAX_LENGTH-1)
		{
			//printf("USART3 RX if: primio: %c\n", rx_char);

			usart3_rx_string_arr[counter] = rx_char;
			counter++;
		}
		else
		{
			//printf("USART1 else: USART1 RX gotov\n");
			// obrisi ostatak buffera
			for (int i=counter; i<USART_MAX_LENGTH-1; i++)
			{
				usart3_rx_string_arr[i] = '\0';
			}
			counter = 0;
			usart3_rx_event = RX_DONE;
		}
		//komentar
	}
}
*/
/************************************************************************************************
*  				USART2_IRQHandler()						*
*************************************************************************************************/
void USART2_IRQHandler(void)
{
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{

		usart_puts(2, "USART2 IRQ unutar if\n");

		usart2_rx_event = RX_IN_PROGRESS;
		static uint8_t counter = 0; // this counter is used to determine the string length

		char rx_char = USART_ReceiveData(USART2);

		if ((rx_char != '\n') && (counter < USART_MAX_LENGTH-1))
		{
			usart2_rx_string_arr[counter] = rx_char;
			counter++;
			usart_puts(2, "USART2 IRQ unutar if if\n");
		}
		else
		{
			// XXX nikad ne dodje ovdje
			usart_puts(2, "USART2 IRQ unutar if else\n");

			for (int i=counter; i<USART_MAX_LENGTH-1; i++)
			{
				usart2_rx_string_arr[i] = '\0';
			}
			counter = 0;
			usart2_rx_event = RX_DONE;

			usart_puts(2, "trebam pozvat parse()\n");
			usart_parse();
		}
		usart_puts(2, "USART2 IRQ pred kraj prvog if-a\n");
			usart_parse();
	}
}

void usart_clear(uint8_t usart)
{
	usart_puts(usart, "\033c");	// clear
}
