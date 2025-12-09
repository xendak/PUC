main:
  addi t0, zero, 4 # stores on a0
  ecall
  addi s11, zero, 2
  add  s8, s11, a0
  ret

