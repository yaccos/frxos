#ifndef KERNEL_H_
#define KERNEL_H_

#include <stddef.h>
#include <stdint.h>

#include "attr.h"

#ifdef __cplusplus
extern "C" {
#endif

__fastcall
extern void kernel_halt(const char *message);

#ifdef __cplusplus
}
#endif

#endif // KERNEL_H_
