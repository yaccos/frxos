#ifndef DEBUG_H_
#define DEBUG_H_

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "idt.h"

#ifdef __cplusplus
extern "C" {
#endif

void dprintf(const char *format, ...);

#define debug() asm("int $0x7E");

extern void enter_debug_mode(struct full_interrupt_frame *frame);

#ifdef __cplusplus
}
#endif

#endif // DEBUG_H_
