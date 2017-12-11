#ifndef MEMORY_H_
#define MEMORY_H_

#include <stddef.h>
#include <stdint.h>

#include "attr.h"

#include "multiboot.h"

#ifdef __cplusplus
extern "C" {
#endif

// initialize memory manager
void install_memmgr(multiboot_info_t *mbinfo);

#ifdef __cplusplus
}
#endif

#endif // MEMORY_H_
