main:
  # secret
  addi t0, zero, 4
  ecall

  add s0, zero, a0

input:
  # code
  addi t0, zero, 4
  ecall
  beq a0, zero, end

  xor a0, s0, a0

  addi t0, zero, 1
  ecall  

  j input


end:
  ret
