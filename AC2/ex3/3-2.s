main:
  addi t0, zero, 4
  ecall
  addi s11, zero, 2
  add  a0, s11, a0
  addi t0, zero, 1
  ecall
  ret
