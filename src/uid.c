#include "uid.h"

#if defined STM32F4 || defined STM32F4XX
	#define STM32_UID0	(*(uint32_t *) 0x1FFF7A10)
	#define STM32_UID1	(*(uint32_t *) 0x1FFF7A14)
	#define STM32_UID2	(*(uint32_t *) 0x1FFF7A18)
#endif
#if defined STM32F1 || defined STM32F10X_MD
	#define STM32_UID0	(*(uint32_t *) 0x1FFFF7E8)
	#define STM32_UID1	(*(uint32_t *) 0x1FFFF7EC)
	#define STM32_UID2	(*(uint32_t *) 0x1FFFF7F0)
#endif

#define FLASH_SIZE (*(uint16_t *)0x1FFF7A22)	// in kB

/*************************************************************************************************
				uid_get()
*************************************************************************************************/
char *uid_get(void)
{
	static char buffer[25] = {};
	snprintf(buffer, 25, "%08X%08X%08X\n", STM32_UID0, STM32_UID1, STM32_UID2);

	return buffer;
}

/*************************************************************************************************
				uid_example()
*************************************************************************************************/
void uid_example(void)
{
	char *uid = uid_get();
	printf("%s(), UID: %s\n", __func__, uid);
}
