.data
msg_n: .string "Digite N (tamanho do vetor): "
msg_v: .string "Digite um numero: "
msg_res: .string "\nQuantidade num maiores que a media: "
msg_med: .string "Media = "

.text
main:
    # 1. Ask for N
    li a0, 4
    la a1, msg_n
    ecall
    
    # Read N
    call LeNumero
    mv s0, a0
    
    # Size = N * 4 bytes
    slli t0, s0, 2  
    sub sp, sp, t0
    mv s1, sp
    
    mv a0, s1
    mv a1, s0
    call LeVetor
    
    mv a0, s1
    mv a1, s0
    call Media
    mv s2, a0       # s2 = Average

    li a0, 4
    la a1, msg_med
    ecall
    
    mv a1, s2
    li a0, 1
    ecall 
    
    # 5. Count numbers > Average
    mv a0, s1
    mv a1, s0
    mv a2, s2
    call ContarMaiores
    mv s3, a0       # s3 = Count
    
    # 6. Print Result
    li a0, 4
    la a1, msg_res
    ecall
    
    li a0, 1
    mv a1, s3
    ecall
    
    # Newline
    li a0, 11
    li a1, 13
    ecall
    
    # 7. Deallocate stack and Exit
    slli t0, s0, 2
    add sp, sp, t0
    
    li a0, 10
    ecall


# int ContarMaiores(int *v, int N, int media)
ContarMaiores:
    mv t0, a0       # ptr
    mv t1, a1       # N
    mv t2, a2       # media
    li t3, 0        # count
    li t4, 0        # i
    
Count_loop:
    beq t4, t1, Count_end
    lw t5, 0(t0)
    
    # if val (t5) <= media (t2), skip increment
    ble t5, t2, Count_next
    addi t3, t3, 1
    
Count_next:
    addi t0, t0, 4
    addi t4, t4, 1
    j Count_loop
    
Count_end:
    mv a0, t3
    ret

# Ex1 -> Ex3

LeNumero:
    addi sp, sp, -8
    sw ra, 4(sp)
    sw s0, 0(sp)
    li s0, 0 
    li a0, 0x130
    ecall
LeNumero_poll:
    li a0, 0x131
    ecall
    beq a0, zero, LeNumero_fim # Break on EOF/Empty
    li t0, 1
    beq a0, t0, LeNumero_poll
    li t1, 10
    beq a1, t1, LeNumero_fim   # Break on \n
    li t1, 13
    beq a1, t1, LeNumero_fim   # Break on \r
    li t2, 48
    blt a1, t2, LeNumero_poll  # Ignore < '0'
    li t2, 57
    bgt a1, t2, LeNumero_poll  # Ignore > '9'
    addi a1, a1, -48
    li t2, 10
    mul s0, s0, t2
    add s0, s0, a1
    j LeNumero_poll
LeNumero_fim:
    mv a0, s0
    lw s0, 0(sp)
    lw ra, 4(sp)
    addi sp, sp, 8
    ret

LeVetor:
    addi sp, sp, -16
    sw s0, 12(sp)
    sw s1, 8(sp)
    sw s2, 4(sp)
    sw ra, 0(sp)
    mv s0, a0
    li s1, 0
    mv s2, a1
LeVetor_loop:
    beq s1, s2, LeVetor_end
    li a0, 4
    la a1, msg_v
    ecall

    call LeNumero   
    sw a0, 0(s0)
    addi s0, s0, 4
    addi s1, s1, 1
    j LeVetor_loop
LeVetor_end:
    lw ra, 0(sp)
    lw s2, 4(sp)
    lw s1, 8(sp)
    lw s0, 12(sp)
    addi sp, sp, 16
    ret

Media:
    mv t0, a0
    mv t1, a1
    li t2, 0
    li t3, 0
Media_loop:
    beq t3, t1, Media_calc
    lw t4, 0(t0)
    add t2, t2, t4
    addi t0, t0, 4
    addi t3, t3, 1
    j Media_loop
Media_calc:
    beq t1, zero, Media_zero
    div a0, t2, t1
    ret
Media_zero:
    li a0, 0
    ret