#include "serial.h"

#include <stddef.h>
#include <stdint.h>

#include "io.h"

void install_serial(uint16_t port) {
  outb(port + 1, 0x00);    // Disable all interrupts
  outb(port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
  outb(port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
  outb(port + 1, 0x00);    //                  (hi byte)
  outb(port + 3, 0x03);    // 8 bits, no parity, one stop bit
  outb(port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
  outb(port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}
