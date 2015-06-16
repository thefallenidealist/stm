#include "mem.h"

#ifdef STM32F1
// TODO napravit za mali ARM
#error mem_info() not implemented for STM32F1
#endif

// #defined in linker script
extern int _ebss;
extern int _sbss;
extern int _etext;
extern int _sdata;
extern int _edata;
//extern int sram;
#ifdef STM32F4
	extern int _estack;	// F4
	extern int _text;	// F4
	extern int flash_used_size;	// F4
#endif

void mem_info()
{
	DEBUG_START;

	uint32_t stackp = __get_MSP();

	uint32_t estack = (uint32_t)&_estack;
	uint32_t stack_size = estack - stackp;
	uint32_t bss_end   = (uint32_t)&_ebss;
	uint32_t bss_start = (uint32_t)&_sbss;
	uint32_t text_start = (uint32_t)&_text;
	uint32_t text_end = (uint32_t)&_etext;
	uint32_t data_start = (uint32_t)&_sdata;
	uint32_t data_end = (uint32_t)&_edata;

	printf("flash used size: %.1f kB\n", (uint32_t)&flash_used_size/1024.0);
    printf("RAM starts at: 0x%x\n", SRAM_BASE);  // defined in ST libs
    printf("RAM bit bang starts at: 0x%x\n", SRAM_BB_BASE);  // defined in ST libs


	printf("\n");
	printf("TEXT start: 0x%x\n", text_start);
	printf("TEXT end:   0x%x\n", text_end);
	printf("TEXT size:  %.1f kB\n", (text_end-text_start)/1024.0);

	printf("\n");
    uint32_t bss_size = bss_end - bss_start;
	printf("BSS start: 0x%x\n", bss_start);
	printf("BSS end:   0x%x\n", bss_end);
    if (bss_size >= 1024)
    {
        printf("BSS size:  %.1f kB\n", (bss_end-bss_start)/1024.0);
    }
    else
    {
	    printf("BSS size:  %d B\n", bss_end-bss_start);
    }

	printf("\n");
	printf("DATA start: 0x%x\n", data_start);
	printf("DATA end:   0x%x\n", data_end);
	printf("DATA size:  %.1f kB\n", (data_end-data_start)/1024.0);

	printf("\n");
	printf("stack pointer:   0x%x\n", stackp);
	printf("stack end:       0x%x\n", estack);
	//printf("remaining stack: 0x%x %dB\n", stack_size, stack_size);
	printf(ANSI_COLOR_CYAN "remaining stack: 0x%x %dB\n" ANSI_COLOR_RESET, stack_size, stack_size);
	printf("heap velicina: %.1f kB\n", (estack - bss_end)/1024.0);

	DEBUG_END;
	printf("\n");
}

void malloc_test()
{
	uint32_t *ptr;
	uint8_t counter_kb = 0;

	//for (int i=0;i<20; i++)
	for (int i=0; i<200; i++)
	{
		ptr = malloc(1024);	// probaj uzet 1kB
		if (ptr == NULL)
		{
			printf("malloc failed\n");
			break;
		}
		else
		{
			counter_kb++;
			printf("malloc uzeo 1kB, sto je ukupno %d: \tadresa: %p\n", counter_kb, ptr, ptr);
		}
	}
}


// eksperiment
/*
       const char *polje[16] =         {"PB0", "PB1", "PB2"};
    static const char *polje2[16] = {"PB0", "PB1", "PB3"};

    printf("addresa polja: %p\n", &polje[0]);   // 0x2001ff9c   stack
    printf("addresa polja: %p\n", &polje[1]);   // 0x2001ffa0
    printf("addresa polja: %p\n", &polje2[0]);  // 0x20000000   pocetak RAMa, DATA segment
    printf("addresa polja: %p\n", &polje2[1]);  // 0x20000004

    for (int i=0; i<3; i++)
    {
        printf("%s\n", polje[i]);
        printf("%s\n", polje2[i]);
        //led_init(polje[i]);
    }

    // stack pointer: 0x2001ff70, remaining: 144B

    const char nesto[] = {1,2,3,4,5,6,7,8,9,0};
    // nece kompajlirat:
    printf("adresa nesto0: %x\n" &(uint32_t)nesto[0]);
    //printf("adresa nesto1: %x\n" &nesto[1]);


 */

    /*
    extern int Reset_Handler;
    extern int NMI_Handler;
    extern intptr_t HardFault_Handler;
    extern intptr_t EXTI1_IRQHandler;
    extern intptr_t Default_Handler;

    //printf("SYSTick: %p\n" &SysTick_Handler);
    printf("UART1: %p\n", &USART1_IRQHandler);
    printf("EXTI0: %p\n", &EXTI0_IRQHandler);
    printf("EXTI1: %p\n", &EXTI1_IRQHandler);
    printf("RESET: %p\n", &Reset_Handler);
    printf("NMI:   %p\n", &NMI_Handler);
    printf("hard:  %p\n", &HardFault_Handler);
    printf("def:   %p\n", &Default_Handler);
    */

void print_remaining_stack(void)
{
	uint32_t stackp = __get_MSP();
	uint32_t estack = (uint32_t)&_estack;
	uint32_t stack_size = estack - stackp;

	printf("stack pointer:   0x%x\n", stackp);
	printf("stack end:       0x%x\n", estack);
	//printf("remaining stack: 0x%x %dB\n", stack_size, stack_size);
	printf(ANSI_COLOR_CYAN "remaining stack: 0x%x %dB\n" ANSI_COLOR_RESET, stack_size, stack_size);
}

