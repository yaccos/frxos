#ifndef KB_H_
#define KB_H_

#include <stddef.h>
#include <stdint.h>

#include "interrupt.h"

void install_keyboard();

extern void _isr_kb1();

#endif // KB_H_
