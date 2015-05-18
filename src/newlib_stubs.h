#ifndef NEWLIB_STUBS_H
#define NEWLIB_STUBS_H

#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <unistd.h> 	// STDIN_FILENO

#if defined STM32F10X_MD || defined STM32F1
	#include "stm32f10x_usart.h"
#endif
#if defined STM32F4XX || defined STM32F4
	#include "stm32f4xx_usart.h"
#endif

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

int _close(int file);
int _execve(char *name, char **argv, char **env);
int _fork(void);
int _fstat(int file, struct stat *st);
int _getpid(void);
int _isatty(int file);
int _kill(int pid, int sig);
int _link(char *old, char *new);
int _lseek(int file, int ptr, int dir);
caddr_t _sbrk(int incr);
int _read(int file, char *ptr, int len);
int _stat(const char *filepath, struct stat *st);
clock_t _times(struct tms *buf);
int _unlink(char *name);
int _wait(int *status);


#endif
