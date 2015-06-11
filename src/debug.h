#ifndef DEBUG_H
#define DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "colors_ansi.h"

#ifdef DEBUG
//	#define DEBUG_START			printf(ANSI_COLOR_BLUE "%s() start\n" ANSI_COLOR_RESET, __func__);
	#define DEBUG_START			;
//	#define DEBUG_END			printf(ANSI_COLOR_BLUE "%s() end\n"   ANSI_COLOR_RESET, __func__);
	#define DEBUG_END			;
	#define DEBUG_INFO( arg )	printf(ANSI_COLOR_YELLOW "%s() %s"   ANSI_COLOR_RESET, __func__, arg);
	#define ERROR( arg )		printf(ANSI_COLOR_RED "ERROR %s(), " ANSI_COLOR_RESET \
								"file: %s, line: %d: " \
								ANSI_COLOR_RED  "%s" ANSI_COLOR_RESET, \
								__func__, __FILE__, __LINE__, arg);
#else
	#define DEBUG_START			;
	#define DEBUG_END			;
	#define DEBUG_INFO( arg )	;
	#define ERROR( arg )		;
#endif

extern uint8_t debug_level;

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif	// DEBUG_H
