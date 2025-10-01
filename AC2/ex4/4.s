end:
  ret

loop:
  bge t1, s1, end
  addi t1, t1, 1
  addi t0, zero, 4
  ecall
  beq a0, zero, end 
  addi a0, a0, 2
  addi t0, zero, 1
  ecall
  j loop

main:
  addi s1, zero, 2
  addi t1, zero, 0
  j loop
  ret
