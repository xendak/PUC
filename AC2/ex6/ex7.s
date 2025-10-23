.globl main
main:
    addi t0, zero, 4
    ecall
    
    beq a0, zero, end
    
    add s0, zero, a0
    
    # counters
    li s1, 8
    li s2, 28

hex_loop:
    # end condition
    beq s1, zero, print_h
    
    # 4 bits
    srl t1, s0, s2
    # s0 shift s2 and F
    andi t1, t1, 15
    
    li t2, 10
    blt t1, t2, is_digit_7
    
is_letter_7:
    addi a0, t1, 55
    j print_digit_7

is_digit_7:
    addi a0, t1, 48
    
print_digit_7:
    addi t0, zero, 2
    ecall
    
    # counters
    addi s2, s2, -4
    addi s1, s1, -1
    j hex_loop

print_h:
    # h
    li a0, 104
    addi t0, zero, 2
    ecall
    
    j main

end:
    ret
