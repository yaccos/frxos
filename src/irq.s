.extern irq_common_handler

.section .data
  .global __irq_return_ptr

    .align 4
  __irq_return_ptr: # pointer to function to call after IRQ returns
    .long 0

.section .text
  _irq_common_stub:
    // push all general-purpose and segment registers (except CS)
    pushal
    pushl %ss
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    // push pointer to stack
    movl %esp, %eax
    pushl %eax

    // reset __irq_return_ptr
    movl $0, __irq_return_ptr

    // call IRQ handler
    call irq_common_handler

    // clear stack frame
    addl $4, %esp
    popl %gs
    popl %fs
    popl %es
    popl %ds
    popl %ss
    popal
    addl $8, %esp

    // if __irq_return_ptr is non-zero, call function before returning from interrupt
    movl __irq_return_ptr, %eax
    cmp $0, %eax
    jz __irq_common_stub__end
    call *%eax

    // return from interrupt
  __irq_common_stub__end:
    iret

  _irq0:
    pushl $0
    pushl $0
    jmp _irq_common_stub

  _irq1:
    pushl $0
    pushl $1
    jmp _irq_common_stub

  _irq2:
    pushl $0
    pushl $2
    jmp _irq_common_stub

  _irq3:
    pushl $0
    pushl $3
    jmp _irq_common_stub

  _irq4:
    pushl $0
    pushl $4
    jmp _irq_common_stub

  _irq5:
    pushl $0
    pushl $5
    jmp _irq_common_stub

  _irq6:
    pushl $0
    pushl $6
    jmp _irq_common_stub

  _irq7:
    pushl $0
    pushl $7
    jmp _irq_common_stub

  _irq8:
    pushl $0
    pushl $8
    jmp _irq_common_stub

  _irq9:
    pushl $0
    pushl $9
    jmp _irq_common_stub

  _irq10:
    pushl $0
    pushl $10
    jmp _irq_common_stub

  _irq11:
    pushl $0
    pushl $11
    jmp _irq_common_stub

  _irq12:
    pushl $0
    pushl $12
    jmp _irq_common_stub

  _irq13:
    pushl $0
    pushl $13
    jmp _irq_common_stub

  _irq14:
    pushl $0
    pushl $14
    jmp _irq_common_stub

  _irq15:
    pushl $0
    pushl $15
    jmp _irq_common_stub

  .global _irq0
  .global _irq1
  .global _irq2
  .global _irq3
  .global _irq4
  .global _irq5
  .global _irq6
  .global _irq7
  .global _irq8
  .global _irq9
  .global _irq10
  .global _irq11
  .global _irq12
  .global _irq13
  .global _irq14
  .global _irq15
