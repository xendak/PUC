.data
t_left:
    .word 0x00020002
t_right:
    .word 0x00080002
b_left:
    .word 0x00020008
b_right:
    .word 0x00080008
add_col:
    .word 0x00010000
add_row:
    .word 0x00000001
eye:
    .word 0x000FF000
mouth:
    .word 0x00edbbe2


.text
main:
    li a0, 0x101
    li a1, 0x00FFFFFF
    ecall
    
    call clearSquare
    call paint

    li a0, 10
    ecall


paint:
    li a0, 0x100
    lw a2, eye
    
    li a1, 0x00030003
    ecall
    li a1, 0x00030004
    ecall
    li a1, 0x00060003
    ecall
    li a1, 0x00060004
    ecall
    lw a2, mouth
    li a1, 0x00020006
    ecall
    li a1, 0x00030007
    ecall
    li a1, 0x00040007
    ecall
    li a1, 0x00050007
    ecall
    li a1, 0x00060007
    ecall
    li a1, 0x00070006
    ecall

    ret

clearSquare:
    lw t1, t_left
    lw t2, t_right
    lw t3, b_left
    lw t5, add_col
    lw t6, add_row
    li a0, 0x100
    li a2, 0x000Ab0c0
    for_v: 
        beq t1, t3, end_v
        mv a3, t1           

        for_h:
            beq a3, t2, end_h

            mv a1, a3
            ecall

            add a3, a3, t5
            j for_h
    
        end_h:
            add t1, t1, t6
            add t2, t2, t6
            j for_v
    
    end_v:
        ret
