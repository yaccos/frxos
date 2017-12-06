#ifndef TYPES_H_
#define TYPES_H_

#include <stddef.h>
#include <stdint.h>

struct register_frame {
  uint32_t edi;
  uint32_t esi;
  uint32_t ebp;
  uint32_t esp;
  uint32_t ebx;
  uint32_t edx;
  uint32_t ecx;
  uint32_t eax;
} __attribute__((packed));

/**
 * Full (standard) interrupt frame, after the following have been pushed to stack (in order):
 *  - EFLAGS, CS and EIP (automatically by interrupt)
 *  - Error code (automatically or dummy code)
 *  - INT/IRQ number
 *  - EAX, ECX, EDX, ESP (at interrupt), EBP, ESI and EDI
 *  - GS, FS, ES, DS and SS
**/
struct full_interrupt_frame {
  uint32_t gs, fs, es, ds, ss;
  uint32_t edi, esi, ebp, esp;
  uint32_t ebx, edx, ecx, eax;
  uint32_t num;
  uint32_t err_code;
  uint32_t eip;
  uint32_t cs;
  uint32_t eflags;
} __attribute__((packed));

#endif // TYPES_H_
