#include <stdio.h>
#include <stdint.h>
#include "colors_ansi.h"

#define INFO_START printf(ANSI_COLOR_BLUE "%s() start\n" ANSI_COLOR_RESET, __func__);
#define INFO_END   printf(ANSI_COLOR_BLUE "%s() end\n"   ANSI_COLOR_RESET, __func__);

//uint8_t verbosity_level = 2;
extern uint8_t verbosity_level;
