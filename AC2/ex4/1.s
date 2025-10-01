main:
  addi t0, zero, 4
  ecall
  addi a0, a0, 2
  addi t0, zero, 1
  ecall
  j main
  ret
