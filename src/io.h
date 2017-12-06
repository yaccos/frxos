#ifndef IO_H_
#define IO_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((always_inline))
static inline void outb(uint16_t port, uint8_t val) {
  asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

__attribute__((always_inline))
static inline uint8_t inb(uint16_t port) {
  uint8_t ret;
  asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
  return ret;
}

__attribute__((always_inline))
static inline void io_wait(void)
{
  asm volatile ( "outb %%al, $0x80" : : "a"(0) );
}

#ifdef __cplusplus
}
#endif

#endif // IO_H_
