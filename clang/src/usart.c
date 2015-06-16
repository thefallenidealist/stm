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
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	// 3 GPIO

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
	//GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	//GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // Pins 6 (TX) and 7 (RX) are used
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// F1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		// F4
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	//GPIO_Init(USART1_GPIO, &GPIO_InitStructure);
	//GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_Init(GPIOB, &GPIO_InitStructure);

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

	USART_Cmd(USART1, ENABLE);				// Enable USART1
}

/************************************************************************************************
*  				USART2_init()							*
*************************************************************************************************/
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
	/*
	   // svi su uvijek 0
	printf("USART1 LBD: %d\n",USART_GetITStatus(USART1, USART_IT_LBD));
	printf("USART1 IDLE: %d\n",USART_GetITStatus(USART1, USART_IT_IDLE));
	printf("USART1 ORE: %d\n",USART_GetITStatus(USART1, USART_IT_ORE));
	printf("USART1 NE: %d\n",USART_GetITStatus(USART1, USART_IT_NE));
	printf("USART1 FE: %d\n",USART_GetITStatus(USART1, USART_IT_FE));
	printf("USART1 PE: %d\n",USART_GetITStatus(USART1, USART_IT_PE));
	*/

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
		static uint8_t cnt = 0; // this counter is used to determine the string length

		char rx_char = USART_ReceiveData(USART1);

		/*
		   ne isprazni buffer, ali usart_puts ce slat samo dok ne dobije \0
		   usart_puts mora poslat \n da ono cemu salje zna kad je kraj
		   */

		if ((rx_char != '\n') && (cnt < USART_MAX_LENGTH-1))
		{
			//printf("cnt: %d\n", cnt);	// onda ne uspije sve primit
			usart1_rx_string_arr[cnt] = rx_char;
			cnt++;
			/*
			   // XXX ne radi
			if (cnt > USART_MAX_LENGTH-1)
			{
				printf("USART1 RX je dobio previse znakova error\n");
			}
			*/
		}
		else
		{
			//printf("USART1 else: USART1 RX gotov\n");
			// obrisi ostatak buffera
			for (int i=cnt; i<USART_MAX_LENGTH-1; i++)
			{
				usart1_rx_string_arr[i] = '\0';
			}
			cnt = 0;
			usart1_rx_event = RX_DONE;
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

	//USART_ClearITPendingBit(USART1, USART_IT_ERR);
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
		static uint8_t cnt = 0; // this counter is used to determine the string length

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
		//printf("zapisujem %c na mjesto %d\n", rx_char, cnt);
		usart3_rx_string_arr[cnt++] = rx_char;

		//usart3_rx_string_arr[cnt++] = USART_ReceiveData(USART3);

		// samo zapisi u buffer, bez obzira sta je
		//usart3_rx_string_arr[cnt++] = rx_char;

		// komentar
		if ( ( (rx_char != '\n') && (rx_char != '\r') ) && (cnt < USART_MAX_LENGTH-1) )
		//if (cnt < USART_MAX_LENGTH-1)
		{
			//printf("USART3 RX if: primio: %c\n", rx_char);

			usart3_rx_string_arr[cnt] = rx_char;
			cnt++;
		}
		else
		{
			//printf("USART1 else: USART1 RX gotov\n");
			// obrisi ostatak buffera
			for (int i=cnt; i<USART_MAX_LENGTH-1; i++)
			{
				usart3_rx_string_arr[i] = '\0';
			}
			cnt = 0;
			usart3_rx_event = RX_DONE;
		}
		//komentar
	}
}
*/

/************************************************************************************************
*  				usart1_parse()							*
*************************************************************************************************/
/*
void usart1_parse(void)
{
	// ono sto dobije razbije na dva komada. 

	// inicijaliziraj za slucaj da treba ispisat prazni string
	char rx_string_copy_arr[USART_MAX_LENGTH] = {};
	//char *rx_string 	= (char *)usart1_rx_string_arr;	// casting da umirimo kompajler, u originalu je volatile char
								// XXX i onda ne radi kako treba
	//char *rx_string 	= usart1_rx_string_arr[0];	// XXX
	char *rx_string 	= usart1_rx_string_arr;
	char *rx_string_copy 	= rx_string_copy_arr;
	char cmd[USART_MAX_LENGTH] = {};
	char arg[USART_MAX_LENGTH] = {};
	int cmd_delimiter = ':';

	// kopiraj, da ne razjebemo originalni string
	strncpy(rx_string_copy, rx_string, USART_MAX_LENGTH-1);

	char *tmp = strchr(rx_string_copy, cmd_delimiter);		// nadji mjesto gdje je delimiter

	if (tmp != NULL)
	{
		*tmp = '\0';	// na mjesto gdje pokazuje tmp (gdje je delimiter) ubaci null i skrati glavni string
		strcpy(cmd, rx_string_copy);
		strcpy(arg, tmp+1);

		printf("cmd: %s\n", cmd);
		printf("arg: %s\n", arg);

		usart_cmd(cmd, arg);
	}
	else
	{
		printf("u stringu nije nadjen delimiter\n");
	}

}
*/

/************************************************************************************************
*  				usart_puts()							*
*************************************************************************************************/
/*
void usart_puts(uint8_t usart, char *string)
{
	//printf("usart_puts(): string: %s\n", string);

	do
	{
		switch (usart)
		{
			case 1:
				while ((USART1->SR & USART_FLAG_TC) == (uint16_t)RESET);
				//printf("usart_puts() salje %c %d\n", *string, *string);
				USART1->DR = (*string++ & (uint16_t)0x01FF);
				break;
			case 2:
				while ((USART2->SR & USART_FLAG_TC) == (uint16_t)RESET);
				USART2->DR = (*string++ & (uint16_t)0x01FF);
				break;
			case 3:
				while ((USART3->SR & USART_FLAG_TC) == (uint16_t)RESET);
				//printf("usart_puts 3 salje: %c %d\n", *string, *string);
				USART3->DR = (*string++ & (uint16_t)0x01FF);
				break;
			default:
				printf("usart_puts(): wrong USART number\n");
				break;
		}
	//} while ((*string != '\n') && (*string != '\r') && (*string != '\0'));
	// usart_puts treba poslat \n na kraju da novi serijski zna da je dosao do kraja
	} while (*string != '\0');
}
*/
