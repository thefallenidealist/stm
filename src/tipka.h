#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
//#include "misc.h"           // NVIC
//#include "stm32f4xx_exti.h"
//#include "stm32f4xx_syscfg.h"

void tipka_init();
//uint8_t tipka_read(uint8_t tipka);
uint8_t tipka_read(void);
//void EXTI0_IRQHandler(void);
