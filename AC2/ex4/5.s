main:
  addi t0, zero, 4
  ecall
  beq a0, zero, end
  add t1, zero, a0
  addi t0, zero, 4
  ecall
  beq a0, zero, end 
  add t2, zero, a0
  bge t1, t2, M1
  bge t1, t2, M2 
  M1:
    addi a0, zero, 0
    add a0, zero, t1
    j M3
  M2:
    addi a0, zero, 0
    add a0, zero, t2
    j M3
  M3:
    addi t0, zero, 1
    ecall
  j main

end:
  ret
