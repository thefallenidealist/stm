// created 141206
#include "stm32f10x.h"
#include <stdint.h>

extern uint32_t _stack_end;
extern uint32_t _ebss;
extern uint32_t _sbss;

void C_Reset_Handler()
{
	uint32_t *source, *destination;

	// copy from flash to RAM

	// zeroing bss
	for(destination = &_sbss; destination < &_ebss ; )
	{
		(*destination++) = 0;
	}

	// aaaaan, we're done
	main();
}
