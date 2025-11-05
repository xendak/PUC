.data
vetor: 
    .word 10
    .word 20
    .word 30
    .word 40
    .word 50

.text
SomaVetor:
    li t0, 0
    for:
        beq a0, zero, end
        lw t1, 0(a1)    
        add t0, t0, t1

        addi a1, a1, 4
        addi a0, a0, -1

        j    for
    end:
        mv a0, t0
        ret


main:
    lui s0, %hi(vetor)
    
    addi a0, zero, 5
    addi a1, s0, %lo(vetor)

    call SomaVetor
    
    ret

