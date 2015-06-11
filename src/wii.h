// created 150128
#ifndef WII_H
#define WII_H

#ifdef __cplusplus
extern "C" {
#endif

#include "i2c.h"
#include "debug.h"
#include "delay.h"

void wii_init();
void wii_read();
void wii_read_start();

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif	// WII_H
