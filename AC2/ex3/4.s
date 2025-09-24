main:
  addi s5, zero, 2048 # overflow
  addi s11, zero, -2048 # underflow
  add  s8, s11, s5
  ret
