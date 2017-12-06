#ifndef DEBUG_H_
#define DEBUG_H_

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

void dprintf(const char *format, ...);

#define debug() asm("int $0x7E");
#define brk()   asm("int $0x7F");

#ifdef __cplusplus
}
#endif

#endif // DEBUG_H_
