#include "memory.h"

#include <stddef.h>
#include <stdint.h>

#include "debug.h"

#include "multiboot.h"

extern const char __kernel_start;
extern const char __kernel_end;

// lower and upper addresses of heap
static void *heap_lower = 0;
static void *heap_upper = 0;

void install_memmgr(multiboot_info_t *mbinfo) {
  dprintf("Installing memory manager\n");

  heap_lower = (void*)&__kernel_end;
  heap_upper = (void*)(1048576 + mbinfo->mem_upper);

  dprintf("Heap range: 0x%08X - 0x%08X (%d bytes)\n", heap_lower, heap_upper, (uint32_t)(heap_upper - heap_lower));
}
