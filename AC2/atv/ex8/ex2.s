.data
vetor: 
    .word 10
    .word 20
    .word 30
    .word 40
    .word 50

.text
MultiplicaVetor:
    addi sp, sp, -16
    sw   s0, sp, 12
    sw   s1, sp, 8
    sw   s2, sp, 4
    sw   ra, sp, 0

    mv   s0, a0
    mv   s1, a1
    mv   s2, a2

for:
    beq  s0, zero, fim
    lw   a0, s1, 0
    mv   a1, s2
    call Multiplica
    sw   a0, s1, 0
    addi s1, s1, 4
    addi s0, s0, -1
    j    for

fim:
    lw   ra, sp, 0
    lw   s2, sp, 4
    lw   s1, sp, 8
    lw   s0, sp, 12
    addi sp, sp, 16
    ret

Multiplica:
    mv t0, a0
    li t1, 1

for1:
    beq a1, t1, m_end
    add a0, a0, t0
    addi a1, a1, -1
    j for1

m_end:
    ret

main:
    lui s0, %hi(vetor)
    
    addi a0, zero, 5
    # add a1, a0, s0
    addi a1, s0, %lo(vetor)
    addi a2, zero, 10

    call MultiplicaVetor
    
    ret
