#include "serial.h"

#include <types.h>

#include "port_io.h"
#include "timer.h"

namespace frxos {
  namespace serial {

    void install(uint16_t port) {
      outb(port + 1, 0x00);    // Disable all interrupts
      outb(port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
      outb(port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
      outb(port + 1, 0x00);    //                  (hi byte)
      outb(port + 3, 0x03);    // 8 bits, no parity, one stop bit
      outb(port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
      outb(port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    }

    static inline uint8_t has_received(port_t port) {
      return inb(port + 5) & 0x01;
    }

    static inline uint8_t is_transmit_empty(port_t port) {
      return inb(port + 5) & 0x20;
    }

    void putch(port_t port, uint8_t value) {
      WAIT_FOR( is_transmit_empty(port) );
      return outb(port, value);
    }

    uint8_t getch(port_t port) {
      WAIT_FOR( has_received(port) );
      return inb(port);
    }

    ssize_t write(port_t port, const void *data, size_t size) {
      const unsigned char *cdata = (const unsigned char*)data;
      for(size_t i = 0; i < size; i++)
        putch(port, (uint8_t)cdata[i]);
      return size;
    }

    ssize_t read(port_t port, void *data, size_t size) {
      unsigned char *cdata = (unsigned char*)data;
      for(size_t i = 0; i < size; i++)
        cdata[i] = getch(port);
      return size;
    }

    ssize_t print(port_t port, const char *str) {
      size_t i = 0;
      for(const char *ch = str; *ch != 0; ch++, i++)
        putch(port, (uint8_t)*ch);
      return i;
    }

  }
}
