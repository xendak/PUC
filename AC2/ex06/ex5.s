.globl main
main:
    addi t0, zero, 5
    ecall
    add t1, zero, a0
    
    # 65 .. 90
    li t2, 65
    blt t1, t2, check_lower
    li t2, 90
    bgt t1, t2, check_lower
    
    ori a0, t1, 32
    j print

check_lower:
    # 97 .. 122
    li t2, 97
    blt t1, t2, print
    li t2, 122
    bgt t1, t2, print
    
    andi a0, t1, 223
    
print:
    addi t0, zero, 2
    ecall
    
    ret
