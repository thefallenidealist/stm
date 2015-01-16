#include "clock_print.h"

void clock_print(void)
{
	printf("----- clock print: ---------------------------------\n");
	RCC_ClocksTypeDef RCC_ClocksStatus;
	RCC_GetClocksFreq(&RCC_ClocksStatus);

	printf("SystemCoreClock: %lu MHz\n", SystemCoreClock/1000000);
	printf("define HSI: %lu MHz\n", HSI_VALUE/1000000);
	printf("define HSE: %lu MHz\n", HSE_VALUE/1000000);

	// vrijednosti iz structa RCC_ClocksStatus
	printf("RCC_ClocksStatus.SYSCLK_Frequency:\t%lu MHz\n", RCC_ClocksStatus.SYSCLK_Frequency/1000000);
	printf("RCC_ClocksStatus.HCLK_Frequency:\t%lu MHz\n", 	RCC_ClocksStatus.HCLK_Frequency/1000000);
	printf("RCC_ClocksStatus.PCLK1_Frequency:\t%lu MHz\n",	RCC_ClocksStatus.PCLK1_Frequency/1000000);
	printf("RCC_ClocksStatus.PCLK2_Frequency:\t%lu MHz\n",	RCC_ClocksStatus.PCLK2_Frequency/1000000);

	uint8_t rcc_source = RCC_GetSYSCLKSource();
	printf("RCC Sys clk source [0 - HSI, 4 - HSE, 8 - PLL]: %d\n", rcc_source);

	printf("----------------------------------------------------\n");
}
