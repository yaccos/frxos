#include "kernel.h"

#include <types.h>

#include "serial.h"
#include "debug.h"
using namespace frxos;

extern "C"
void kernel_init() {
  serial::install_all();
}

extern "C"
void kernel_main() {
  debug::print_all("hello!\n", "world!\n");
}

extern "C"
void kernel_fini() {
}
