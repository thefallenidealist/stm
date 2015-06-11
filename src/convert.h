// created 150213
#ifndef CONVERT_H
#define CONVERT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

uint8_t  dec2bcd	(uint8_t dec);
void 	 dec2bin8	(uint8_t arg);
uint8_t *dec2bin8_str(uint8_t arg);

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif	// CONVERT_H
