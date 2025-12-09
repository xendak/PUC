main:
  addi t0, zero, 4
  ecall
  add s0, s0, a0

  addi t0, zero, 4
  ecall
  add s1, s1, a0

  # 12x
  slli t0, s0, 3
  slli t1, s0, 2
  add s0, t0, t1

  # 66y
  slli t0, s1, 6
  slli t1, s1, 1
  add s1, t0, t1

  # z
  add a0, s0, s1
  slli a0, a0, 2
  
  # addi, t0, zero, 1
  # ecall

  ret
