// Vbat 1.8 - 3.6V	TODO
// XXX RTC_SetCounter nikad ne izadje 


#include "rtc.h"

static volatile uint8_t time_h;
static volatile uint8_t time_m;
static volatile uint8_t time_s;
static volatile uint64_t uptime_var=0;

uint32_t get_uptime(void)
{
	return uptime_var;	// ms (netocna) ili s (ovisi o RTC prescaleru)
}

void RTC_init2(void)
{
	// RTC_Configuration iz primjera
	// pravi init, od nule

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	PWR_BackupAccessCmd(ENABLE);	// Allow access to BKP Domain
	BKP_DeInit();			// Reset Backup Domain
	RCC_LSEConfig(RCC_LSE_ON);	// Enable LSE
	//RCC_LSIConfig(RCC_LSI_ON);	// Enable LSI
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)	// Wait till LSE is ready 
	//while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
	{}
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);		// Select LSE as RTC Clock Source
	//RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);		// Select LSI as RTC Clock Source
	RCC_RTCCLKCmd(ENABLE);				// Enable RTC Clock
	RTC_WaitForSynchro();				// Wait for RTC registers synchronization
	RTC_WaitForLastTask();				// Wait until last write operation on RTC registers has finished
	RTC_ITConfig(RTC_IT_SEC, ENABLE);		// Enable the RTC Second
	RTC_WaitForLastTask();				// Wait until last write operation on RTC registers has finished
	RTC_SetPrescaler(32767); 			// RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1)			1s
	RTC_WaitForLastTask();				// Wait until last write operation on RTC registers has finished

	// sam dodao
	RTC_SetCounter( (uint32_t)((11*60+55)*60) ); // here: 1st January 2000 11:55:00
	RTC_WaitForLastTask();
	BKP_WriteBackupRegister(BKP_DR1, 0x1);
	PWR_BackupAccessCmd(DISABLE);
	
	//PWR_BackupAccessCmd(DISABLE);
}

void time_vrati(void)
{
	//procitaj vrijeme iz BCKP registra
	RTC_WaitForSynchro();
	uint32_t time_tmp = RTC_GetCounter();	// dobiju se sekunde
	// XXX mozda nepotrebna linija ispod
	//RTC_WaitForLastTask();				// Wait until last write operation on RTC registers has finished

	time_h = time_tmp/3600;
	time_m = (time_tmp - time_h*3600)/60;
	time_s = (time_tmp -time_h*3600 - time_m*60);
}

void RTC_init(void)
{
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	NVIC_InitTypeDef NVIC_InitStructure;
	// Configure one bit for preemption priority
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	// Enable the RTC Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	// usch usch, jedinica
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	if (BKP_ReadBackupRegister(BKP_DR1) != 0x1)	// proizvoljna vrijednost
	{
		// uC je bio bez napona, ne zna se koje je vrijeme, RTC masinerija nije nastimana
		RTC_init2();

		// vrijeme nije sacuvano
		time_h = 0;
		time_m = 0;
		time_s = 0;

		BKP_WriteBackupRegister(BKP_DR1, 0x1);
	}
	else
	{
		// dogodio se reset, ali je vrijeme sacuvano
		time_vrati();

		RTC_WaitForSynchro();				// This function must be called before any read operation after an APB reset or an APB clock stop.
		RTC_ITConfig(RTC_IT_SEC, ENABLE);		// omogucava RTC interrupt svake sekunde
		RTC_WaitForLastTask();				// mora se pozvat prije svakog zapisivanja u RTC registre
	}
	/*
	   // stimanje da PC13 pulsira pomocu RTC-a, valjda
#ifdef RTCClockOutput_Enable
	// Enable PWR and BKP clocks
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	// Allow access to BKP Domain
	PWR_BackupAccessCmd(ENABLE);
	// Disable the Tamper Pin
	BKP_TamperPinCmd(DISABLE); // To output RTCCLK/64 on Tamper pin, the tamper functionality must be disabled 
	// Enable RTC Clock Output on Tamper Pin
	BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);
#endif
	*/
	RCC_ClearFlag();
}

void RTC_update(void)
{
	// RTC IRQ pozove ovo
	time_s++;

	if(time_s > 59)
	{
		time_s = 0;
		time_m++;
	}
	if(time_m > 59)
	{
		time_m = 0;
		time_h++;
	}
	if(time_h > 23)
	{
		time_h = 0;
	}

	uptime_var++;
}

void time_print(void)
{
	//printf("time:\t\t%.2d:%.2d:%.2d\n", time_h, time_m, time_s);
	printf("\t\t\t\t RTC: %.2d:%.2d:%.2d\n", time_h, time_m, time_s);
}

uint8_t RTC_get_h(void)
{
	return time_h;
}

uint8_t RTC_get_m(void)
{
	return time_m;
}

uint8_t RTC_get_s(void)
{
	return time_s;
}

void RTC_IRQHandler(void)
{
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
	{
		RTC_ClearITPendingBit(RTC_IT_SEC);	// Clear the RTC Second interrupt
		RTC_update();
	}
}
