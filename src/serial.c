#include "serial.h"

#include <stddef.h>
#include <stdint.h>

#include "io.h"

void serial_init(int port) {
  outb(port + 1, 0x00);    // Disable all interrupts
  outb(port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
  outb(port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
  outb(port + 1, 0x00);    //                  (hi byte)
  outb(port + 3, 0x03);    // 8 bits, no parity, one stop bit
  outb(port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
  outb(port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

static int serial_received(int port ) {
  return inb(port + 5) & 1;
}

char serial_getch(int port) {
  while(serial_received(port) == 0);
  return inb(port);
}

static int serial_is_transmit_empty(int port) {
  return inb(port + 5) & 0x20;
}

void serial_putch(int port, char ch) {
  while(serial_is_transmit_empty(port) == 0);
  outb(port, ch);
}

void serial_write(int port, void *data, uint32_t size) {
  char *cdata = (char*)data;
  for(uint32_t i = 0; i < size; i++)
    serial_putch(port, cdata[i]);
}

void serial_print(int port, const char *str) {
  for(const char *p = str; *p; p++)
    serial_putch(port, *p);
}
