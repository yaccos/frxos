#ifndef IDT_H_
#define IDT_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define IDT_SIZE 256

/**
 * Full (standardized) interrupt frame, after the following have been
 * pushed to stack (in order):
 *  - EFLAGS, CS and EIP (automatically by interrupt)
 *  - Error code (automatically or dummy code)
 *  - INT/IRQ number
 *  - EAX, ECX, EDX, EBX, ESP (at interrupt), EBP, ESI and EDI
 *  - SS, DS, ES, FS, GS
**/
struct full_interrupt_frame {
  uint32_t gs, fs, es, ds, ss; // segment registers
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // general purpose registers
  uint32_t no; // interrupt/IRQ number
  uint32_t err_code; // exception error code, or 0
  uint32_t eip, cs, eflags; // registers pushed by interrupt
};

void install_idt();

void load_idt_entry(uint8_t num, void (*func)(), uint16_t selector, uint8_t flags);
#define load_idt_func(num, name) \
  do { \
    extern void name(); \
    load_idt_entry(num, &name, 0x08, 0x8E); \
  } while(0)

#ifdef __cplusplus
}
#endif

#endif // IDT_H_
