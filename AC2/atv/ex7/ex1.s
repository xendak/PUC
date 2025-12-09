.data
vetor: 
    .word 10
    .word 20
    .word 30

.text
main:
    lui s0, %hi(vetor)
    addi s0, s0, %lo(vetor)
    
    add t3, zero, zero
    
    lw t0, 0(s0)
    add t3, t3, t0
    
    lw t1, 4(s0)
    add t3, t3, t1
    
    lw t2, 8(s0)
    add t3, t3, t2
    
    add a0, t3, zero
    addi t0, zero, 1
    ecall
    ret
