end:
  ret
  
main:
  addi t0, zero, 4
  ecall
  beq a0, zero, end 
  addi a0, a0, 2
  addi t0, zero, 1
  ecall
  bne s0, zero, loop
  j main
  ret
