.extern __debug_mode

.section .data
  in_debug_mode:
    .align 4
    .long 0
    .align 4

.section .text
  .global enter_debug_mode
  enter_debug_mode:
    movl in_debug_mode, %eax
    andl $0, %eax
    jnz __enter_debug_mode__end

    movl 4(%esp), %eax
    pushl %eax

    sti
    call __debug_mode
    cli

    addl $4, %esp
  __enter_debug_mode__end:
    ret
