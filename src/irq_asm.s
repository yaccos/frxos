.include "src/pushxl.inc.s"

.section .text
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

  .extern irq_handler
  _irq_common_stub:
    cli
    pushxl // push all registers
    addl $20, 32(%esp) // set stored ESP to ESP at interrupt

    // push pointer to stack
    movl %esp, %eax
    pushl %eax

    // call irq_handler()
    call irq_handler

    // clear stack
    addl $4, %esp
    popxl
    addl $8, %esp

    // return from interrupt
    iret

  _irq0:
    cli
    pushl $0 // dummy error code
    pushl $0 // IRQ number
    jmp _irq_common_stub

  _irq1:
    cli
    pushl $0 // dummy error code
    pushl $1 // IRQ number
    jmp _irq_common_stub

  _irq2:
    cli
    pushl $0 // dummy error code
    pushl $2 // IRQ number
    jmp _irq_common_stub

  _irq3:
    cli
    pushl $0 // dummy error code
    pushl $3 // IRQ number
    jmp _irq_common_stub

  _irq4:
    cli
    pushl $0 // dummy error code
    pushl $4 // IRQ number
    jmp _irq_common_stub

  _irq5:
    cli
    pushl $0 // dummy error code
    pushl $5 // IRQ number
    jmp _irq_common_stub

  _irq6:
    cli
    pushl $0 // dummy error code
    pushl $6 // IRQ number
    jmp _irq_common_stub

  _irq7:
    cli
    pushl $0 // dummy error code
    pushl $7 // IRQ number
    jmp _irq_common_stub

  _irq8:
    cli
    pushl $0 // dummy error code
    pushl $8 // IRQ number
    jmp _irq_common_stub

  _irq9:
    cli
    pushl $0 // dummy error code
    pushl $9 // IRQ number
    jmp _irq_common_stub

  _irq10:
    cli
    pushl $0 // dummy error code
    pushl $10 // IRQ number
    jmp _irq_common_stub

  _irq11:
    cli
    pushl $0 // dummy error code
    pushl $11 // IRQ number
    jmp _irq_common_stub

  _irq12:
    cli
    pushl $0 // dummy error code
    pushl $12 // IRQ number
    jmp _irq_common_stub

  _irq13:
    cli
    pushl $0 // dummy error code
    pushl $13 // IRQ number
    jmp _irq_common_stub

  _irq14:
    cli
    pushl $0 // dummy error code
    pushl $14 // IRQ number
    jmp _irq_common_stub

  _irq15:
    cli
    pushl $0 // dummy error code
    pushl $15 // IRQ number
    jmp _irq_common_stub
