// exceptions
.section .text
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

  .extern kernel_fault_handler
  .extern _halt
  _isr_exception_stub:
    pushal // push all registers
    addl $20, 12(%esp) // set stored ESP to ESP at interrupt

    // push pointer to stack
    movl %esp, %eax
    pushl %eax

    // call fault handler
    movl $0, %eax
    call kernel_fault_handler

    // if kernel_fault_handler() returned non-zero, then 
    // halt
    cmp $0, %eax
    jne _halt

    // clear stack
    popl %eax
    popal
    addl $8, %esp

    // return from interrupt
    iret

  _isr0:
    cli
    pushl $0 // dummy error code
    pushl $0 // interrupt number
    jmp _isr_exception_stub

  _isr1:
    cli
    pushl $0 // dummy error code
    pushl $1 // interrupt number
    jmp _isr_exception_stub

  _isr2:
    cli
    pushl $0 // dummy error code
    pushl $2 // interrupt number
    jmp _isr_exception_stub

  _isr3:
    cli
    pushl $0 // dummy error code
    pushl $3 // interrupt number
    jmp _isr_exception_stub

  _isr4:
    cli
    pushl $0 // dummy error code
    pushl $4 // interrupt number
    jmp _isr_exception_stub

  _isr5:
    cli
    pushl $0 // dummy error code
    pushl $5 // interrupt number
    jmp _isr_exception_stub

  _isr6:
    cli
    pushl $0 // dummy error code
    pushl $6 // interrupt number
    jmp _isr_exception_stub

  _isr7:
    cli
    pushl $0 // dummy error code
    pushl $7 // interrupt number
    jmp _isr_exception_stub

  _isr8:
    cli
    // error code already pushed
    pushl $8 // interrupt number
    jmp _isr_exception_stub

  _isr9:
    cli
    pushl $0 // dummy error code
    pushl $9 // interrupt number
    jmp _isr_exception_stub

  _isr10:
    cli
    // error code already pushed
    pushl $10 // interrupt number
    jmp _isr_exception_stub

  _isr11:
    cli
    // error code already pushed
    pushl $11 // interrupt number
    jmp _isr_exception_stub

  _isr12:
    cli
    // error code already pushed
    pushl $12 // interrupt number
    jmp _isr_exception_stub

  _isr13:
    cli
    // error code already pushed
    pushl $13 // interrupt number
    jmp _isr_exception_stub

  _isr14:
    cli
    // error code already pushed
    pushl $14 // interrupt number
    jmp _isr_exception_stub

  _isr15:
    cli
    pushl $0 // dummy error code
    pushl $15 // interrupt number
    jmp _isr_exception_stub

  _isr16:
    cli
    pushl $0 // dummy error code
    pushl $16 // interrupt number
    jmp _isr_exception_stub

  _isr17:
    cli
    pushl $0 // dummy error code
    pushl $17 // interrupt number
    jmp _isr_exception_stub

  _isr18:
    cli
    pushl $0 // dummy error code
    pushl $18 // interrupt number
    jmp _isr_exception_stub

  _isr19:
    cli
    pushl $0 // dummy error code
    pushl $19 // interrupt number
    jmp _isr_exception_stub

  _isr20:
    cli
    pushl $0 // dummy error code
    pushl $20 // interrupt number
    jmp _isr_exception_stub

  _isr21:
    cli
    pushl $0 // dummy error code
    pushl $21 // interrupt number
    jmp _isr_exception_stub

  _isr22:
    cli
    pushl $0 // dummy error code
    pushl $22 // interrupt number
    jmp _isr_exception_stub

  _isr23:
    cli
    pushl $0 // dummy error code
    pushl $23 // interrupt number
    jmp _isr_exception_stub

  _isr24:
    cli
    pushl $0 // dummy error code
    pushl $24 // interrupt number
    jmp _isr_exception_stub

  _isr25:
    cli
    pushl $0 // dummy error code
    pushl $25 // interrupt number
    jmp _isr_exception_stub

  _isr26:
    cli
    pushl $0 // dummy error code
    pushl $26 // interrupt number
    jmp _isr_exception_stub

  _isr27:
    cli
    pushl $0 // dummy error code
    pushl $27 // interrupt number
    jmp _isr_exception_stub

  _isr28:
    cli
    pushl $0 // dummy error code
    pushl $28 // interrupt number
    jmp _isr_exception_stub

  _isr29:
    cli
    pushl $0 // dummy error code
    pushl $29 // interrupt number
    jmp _isr_exception_stub

  _isr30:
    cli
    pushl $0 // dummy error code
    pushl $30 // interrupt number
    jmp _isr_exception_stub

  _isr31:
    cli
    pushl $0 // dummy error code
    pushl $31 // interrupt number

    jmp _isr_exception_stub
