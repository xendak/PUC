main:
    addi t0, zero, 4
    ecall

    addi a0, a0, -10

    blt a0, zero, negative
    addi t0, zero, 1
    ecall
    j end

negative:
    mv t1, a0
    
    addi a0, zero, 45
    addi t0, zero, 2
    ecall
    neg a0, t1

    addi t0, zero, 1
    ecall

end:
    ret
