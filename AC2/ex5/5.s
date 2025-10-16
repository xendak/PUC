main:
  # secret
  addi t0, zero, 4
  ecall

  add s0, zero, a0

  # code
  addi t0, zero, 4
  ecall

  xor a0, s0, a0

  addi t0, zero, 1
  ecall  

  # undo secret
  xor a0, s0, a0

  addi t0, zero, 1
  ecall  
  ret
