.text

multiply:
    # a0 x a1 saves in a0
    li t0, 0
    
multiply_loop:
    beqz a1, multiply_end
    add t0, t0, a0
    addi a1, a1, -1
    j multiply_loop
    
multiply_end:
    mv a0, t0
    ret

factorial:
    # save return address and argument
    addi sp, sp, -8
    sw ra, 4(sp)
    sw a0, 0(sp)
    
    # base case if n less than 1, return 1
    li t0, 1
    ble a0, t0, factorial_base
    
    # recursive case: n * factorial(n-1)
    addi a0, a0, -1
    call factorial
    
    # a0 now has factorial(n-1)
    # multiply by n (local var in stack)
    lw a1, 0(sp)
    
    # save factorial(n-1) result
    mv s0, a0
    
    # prepare multiply arguments
    mv a0, s0
    call multiply
    
    # restore and return
    lw ra, 4(sp)
    addi sp, sp, 8
    ret
    
factorial_base:
    li a0, 1
    lw ra, 4(sp)
    addi sp, sp, 8
    ret

main:
    # read number
    li t0, 4
    ecall
    
    # save input
    mv s0, a0
    
    # call factorial
    mv a0, s0
    call factorial
    
    # print result
    li t0, 1
    ecall
    
    # end
