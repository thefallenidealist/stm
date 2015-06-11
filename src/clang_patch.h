#ifndef CLANG_PATCH_H
#define CLANG_PATCH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>

void __aeabi_memset(void *dest, char c, size_t n);
void __aeabi_memcpy(void *dest, const void *src, size_t n);
void __aeabi_memcpy4(void *dest, const void *src, size_t n);
void __aeabi_memclr(void *dest, size_t n);
void __aeabi_memclr4(void *dest, size_t n);
void __aeabi_memset(void *dest, char c, size_t n);

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif	// CLANG_PATCH_H
