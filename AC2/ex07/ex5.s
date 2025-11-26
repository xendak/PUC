.data
string:
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0  

.text
main:
    
    lui s0, %hi(string)
    addi s0, s0, %lo(string)
    
    add a0, s0, zero     
    addi a1, zero, 20    
    addi t0, zero, 6     
    ecall
    
    add t0, s0, zero     
    addi t1, zero, 0     
    addi t2, zero, 32    
    addi t3, zero, 0     
    
count_loop:
    lb t4, 0(t0)
    beq t4, t3, print_count
    beq t4, t2, check_end
    addi t1, t1, 1
    
next_char:
    addi t0, t0, 1
    j count_loop

check_end:
    lb t5, 1(t0)
    beq t5, t2, print_count
    addi t1, t1, 1
    j next_char

print_count:
    add a0, t1, zero
    addi t0, zero, 1
    ecall
    
    ret
