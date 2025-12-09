# void LeVetor(int *v, int N)
# a0 = vector address, a1 = N
LeVetor:
    addi sp, sp, -16
    sw s0, 12(sp)   # Vector pointer
    sw s1, 8(sp)    # Counter
    sw s2, 4(sp)    # N (limit)
    sw ra, 0(sp)
    
    mv s0, a0
    li s1, 0
    mv s2, a1
    
LeVetor_loop:
    beq s1, s2, LeVetor_end
    
    call LeNumero
    
    # Store in vector
    sw a0, 0(s0)
    
    addi s0, s0, 4
    addi s1, s1, 1
    j LeVetor_loop
    
LeVetor_end:
    lw ra, 0(sp)
    lw s2, 4(sp)
    lw s1, 8(sp)
    lw s0, 12(sp)
    addi sp, sp, 16
    ret