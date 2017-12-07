.extern __debug_mode

.section .data
  .global in_debug_mode
  .global leave_debug_mode

    .align 4
  in_debug_mode:
    .byte 0
  leave_debug_mode:
    .byte 0
    .align 4

.section .text
  .global enter_debug_mode
  enter_debug_mode:
    movb in_debug_mode, %al
    orb $0, %al
    jnz __enter_debug_mode__leave

  __enter_debug_mode__enter:
    movl 4(%esp), %eax
    pushl %eax

    sti
    call __debug_mode
    cli

    addl $4, %esp
    jmp __enter_debug_mode__end

  __enter_debug_mode__leave:
    movb $1, leave_debug_mode

  __enter_debug_mode__end:
    ret
