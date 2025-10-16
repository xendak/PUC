main:
  # input
  addi t0, zero, 4
  ecall
  add s0, zero, a0

  # counter start
  add s1, zero, zero
  # n bits
  li t1, 32

loop:
  beq s1, t1, end
  # increase counter
  addi s1, s1, 1

  # check MSB 
  bltz s0, odd

even:
  addi a0, zero, 0
  j print
  
odd:
  addi a0, zero, 1

print:
  slli s0, s0, 1
  addi t0, zero, 1
  ecall  
  j loop

end:
  ret
