#include "mem.h"

// #defined in linker script
extern int _estack;
extern int _estack;
extern int _ebss;

void mem_info()
{
	uint32_t stackp = __get_MSP();

	uint32_t estack = (uint32_t)&_estack;
	uint32_t bss_end   = (uint32_t)&_ebss;
	uint32_t stack_size = estack - stackp;

	printf("stack pointer  = 0x%x\n", stackp);
	printf("stack end      = 0x%x\n", estack);
	printf("remaining stack: 0x%x %dB\n", stack_size, stack_size);

	printf("BSS end: 0x%x\n", _ebss);
	printf("heap velicina: %.1f kB\n", (estack - bss_end)/1024.0);
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
