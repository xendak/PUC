.data
matrix:
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0

.text
main:
    lui s0, %hi(matrix)
    addi s0, s0, %lo(matrix)
    
    addi t0, zero, 0
    
loop_i:
    addi t3, zero, 2
    beq t0, t3, end
    
    addi t1, zero, 0
    
loop_j:
    addi t4, zero, 3
    beq t1, t4, next
    
    addi t5, zero, 3
    # mul t2, t0, t5
    slli t2, t0, 1
    add t2, t2, t0
    add t2, t2, t1
    
    slli t2, t2, 2
    
    add t6, t0, t1
    
    add a0, s0, t2
    sw t6, 0(a0)
    
    addi t1, t1, 1
    j loop_j

next:
    addi t0, t0, 1
    j loop_i

end:
    addi t0, zero, 0
    addi t1, zero, 6
    ret
