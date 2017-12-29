#ifndef PORT_IO_H_
#define PORT_IO_H_

#include <types.h>

#ifndef __cplusplus
#error Trying to include C++ header in non-C++ code
#endif

namespace frxos {
  using port_t = uint16_t;

  static inline void outb(port_t port, uint8_t value) {
    asm volatile("outb %0, %1" :: "a"(value), "Nd"(port));
  }

  static inline uint8_t inb(port_t port) {
    uint8_t value;
    asm volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
  }

  static inline void io_wait() {
    asm volatile("outb %%al, $0x80" :: "a"(0));
  }
}

#endif // PORT_IO_H_
