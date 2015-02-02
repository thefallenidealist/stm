#include "usart.h"

// *************************************** variables **********************************************
rx_event_t usart1_rx_event = RX_PRINTED;
rx_event_t usart2_rx_event = RX_PRINTED;
rx_event_t usart3_rx_event = RX_PRINTED;
/*
volatile char usart1_rx_string_arr[USART_MAX_LENGTH] = {};
volatile char usart2_rx_string_arr[USART_MAX_LENGTH] = {};
volatile char usart3_rx_string_arr[USART_MAX_LENGTH] = {};
*/
volatile char usart1_rx_string_arr[USART_MAX_LENGTH] = {};
volatile char usart2_rx_string_arr[USART_MAX_LENGTH] = {};
volatile char usart3_rx_string_arr[USART_MAX_LENGTH] = {};



/************************************************************************************************
*  				USART1_init()							*
*************************************************************************************************/
void USART1_init(uint32_t speed)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	// 1 RCC init
	RCC_APB2PeriphClockCmd(USART1_GPIO_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(USART1_RCC, ENABLE);
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	// DMA clock
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		// moguce da i ne treba

	// 2 NVIC
	// Enable the USART1 Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);	// XXX razjebe sve
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	// 3 GPIO
	// Configure USART1 Tx (PA9) as alternate function push-pull
	GPIO_InitStructure.GPIO_Pin = USART1_TX_Pin;
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(USART1_GPIO, &GPIO_InitStructure);
	// Configure USART1 Rx (PA10) as input floating
	GPIO_InitStructure.GPIO_Pin = USART1_RX_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// moze i IPD/IPU
	GPIO_Init(USART1_GPIO, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = speed;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);				// Enable USART1

	//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);	// XXX razjebe sve
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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
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

/************************************************************************************************
*  				USART1_IRQHandler()						*
*************************************************************************************************/
void USART1_IRQHandler(void)
{
	usart1_rx_string_arr[USART_MAX_LENGTH-1] = '\0';
	usart3_rx_string_arr[USART_MAX_LENGTH-1] = '\0';

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		usart1_rx_event = RX_IN_PROGRESS;

		static uint8_t cnt = 0; // this counter is used to determine the string length

		char rx_char = USART_ReceiveData(USART1);

		//if( (rx_char != '\n') && (cnt < USART_MAX_LENGTH) )
		//if ( ( (rx_char != '\n') || (rx_char != '\r') ) && (cnt < USART_MAX_LENGTH) )
		if ( ( (rx_char != '\n') && (rx_char != '\r') ) && (cnt < USART_MAX_LENGTH-1) )
		{
			usart1_rx_string_arr[cnt] = rx_char;
			cnt++;
		}
		else
		{
			//usart1_rx_string_arr[--cnt] = '\0';	// maknimo \n i dodajmo null
			if(cnt < USART_MAX_LENGTH-1)
			{
				usart1_rx_string_arr[cnt] = rx_char;
			}
			cnt = 0;
			usart1_rx_event = RX_DONE;
		}
	}
	// interrupt treba testirat da zna jel RX ili TX u pitanju
	// else if USART_IT_TXE
}

/************************************************************************************************
*  				USART2_IRQHandler()						*
*************************************************************************************************/
/*
void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		usart2_rx_event = RX_IN_PROGRESS;

		static uint8_t cnt = 0; // this counter is used to determine the string length

		char rx_char = USART_ReceiveData(USART2);

		if( (rx_char != '\n') && (cnt < USART_MAX_LENGTH) )
		{
			usart2_rx_string_arr[cnt] = rx_char;
			cnt++;
		}
		else
		{
			usart2_rx_string_arr[--cnt] = '\0';	// maknimo \n i dodajmo null
			cnt = 0;
			usart2_rx_event = RX_DONE;
		}
	}
	// interrupt treba testirat da zna jel RX ili TX u pitanju
	// else if USART_IT_TXE
}
*/

/************************************************************************************************
*  				USART3_IRQHandler()						*
*************************************************************************************************/
void USART3_IRQHandler(void)
{
	usart1_rx_string_arr[USART_MAX_LENGTH-1] = '\0';
	usart3_rx_string_arr[USART_MAX_LENGTH-1] = '\0';

	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		usart3_rx_event = RX_IN_PROGRESS;

		static uint8_t cnt = 0; // this counter is used to determine the string length

		char rx_char = USART_ReceiveData(USART3);

		//if( (rx_char != '\n') && (cnt < USART_MAX_LENGTH) )
		//if ( ( (rx_char != '\n') || (rx_char != '\r') ) && (cnt < USART_MAX_LENGTH) )
		//if ( ( (rx_char != '\n') && (rx_char != '\r') ) && (cnt < USART_MAX_LENGTH) )
		//while ( (rx_char != '\n') || (rx_char != '\r') || (cnt < USART_MAX_LENGTH) )

		/*
		if (rx_char == '\r')
			printf("USART3 naletio na r\n");
		if (rx_char == '\n')
			printf("USART3 naletio na n\n");
		if (rx_char == '\0')
			printf("USART3 naletio na 0\n");
		if (rx_char == NULL)
			printf("USART3 naletio na NULL\n");
		if (rx_char == 'A')
			printf("USART3 naletio na char A\n");
			*/

		if ( (rx_char != '\n') && (rx_char != '\r') && (rx_char != 0) && \
				(rx_char >= 32) && (rx_char < 127) && (cnt < USART_MAX_LENGTH-1) )
		{
			//printf("USART3 unutar divljeg ifa\n");
			//printf("USART3 primio: %c\n", rx_char);
			//printf("USART3 prima %d. kurton u usta\n", cnt);
			usart3_rx_string_arr[cnt] = rx_char;
			cnt++;
		}
		else
		{
			printf("USART3 unutar else\n");
			// TODO ljepse bude na USART1 kad nema na kraju \n (jer imaju printfovi)
			// ali razjebe USART puts jer ce on isprintat sve tek kad dobije \n
			//usart3_rx_string_arr[--cnt] = '\0';	// maknimo \n i dodajmo null
			//usart1_rx_string_arr[cnt] = rx_char;
			cnt = 0;
			usart3_rx_event = RX_DONE;
		}
	}
	// interrupt treba testirat da zna jel RX ili TX u pitanju
	// else if USART_IT_TXE
}

/************************************************************************************************
*  				usart1_parse()							*
*************************************************************************************************/
void usart1_parse(void)
{
	// ono sto dobije razbije na dva komada. 

	// inicijaliziraj za slucaj da treba ispisat prazni string
	char rx_string_copy_arr[USART_MAX_LENGTH] = {};
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
	}
	else
	{
		printf("u stringu nije nadjen delimiter\n");
	}
}

/************************************************************************************************
*  				usart_puts()							*
*************************************************************************************************/
void usart_puts(uint8_t usart, char *string)
{
	printf("e, odje usart_puts\n");
	printf("usart_puts(): string: %s\n", *string);
	//size_t string_length = strlen(string);
	//printf("usart_puts(): duzina stringa: %lu\n", string_length);

	//for (uint8_t i=0; i<=string_length; i++)	// +1 za \n
	//while(*string != '\n')
	do
	{
		switch (usart)
		{
			case 1:
				while ((USART1->SR & USART_FLAG_TC) == (uint16_t)RESET);
				USART1->DR = (*string++ & (uint16_t)0x01FF);
				break;
			case 2:
				while ((USART2->SR & USART_FLAG_TC) == (uint16_t)RESET);
				USART2->DR = (*string++ & (uint16_t)0x01FF);
				break;
			case 3:
				while ((USART3->SR & USART_FLAG_TC) == (uint16_t)RESET);
				USART3->DR = (*string++ & (uint16_t)0x01FF);
				break;
			default:
				printf("usart_puts(): wrong USART number\n");
				break;
		}
		//printf("zadnji char koji smo dobili: %c\n", *string);
		// TODO
		// mora se pazit da zadnji char stringa bude \n inace ce samo bufferirat i ispisat sutra citavu hrpu

		if(*string == '\n')
			printf("usart_puts() je dobio beckslesh n\n");
		if(*string == '\0')
			printf("usart_puts() je dobio nulnul\n");


	} while ((*string != '\n') && (*string != '\0'));

	printf("e, odje usart_puts kraj\n");
}
