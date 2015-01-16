//
#include "rtc2.h"

typedef enum
{
	RTC_SETUP_NOT_DONE = 0,
	RTC_SETUP_DONE = 1
} rtc_setup_t;
rtc_setup_t rtc_setup;

void rtc_main()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	PWR_BackupAccessCmd(ENABLE);

	//RTC_DeInit();

	uint32_t status;
	status = RTC_ReadBackupRegister(RTC_BKP_DR0);
	printf("rtc status: %d\n", status);

	// prvo omoguci LSI
	RCC_LSICmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);

	// odaberi LSI kao RTC CLK
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
	RCC_RTCCLKCmd(ENABLE);
	RTC_WaitForSynchro();

	// RTC prescaler
	RTC_InitTypeDef	RTC_InitStruct;
	RTC_InitStruct.RTC_HourFormat = RTC_HourFormat_24;
	// treba iako je default, inace divlja
	RTC_InitStruct.RTC_AsynchPrediv = (uint32_t)0x7F;	// default
	RTC_InitStruct.RTC_SynchPrediv = (uint32_t)0xFF; 	// default
	RTC_Init(&RTC_InitStruct);

	// kad je postavljen clock
	rtc_setup = RTC_SETUP_DONE;
	//RTC_WriteBackupRegister(RTC_BKP_DR0, 1);
	RTC_WriteBackupRegister(RTC_BKP_DR0, RTC_SETUP_DONE);
	status = RTC_ReadBackupRegister(RTC_BKP_DR0);	// zapisi da je RTC postavljen
	printf("rtc status: %d\n", status);
}

//void rtc_get_time()
RTC_data_t *rtc_get_time()
{
	RTC_TimeTypeDef	RTC_TimeStruct;
	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);

	uint8_t rtc_h = RTC_TimeStruct.RTC_Hours;
	uint8_t rtc_m = RTC_TimeStruct.RTC_Minutes;
	uint8_t rtc_s = RTC_TimeStruct.RTC_Seconds;

	// spremi u globalni struct da ostatak programa moze koristit
	RTC_data.hours = rtc_h;
	RTC_data.minutes = rtc_m;
	RTC_data.seconds = rtc_s;

	//printf("RTC: %d %d %d\n", rtc_h, rtc_m, rtc_s);
	return &RTC_data;
}

void rtc_set_time(uint8_t h, uint8_t m, uint8_t s)
{
	RTC_TimeTypeDef	RTC_TimeStruct;
	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);

	RTC_TimeStruct.RTC_Hours	= h;
	RTC_TimeStruct.RTC_Minutes	= m;
	RTC_TimeStruct.RTC_Seconds	= s;


	RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct);



}
