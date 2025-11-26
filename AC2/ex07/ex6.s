.data
point:
    .word 10 # x
    .word 20 # y
    .word 30 # x
    .word 15 # y
    .word 20 # x
    .word 25 # y
    .word 30 # x
    .word 30 # y
    .word 45 # x
    .word 40 # y

.text
main:
    lui s0, %hi(point)
    addi s0, s0, %lo(point)
    
    lw s1, 0(s0)
    lw s2, 4(s0)
    
    addi t0, zero, 1
    addi t1, zero, 5
    
loop_point:
    beq t0, t1, print
    
    slli t2, t0, 3
    
    add a0, s0, t2
    lw t3, 0(a0)
    lw t4, 4(a0)
    
    blt t3, s1, next
    bgt t3, s1, max
    
    blt t4, s2, next
    
max:
    add s1, t3, zero
    add s2, t4, zero
    
next:
    addi t0, t0, 1
    j loop_point

print:
    add a0, s1, zero
    addi t0, zero, 1
    ecall
    
    addi a0, zero, 44
    addi t0, zero, 2
    ecall
    
    addi a0, zero, 32
    addi t0, zero, 2
    ecall
    
    add a0, s2, zero
    addi t0, zero, 1
    ecall
    
    ret
