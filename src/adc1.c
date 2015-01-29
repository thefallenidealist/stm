// jednostavni ADC
#include "adc1.h"

// XXX ne radi na F4

// *************************************** variables **********************************************

// *************************************** function prototypes ************************************

// *************************************** example ************************************************
void ADC_example(void)
{
	printf("ADC_example(void)\n");
	ADC_init(void);
	ADC_TempSensorVrefintCmd(ENABLE);	// enable internal temperature sensor

	delay_ms(1);	// treba mu malo da nadodje
	uint16_t tempraw = ADC_read(16);
	printf("ADC16: %d\n", tempraw);
}

void ADC_init(void)
{
	ADC_InitTypeDef  ADC_InitStructureure;
	// PCLK2 is the APB2 clock 
	// ADCCLK = PCLK2/6 = 72/6 = 12MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_DeInit(ADC1);

	// ADC1 Configuration ------------------------------------------------------
	// ADC1 and ADC2 operate independently 
	ADC_InitStructureure.ADC_Mode = ADC_Mode_Independent;
	// Disable the scan conversion so we do one at a time 
	ADC_InitStructureure.ADC_ScanConvMode = DISABLE;
	// Don't do contimuous conversions - do them on demand 
	ADC_InitStructureure.ADC_ContinuousConvMode = DISABLE;
	// Start conversin by software, not an external trigger 
	ADC_InitStructureure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	// Conversions are 12 bit - put them in the lower 12 bits of the result 
	ADC_InitStructureure.ADC_DataAlign = ADC_DataAlign_Right;
	// Say how many channels would be used by the sequencer 
	ADC_InitStructureure.ADC_NbrOfChannel = 1;

	// Now do the setup 
	ADC_Init(ADC1, &ADC_InitStructureure);
	// Enable ADC1 
	ADC_Cmd(ADC1, ENABLE);

	// Enable ADC1 reset calibaration register 
	ADC_ResetCalibration(ADC1);
	// Check the end of ADC1 reset calibration register 
	while (ADC_GetResetCalibrationStatus(ADC1));
	// Start ADC1 calibaration 
	ADC_StartCalibration(ADC1);
	// Check the end of ADC1 calibration 
	while (ADC_GetCalibrationStatus(ADC1));
}

uint16_t ADC_read(uint8_t channel)
{
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_1Cycles5);
	// Start the conversion
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	// Wait until conversion completion
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	// Get the conversion value
	return ADC_GetConversionValue(ADC1);
}
