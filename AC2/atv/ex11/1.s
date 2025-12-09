# string to int :)
# int LeNumero()
# Returns: a0 (integer read)
LeNumero:
    addi sp, sp, -8
    sw ra, 4(sp)
    sw s0, 0(sp)

    # Initialize accumulator = 0
    li s0, 0 

    li a0, 0x130
    ecall

LeNumero_poll:
    li a0, 0x131
    ecall
    
    beq a0, zero, LeNumero_fim
    
    li t0, 1
    beq a0, t0, LeNumero_poll
        
    # Check for \n (10) or \r (13)
    li t1, 10
    beq a1, t1, LeNumero_fim
    li t1, 13
    beq a1, t1, LeNumero_fim

    # '0' => 48 ... '9' => 57
    li t2, 48
    blt a1, t2, LeNumero_poll
    li t2, 57
    bgt a1, t2, LeNumero_poll

    addi a1, a1, -48      # Convert ASCII to Int
    
    # make the number go to the correct place (sum * 10 + digit)
    li t2, 10
    mul s0, s0, t2
    add s0, s0, a1
    
    j LeNumero_poll

LeNumero_fim:
    # return to a0
    mv a0, s0
    lw s0, 0(sp)
    lw ra, 4(sp)
    addi sp, sp, 8
    ret