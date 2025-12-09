main:
  addi t0, zero, 4
  ecall
  addi s11, zero, 0
  add s8, s11, a0
  addi t0, zero, 4
  ecall
  xor a0, s8, a0
  addi t0, zero, 1
  ecall
  ret
