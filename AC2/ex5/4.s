main:
  addi t0, zero, 4
  ecall

  # check for end loop
  beq a0, zero, print
  
  # check even
  andi t0, a0, 1
  bne t0, zero, odd
  j even


odd:
  add s0, s0, a0
  j main

even:
  add s1, s1, a0
  j main


print:
  sub a0, s0, s1
  addi t0, zero, 1
  ecall  
  ret
