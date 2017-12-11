.section .text
  .global load_gdt
  load_gdt:
    movl 4(%esp), %eax
    lgdt (%eax)

    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss
    ljmpl $0x08, $__load_gdt_flush
  __load_gdt_flush:
    ret
