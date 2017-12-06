/**
 * PUSHX/PUSHXL
 *  same as PUSHA/PUSHAL, but also pushes SS, DS, ES, FS and GS segment registers (in that order).
**/
.macro PUSHX
  pusha
  pushl %ss
  pushl %ds
  pushl %es
  pushl %fs
  pushl %gs
.endm

.macro PUSHXL
  pushx
.endm

/**
 * POPX/POPXL
 *   analogue of POPA/POPAL for PUSHX/PUSHXL
**/
.macro POPX
  popl %gs
  popl %fs
  popl %es
  popl %ds
  popl %ss
  popa
.endm

.macro POPXL
  popx
.endm
