.include "src/pushxl.inc.s"

.section .text
  # interrupt handler for debug interrupt
  .global debug_int_handler
  debug_int_handler:
    cli
    pushl $0
    pushl $0
    pushxl

    movl %esp, %eax
    pushl %eax

    call debug_dump_state

    addl $4, %esp
    popxl
    addl $8, %esp

    iret
