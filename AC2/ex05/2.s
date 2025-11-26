main:
  addi t0, zero, 4
  ecall

  # check parity
  andi t0, a0, 1

  beq t0, zero, even
  j odd

odd:
  li a0, 73
  j print
  
even:
  li a0, 80
  j print

print:
  addi t0, zero, 2
  ecall  
  ret
