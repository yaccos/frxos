#include "display.h"

#include <stddef.h>
#include <stdint.h>

#include "debug.h"
#include "io.h"
#include "mini-printf.h"

volatile uint16_t *vga_buffer = (uint16_t*)0xB8000;
uint16_t VGA_COLS = 80;
uint16_t VGA_ROWS = 25;
#define VGA_SIZE ((uint16_t)(VGA_COLS * VGA_ROWS))

#define VGA_POS(row, col) ((uint16_t)(row) * VGA_COLS + (uint16_t)(col))

uint16_t get_vga_cols() { return VGA_COLS; }
uint16_t get_vga_rows() { return VGA_ROWS; }
uint16_t get_vga_size() { return VGA_COLS * VGA_ROWS; }

void install_display() {
  vga_fill(0x0F00);
  vga_disable_cursor();
  vga_move_cursor(0, 0);
}

void vga_fill(uint16_t ch) {
  for(uint16_t i = 0; i < VGA_SIZE; i++) {
    vga_buffer[i] = ch;
  }
}

void vga_move_cursor(uint8_t row, uint8_t col) {
  uint16_t pos = VGA_POS(row, col);
  
   outb(0x3D4, 0x0F);
   outb(0x3D5, (uint8_t) (pos & 0xFF));
   outb(0x3D4, 0x0E);
   outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
 
}

void vga_enable_cursor(uint8_t cursor_start, uint8_t cursor_end) {
  outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3E0) & 0xE0) | cursor_end);
}

void vga_disable_cursor() {
  outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void vga_putch(uint8_t row, uint8_t col, uint16_t ch) {
  uint16_t pos = VGA_POS(row, col);
  vga_buffer[pos] = ch;
}

void vga_readb(uint8_t row, uint8_t col, uint16_t *data, uint16_t size) {
  uint16_t pos = VGA_POS(row, col);
  for(uint16_t i = 0; i < size; i++)
    data[i] = vga_buffer[pos + i];
} 

void vga_writeb(uint8_t row, uint8_t col, const uint16_t *data, uint16_t size) {
  uint16_t pos = VGA_POS(row, col);
  for(uint16_t i = 0; i < size; i++)
    vga_buffer[pos + i] = data[i];
}

void vga_write(uint8_t row, uint8_t col, uint16_t color, const char *data, uint16_t size) {
  uint16_t pos = VGA_POS(row, col);

  for(uint16_t i = 0; i < size; i++) {
    const char ch = data[i];

    if(ch >= 0x20 && ch <= 0x7E)
      vga_buffer[pos++] = color | ch;
    else if(ch == '\n')
      pos += VGA_COLS - pos % VGA_COLS;
  }
}

void vga_printf(uint8_t row, uint8_t col, uint16_t color, const char *format, ...) {
  #define TMP_BUFFER_SIZE 4096 
  static char buffer[TMP_BUFFER_SIZE];

  va_list args;
  va_start(args, format);
  
  int len = mini_vsnprintf(buffer, TMP_BUFFER_SIZE, format, args);

  if(len > 0) {
    vga_write(row, col, color, buffer, len);
  }

  va_end(args);
  #undef TMP_BUFFER_SIZE
}
