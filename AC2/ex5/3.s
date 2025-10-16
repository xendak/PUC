main:
  addi t0, zero, 4
  ecall

  # 10011 & 11
  # 10 & 11
  # 11 & 11
  # 100 & 11
  andi t0, a0, 3
  bne t0, zero, no
  
  j yes

yes:
  li a0, 83
  j print
  
no:
  li a0, 78
  j print

print:
  addi t0, zero, 2
  ecall  
  ret
