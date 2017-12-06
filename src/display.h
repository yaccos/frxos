#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

void install_display();

uint16_t get_vga_cols();
uint16_t get_vga_rows();
uint16_t get_vga_size();

void vga_fill(uint16_t ch);
static inline void vga_reset() { vga_fill(0); }

void vga_move_cursor(uint8_t row, uint8_t col);
void vga_enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void vga_disable_cursor();

void vga_putch(uint8_t row, uint8_t col, uint16_t ch);

void vga_readb(uint8_t row, uint8_t col, uint16_t *data, uint16_t size);
void vga_writeb(uint8_t row, uint8_t col, const uint16_t *data, uint16_t size);

void vga_write(uint8_t row, uint8_t col, uint16_t color, const char *data, uint16_t size);
void vga_printf(uint8_t row, uint8_t col, uint16_t color, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif // DISPLAY_H_
