#ifndef DEBUG_H_
#define DEBUG_H_

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "types.h"

/**
 * dprintf(format, ...)
 * 
 *  Print to message standard debugging output.
**/
void dprintf(const char *format, ...);

/**
 * debug()
 * 
 * Force a debug exception (exception #1)
**/
#define debug() asm("int $1")

/**
 * brk()
 * 
 * Force a breakpoint exception (exception #3)
**/
#define brk() asm("int $3")

void dump_fault_state(struct fault_frame *frame);

#endif // DEBUG_H_
