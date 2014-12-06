//
#define ARRAYSIZE 800
volatile uint32_t status = 0;
volatile uint32_t i;

void dma2()
{
	//initialize source and destination arrays
	uint32_t source[ARRAYSIZE];
	uint32_t destination[ARRAYSIZE];
	//initialize array
	for (i=0; i<ARRAYSIZE;i++)
	    source[i]=i;
	//initialize led
	//LEDsInit();
	//enable DMA1 clock


	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	//create DMA structure
	DMA_InitTypeDef  DMA_InitStructure;
	//reset DMA1 channe1 to default values;
	DMA_DeInit(DMA1_Channel1);
	//channel will be used for memory to memory transfer
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
	//setting normal mode (non circular)
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	//medium priority
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	//source and destination data size word=32bit
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	//automatic memory increment enable. Destination and source
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	//Location assigned to peripheral register will be source
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	//chunk of data to be transfered
	DMA_InitStructure.DMA_BufferSize = ARRAYSIZE;
	//source and destination start addresses
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)source;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)destination;
	//send values to DMA registers
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	// Enable DMA1 Channel Transfer Complete interrupt
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
	NVIC_InitTypeDef NVIC_InitStructure;
	//Enable DMA1 channel IRQ Channel */
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//LED on before transfer
	//LEDToggle(LEDG);
	//Enable DMA1 Channel transfer
	DMA_Cmd(DMA1_Channel1, ENABLE);
printf("\t\t\t\t\t\tDMA debug\n");
led("PB12", 2);
	while(status==0) {};
	    //LEDToggle(LEDB);
	    for (i=0; i<ARRAYSIZE;i++)
	    {
		destination[i]=source[i];
	    }
	    //LEDToggle(LEDB);
}


void DMA1_Channel1_IRQHandler(void)
{
	//Test on DMA1 Channel1 Transfer Complete interrupt
	if(DMA_GetITStatus(DMA1_IT_TC1))
	{
		//status=1;
		//LEDToggle(LEDG);
		//Clear DMA1 Channel1 Half Transfer, Transfer Complete and Global interrupt pending bits
		DMA_ClearITPendingBit(DMA1_IT_GL1);
	}
}
