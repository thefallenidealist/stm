#ifndef CMD_H
#define CMD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
//#include "led.h"
#include "gpio.h"

#if defined STM32F4 || defined STM32F4XX
#include "sakupljac.h"	// XXX ne bi trebalo bit ovdje
#endif

void uart_cmd(char *cmd, char *arg);
void uart_parse(void);
void uart_parse_rtc(const char* arg);

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif	// CMD_H
