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

struct interrupt_frame {
  uint32_t eip;
  uint32_t cs;
  uint32_t eflags;
} __attribute__((packed));

struct fault_frame {
  struct register_frame regs;
  uint32_t int_no;
  uint32_t err_code;
  struct interrupt_frame inf;
} __attribute__((packed));

#endif // TYPES_H_
