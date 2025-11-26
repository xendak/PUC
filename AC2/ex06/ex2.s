.text
.globl main
main:
  addi t0, zero, 4
  ecall
  add s0, zero, a0
  bltz s0, handle_negative
  add a0, zero, s0
  addi t0, zero, 35
  ecall
  j end

handle_negative:
  li a0, 45
  addi t0, zero, 2
  ecall
  neg a0, s0
  addi t0, zero, 1
  ecall

end:
    ret

.data
  x: .word 10
  y: .byte 20

