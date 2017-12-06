.extern fault_handler
.extern kernel_halt

.section .text
  _fault_common_stub:
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

    // call fault handler
    call fault_handler

    // clear stack frame
    addl $4, %esp
    popl %gs
    popl %fs
    popl %es
    popl %ds
    popl %ss
    popal
    addl $8, %esp

    // halt kernel
    jmp kernel_halt
    iret

  _isr0:
    pushl $0
    pushl $0
    jmp _fault_common_stub

  _isr1:
    pushl $0
    pushl $1
    jmp _fault_common_stub

  _isr2:
    pushl $0
    pushl $2
    jmp _fault_common_stub

  _isr3:
    pushl $0
    pushl $3
    jmp _fault_common_stub

  _isr4:
    pushl $0
    pushl $4
    jmp _fault_common_stub

  _isr5:
    pushl $0
    pushl $5
    jmp _fault_common_stub

  _isr6:
    pushl $0
    pushl $6
    jmp _fault_common_stub

  _isr7:
    pushl $0
    pushl $7
    jmp _fault_common_stub

  _isr8:
    // error code pushed to stack
    pushl $8
    jmp _fault_common_stub

  _isr9:
    pushl $0
    pushl $9
    jmp _fault_common_stub

  _isr10:
    // error code pushed to stack
    pushl $10
    jmp _fault_common_stub

  _isr11:
    // error code pushed to stack
    pushl $11
    jmp _fault_common_stub

  _isr12:
    // error code pushed to stack
    pushl $12
    jmp _fault_common_stub

  _isr13:
    // error code pushed to stack
    pushl $13
    jmp _fault_common_stub

  _isr14:
    // error code pushed to stack
    pushl $14
    jmp _fault_common_stub

  _isr15:
    pushl $0
    pushl $15
    jmp _fault_common_stub

  _isr16:
    pushl $0
    pushl $16
    jmp _fault_common_stub

  _isr17:
    pushl $0
    pushl $17
    jmp _fault_common_stub

  _isr18:
    pushl $0
    pushl $18
    jmp _fault_common_stub

  _isr19:
    pushl $0
    pushl $19
    jmp _fault_common_stub

  _isr20:
    pushl $0
    pushl $20
    jmp _fault_common_stub

  _isr21:
    pushl $0
    pushl $21
    jmp _fault_common_stub

  _isr22:
    pushl $0
    pushl $22
    jmp _fault_common_stub

  _isr23:
    pushl $0
    pushl $23
    jmp _fault_common_stub

  _isr24:
    pushl $0
    pushl $24
    jmp _fault_common_stub

  _isr25:
    pushl $0
    pushl $25
    jmp _fault_common_stub

  _isr26:
    pushl $0
    pushl $26
    jmp _fault_common_stub

  _isr27:
    pushl $0
    pushl $27
    jmp _fault_common_stub

  _isr28:
    pushl $0
    pushl $28
    jmp _fault_common_stub

  _isr29:
    pushl $0
    pushl $29
    jmp _fault_common_stub

  _isr30:
    pushl $0
    pushl $30
    jmp _fault_common_stub

  _isr31:
    pushl $0
    pushl $31
    jmp _fault_common_stub

  .global _isr0
  .global _isr1
  .global _isr2
  .global _isr3
  .global _isr4
  .global _isr5
  .global _isr6
  .global _isr7
  .global _isr8
  .global _isr9
  .global _isr10
  .global _isr11
  .global _isr12
  .global _isr13
  .global _isr14
  .global _isr15
  .global _isr16
  .global _isr17
  .global _isr18
  .global _isr19
  .global _isr20
  .global _isr21
  .global _isr22
  .global _isr23
  .global _isr24
  .global _isr25
  .global _isr26
  .global _isr27
  .global _isr28
  .global _isr29
  .global _isr30
  .global _isr31
