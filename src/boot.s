# multiboot header
.set MB_MAGIC, 0x1BADB002
.set MB_FLAGS, 3 # 1: load modules on page boundaries, 2: provide a memory map
.set MB_CHECKSUM, (0 - (MB_MAGIC + MB_FLAGS))

.section .multiboot
  .align 4
  .long MB_MAGIC
  .long MB_FLAGS
  .long MB_CHECKSUM

# stack
.section .bss
  .global _stack_top
  .global _stack_bottom
  .align 16
  _stack_bottom:
    .skip 4096 # 4k stack
  _stack_top:

# read-only data
.section .rodata

# data
.section .data

# code
.section .text
  .extern kernel_main
  .global _start

  _start:
    # disable interrupts
    cli

    # initialize stack
    movl $_stack_top, %esp
    movl %esp, %ebp

    # call static constructors
    call _init

    # call main function
    call kernel_main

    # call static deconstructor
    call _fini

  .global kernel_halt
  kernel_halt:
  _halt:
    cli
    hlt
    jmp _halt
