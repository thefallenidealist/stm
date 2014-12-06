// created 140919

void dma_init();
#define ARRAYSIZE	1000
volatile uint32_t source[ARRAYSIZE];
volatile uint32_t destination[ARRAYSIZE];
volatile uint32_t status = 0;

void dma_main()
{
	volatile uint32_t a, b;

	a = get_uptime();
	for(int i=0; i<100; i++)
		{
		for (int i=0; i<ARRAYSIZE;i++)
		{
			source[i]=i;
		}
	}
	b = get_uptime();
	printf("ne DMA: %lu ms\n", b-a);


	dma_init();

	a = get_uptime();
	for(int i=0; i<100; i++)
	{
		DMA_Cmd(DMA1_Channel1, ENABLE);
		while(status==0) {};

		for (int i=0; i<ARRAYSIZE;i++)
		{
			destination[i]=source[i];
		}
	}
	b = get_uptime();

	printf("DMA: %lu ms\n", b-a);
}

void dma_init()
{
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
}

void DMA1_Channel1_IRQHandler(void)
{
	//Test on DMA1 Channel1 Transfer Complete interrupt
	//	status=1;
	if(DMA_GetITStatus(DMA1_IT_TC1))
	{
		status=1;
		//LEDToggle(LEDG);
		//Clear DMA1 Channel1 Half Transfer, Transfer Complete and Global interrupt pending bits
		DMA_ClearITPendingBit(DMA1_IT_GL1);
	}
}
