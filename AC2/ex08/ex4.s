.text
TamanhoString:
    # stack begin
    addi sp, sp, -108
    sw   ra, 104(sp)
    sw   s0, 100(sp)
    
    mv   s0, sp         

    # read string
    li   t0, 6
    mv   a0, s0
    li   a1, 100        
    ecall

    # strlen(*str: a0)
    mv   a0, s0
    call strlen
    
    # stack end
    lw   s0, 100(sp)
    lw   ra, 104(sp)
    addi sp, sp, 108
    ret

strlen:
    mv   t0, a0
    li   t2, 10
    # check against space
    li   t3, 32
    
    strlen_loop:
        lbu  t1, 0(t0)
        beq  t1, zero, strlen_end
        beq  t1, t2, strlen_end
        beq  t1, t3, check_next
        
        addi t0, t0, 1
        j    strlen_loop
    
    check_next:
        lbu  t4, 1(t0)
        beq  t4, t2, strlen_end
        beq  t4, t3, strlen_end
        beq  t4, zero, strlen_end
        
        addi t0, t0, 1
        j    strlen_loop
    
    strlen_end:
        # size is end - start
        sub  a0, t0, a0
        ret

main:
    call TamanhoString
    
    mv   s0, a0         

    li   t0, 1
    mv   a0, s0
    ecall
