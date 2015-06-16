// XXX	moguci zajeb sa clang libovima

#include "clang_patch.h"


// treba za strncpy, IIRC
void __aeabi_memset(void *dest, char c, size_t n)
{
	memset(dest, c, n);
}

// odjednom treba za USART_SendData(string)
/*
void __aeabi_memcpy(void *dest, char c, size_t n)
{
	memcpy(dest, c, n);
}
*/

void __aeabi_memcpy(void *dest, const void *src, size_t n)
{
	memcpy(dest, src, n);
}
 
void __aeabi_memcpy4(void *dest, const void *src, size_t n)
{
	memcpy(dest, src, n);
}
 
void __aeabi_memclr(void *dest, size_t n)
{
	memset(dest, 0, n);
}
 
void __aeabi_memclr4(void *dest, size_t n)
{
	memset(dest, 0, n);
}
