.data
vec1: 
    .word 10
    .word 20
    .word 30
    .word 40
    .word 50

vec2:
    .word 5
    .word 15
    .word 25
    .word 35
    .word 45

vec3:
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0

.text
main:
    lui s0, %hi(vec1)
    addi s0, s0, %lo(vec1)
    lui s1, %hi(vec2)
    addi s1, s1, %lo(vec2)
    lui s2, %hi(vec3)
    addi s2, s2, %lo(vec3)
    addi t3, zero, 0
    addi t4, zero, 5
    addi t5, zero, 0
loop:
    beq t3, t4, end
    slli t6, t3, 2
    add a0, s0, t6
    lw t0, 0(a0)
    add a1, s1, t6
    lw t1, 0(a1)
    add t2, t0, t1
    add a2, s2, t6
    sw t2, 0(a2)
    add t5, t5, t2
    addi t3, t3, 1
    j loop

end:
    add a0, t5, zero
    addi t0, zero, 1
    ecall
    ret
