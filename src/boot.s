.extern kernel_main

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
  .global __stack_top
  .global __stack_bottom
  .align 16
  __stack_bottom:
    .skip 4096 # 4k stack
  __stack_top:

# read-only data
.section .rodata

# writable data
.section .data

# code
.section .text
  .global __start
  .global kernel_halt

  __start:
    # disable interrupts
    cli

    # initialize stack
    movl $__stack_top, %esp
    movl %esp, %ebp

    # push to stack:
    pushl %ebx     # pointer to multiboot information struct
    pushl %eax     # multiboot magic word

    # call C constructors
    #call _init

    # call kernel initializer
    call kernel_init

    # call kernel main()
    sti
    call kernel_main
    cli

    # cleanup / halt kernel
    movl $0, %ecx
    jmp kernel_halt
  # ** end of __start **


    # ECX gives pointer to exit message (may be null)
  kernel_halt:
    # call kernel finalizer
    call kernel_fini

    # call C destructors
    #call _fini

  __kernel_halt_loop:
    # enter infinite loop
    cli                     # disable hardware interrupts
    hlt                     # wait for interrupts
    jmp __kernel_halt_loop  # if interrupt
