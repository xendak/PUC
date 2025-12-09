.data
    operations:
        .word 43
        .word 0x2c #add_func
        .word 45
        .word 0x34 #sub_func

.text

add_func:
    add a0, a0, a1
    ret

sub_func:
    sub a0, a0, a1
    ret

main:
    # read first number
    li t0, 4
    ecall
    mv s0, a0
    
    # read operator character
    addi sp, sp, -8
    li t0, 6
    mv a0, sp
    li a1, 2
    ecall
    lbu s1, 0(sp)
    addi sp, sp, 8
    
    # read second number
    li t0, 4
    ecall
    mv s2, a0
    
    # load function pointer
    lui t0, %hi(operations)
    addi t0, t0, %lo(operations)
    
    li t1, 2
    
find_operation:
    beqz t1, end
    
    lw t2, 0(t0)
    beq t2, s1, operation_found
    
    # move to next operation
    addi t0, t0, 8
    addi t1, t1, -1
    j find_operation
    
operation_found:
    lw t3, 4(t0)
    
    # arguments
    mv a0, s0
    mv a1, s2
    
    # call function
    jalr ra, t3, 0
    
    # print result
    li t0, 1
    ecall

end:
    ret
