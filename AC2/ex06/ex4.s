main:
    addi t0, zero, 5
    ecall
    
    # 0b11011111
    andi a0, a0, 223
    
    addi t0, zero, 2
    ecall
    
    ret
