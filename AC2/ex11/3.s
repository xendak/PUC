# int Media(int *v, int N)
# a0 = vector address, a1 = N
# Returns: a0 (average)
Media:
    mv t0, a0       # t0 = vector ptr
    mv t1, a1       # t1 = N
    li t2, 0        # t2 = sum
    li t3, 0        # t3 = iterator
    
Media_loop:
    beq t3, t1, Media_calc
    lw t4, 0(t0)
    add t2, t2, t4
    addi t0, t0, 4
    addi t3, t3, 1
    j Media_loop
    
Media_calc:
    beq t1, zero, Media_zero
    
    # Average = sum / N
    div a0, t2, t1
    ret
Media_zero:
    li a0, 0
    ret