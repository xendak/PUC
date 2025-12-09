.data
vec: 
    .word 10
    .word 20
    .word 30

.text
main:
    lui s0, %hi(vec)
    addi s0, s0, %lo(vec)
    
    lw t0, 0(s0)
    addi t0, t0, 1
    sw t0, 0(s0)
  
    lw t1, 4(s0)
    addi t1, t1, 1
    sw t1, 4(s0)
  
    lw t2, 8(s0)
    addi t2, t2, 1
    sw t2, 8(s0)
  
    lw a0, 0(s0)
    addi t0, zero, 1
    ecall
  
    addi a0, zero, 32
    addi t0, zero, 2
    ecall
  
    lw a0, 4(s0)
    addi t0, zero, 1
    ecall
    
    addi a0, zero, 32
    addi t0, zero, 2
    ecall
  
    lw a0, 8(s0)
    addi t0, zero, 1
    ecall
  
    ret
