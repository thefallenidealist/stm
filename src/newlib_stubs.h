#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <unistd.h> 	// STDIN_FILENO

#ifdef STM32F10X_MD
	#include "stm32f10x_usart.h"
#endif
#ifdef STM32F4XX
	#include "stm32f4xx_usart.h"
#endif

   		// TODO		ne moze pokupit define iz drugog fajla jer build sistem ne radi tako
#ifndef STDOUT_USART
  #define STDOUT_USART 1
  //#define STDOUT_USART 3
#endif

#ifndef STDERR_USART
  #define STDERR_USART 1
  //#define STDERR_USART 3
#endif

#ifndef STDIN_USART
  #define STDIN_USART 1
  //#define STDIN_USART 3
#endif


#undef errno
extern int errno;
