.section .text
  .extern kb_int_handler
  .global _isr_kb1
  _isr_kb1:
    cli
    call kb_int_handler
    iret
