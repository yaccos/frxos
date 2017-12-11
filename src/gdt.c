#include "gdt.h"

#include <stddef.h>
#include <stdint.h>

#include "attr.h"
// #include "debug.h"

#define GDT_SIZE 3

struct gdt_entry {
  uint16_t limit_lo;
  uint16_t base_lo;
  uint8_t  base_mid;
  uint8_t  access;
  uint8_t  granularity;
  uint8_t  base_hi;
} __packed;

struct gdt_pointer {
  uint16_t limit;
  struct gdt_entry *base;
} __packed;

void load_gdt_entry(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);

static struct gdt_entry gdt[GDT_SIZE] = { 0 };
static struct gdt_pointer gdt_ptr;

extern void load_gdt(struct gdt_pointer*);

void install_gdt() {
  gdt_ptr.limit = (sizeof(struct gdt_entry) * GDT_SIZE) - 1;
  gdt_ptr.base = &gdt;

  // NULL entry
  load_gdt_entry(0, 0, 0, 0, 0);
  
  // code segment
  load_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  
  // data segment
  load_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

  load_gdt(&gdt_ptr);
}

void load_gdt_entry(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
  gdt[num].base_lo  = (base & 0xFFFF);
  gdt[num].base_mid = (base >> 16) & 0xFF;
  gdt[num].base_hi  = (base >> 24) & 0xFF;
  gdt[num].limit_lo = (limit & 0xFFFF);
  gdt[num].granularity = ((limit >> 16) & 0x0F) | (granularity & 0xF0);
  gdt[num].access = access;
}
