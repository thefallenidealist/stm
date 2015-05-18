// created 150305
#include "cpu_id.h"

void print_cpu_id()
{
	uint32_t cpu_id = SCB->CPUID;
	uint8_t implementer = cpu_id >> 24;
	uint8_t variant 	= (cpu_id >> 20) & 0xF;
	uint8_t constant	= (cpu_id >> 16) & 0xF;
	uint16_t part		= (cpu_id >> 4)  & 0xFFF;
	uint8_t revision	= cpu_id & 0b1111;

	printf("CPU ID:      0x%X\n", cpu_id);
	printf("Implementer: 0x%X\n", implementer);
	printf("Variant:     0x%X\n", variant);
	printf("Constant:    0x%X\n", constant);
	printf("PartNo:      0x%X\n", part);
	printf("Revision:    0x%X\n", revision);

	if (constant == 0xF)
	{
		// M3 or M4
		if (part == 0xC23)
		{
			// M3
			if ( (variant == 0x0) && (revision == 0x0) )
			{
				printf("CPU core is Cortex-M3 r0p0\n");
			}
			else if ( (variant == 0x0) && (revision == 0x1) )
			{
				printf("CPU core is Cortex-M3 r1p0\n");
			}
			else if ( (variant == 0x1) && (revision == 0x1) )
			{
				printf("CPU core is Cortex-M3 r1p1\n");
			}
			else if ( (variant == 0x2) && (revision == 0x0) )
			{
				printf("CPU core is Cortex-M3 r2p0\n");
			}
			else if ( (variant == 0x2) && (revision == 0x1) )
			{
				printf("CPU core is Cortex-M3 r2p1\n");
			}

		}
		else if (part == 0xC24)
		{
			// M4
			if ( (variant == 0x0) && (revision == 0x0) )
			{
				printf("CPU core is Cortex-M4 r0p0\n");
			}
			else if ( (variant == 0x0) && (revision == 0x1) )
			{
				printf("CPU core is Cortex-M4 r0p1\n");
			}
		}

	}
	else if (constant == 0xC)
	{
		// M0, M0+ or M1
		if (part == 0xC20)
		{
			printf("CPU core is Cortex-M0 r0p0\n");
		}
		else if (part == 0xC60)
		{
			printf("CPU core is Cortex-M0+ r0p0\n");
		}
		
		if (part == 0xC21)	// M1
		{
			if ( (variant == 0x0) && (revision == 0x0) )
			{
				printf("CPU core is Cortex-M1 r0p0\n");
			}
			else if ( (variant == 0x0) && (revision == 0x1) )
			{
				printf("CPU core is Cortex-M1 r0p1\n");
			}
			else if ( (variant == 0x1) && (revision == 0x0) )
			{
				printf("CPU core is Cortex-M1 r1p0\n");
			}
		}
	}
	else
	{
		printf("Unknown CPU core\n");
	}
}

/*
int8_t get_cpu_id(void)
{
	uint32_t cpu_id 	= SCB->CPUID;
	uint8_t implementer = cpu_id >> 24;
	uint8_t variant 	= (cpu_id >> 20) & 0xF;
	uint8_t constant	= (cpu_id >> 16) & 0xF;
	uint16_t part		= (cpu_id >> 4)  & 0xFFF;
	uint8_t revision	= cpu_id & 0b1111;

	printf("CPU ID:      0x%X\n", cpu_id);
	printf("Implementer: 0x%X\n", implementer);
	printf("Variant:     0x%X\n", variant);
	printf("Constant:    0x%X\n", constant);
	printf("PartNo:      0x%X\n", part);
	printf("Revision:    0x%X\n", revision);

	if (constant == 0xF)
	{
		// M3 or M4
		if (part == 0xC23)
		{
			// M3
			if ( (variant == 0x0) && (revision == 0x0) )
			{
				//printf("CPU core is Cortex-M3 r0p0\n");
				return 3;
			}
			else if ( (variant == 0x0) && (revision == 0x1) )
			{
				//printf("CPU core is Cortex-M3 r1p0\n");
				return 3;
			}
			else if ( (variant == 0x1) && (revision == 0x1) )
			{
				//printf("CPU core is Cortex-M3 r1p1\n");
				return 3;
			}
			else if ( (variant == 0x2) && (revision == 0x0) )
			{
				//printf("CPU core is Cortex-M3 r2p0\n");
				return 3;
			}
			else if ( (variant == 0x2) && (revision == 0x1) )
			{
				//printf("CPU core is Cortex-M3 r2p1\n");
				return 3;
			}

		}
		else if (part == 0xC24)
		{
			// M4
			if ( (variant == 0x0) && (revision == 0x0) )
			{
				//printf("CPU core is Cortex-M4 r0p0\n");
				return 4;
			}
			else if ( (variant == 0x0) && (revision == 0x1) )
			{
				//printf("CPU core is Cortex-M4 r0p1\n");
				return 4;
			}
		}

	}
	else if (constant == 0xC)
	{
		// M0, M0+ or M1
		if (part == 0xC20)
		{
			//printf("CPU core is Cortex-M0 r0p0\n");
			return 0;
		}
		else if (part == 0xC60)
		{
			//printf("CPU core is Cortex-M0+ r0p0\n");
			return 0;
		}
		
		if (part == 0xC21)	// M1
		{
			if ( (variant == 0x0) && (revision == 0x0) )
			{
				//printf("CPU core is Cortex-M1 r0p0\n");
				return 1;
			}
			else if ( (variant == 0x0) && (revision == 0x1) )
			{
				//printf("CPU core is Cortex-M1 r0p1\n");
				return 1;
			}
			else if ( (variant == 0x1) && (revision == 0x0) )
			{
				//printf("CPU core is Cortex-M1 r1p0\n");
				return 1;
			}
		}
	}
}
*/
