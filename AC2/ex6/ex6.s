.globl main
main:
    addi t0, zero, 4
    ecall
    add t1, zero, a0
    
    # 0..9 or digit A..F
    li t2, 10
    blt t1, t2, is_digit
    
is_letter:
    addi a0, t1, 55
    j print_hex

is_digit:
    addi a0, t1, 48
    
print_hex:
    addi t0, zero, 2
    ecall
    
    # h
    li a0, 104
    addi t0, zero, 2
    ecall
    
    ret
