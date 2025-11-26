.data
heap_head: .word 0
msg_alloc1: .string "1. Alocando 10 bytes (A)...\n"
msg_addrA:  .string "   -> Endereco de A: "
msg_free1:  .string "2. Liberando bloco A...\n"
msg_alloc2: .string "3. Alocando 10 bytes novamente (B)...\n"
msg_addrB:  .string "   -> Endereco de B: "

msg_success: .string "\n[SUCESSO] O endereco B eh igual ao A.\n"
msg_fail:    .string "\n[FALHA] O endereco B eh diferente de A.\n"

.text
main:
    # malloc
    li a0, 4
    la a1, msg_alloc1
    ecall
    
    li a0, 10
    call my_malloc
    mv s0, a0       # s0 = address of A
    
    # write to A
    li t0, 99
    sb t0, 0(s0)
    
    # print Address A
    li a0, 4
    la a1, msg_addrA
    ecall
    
    # print address in hex
    mv a1, s0
    li a0, 34
    ecall
    
    # newline
    li a0, 11
    li a1, 13
    ecall

    # free
    li a0, 4
    la a1, msg_free1
    ecall
    
    mv a0, s0
    call my_free
    
    # malloc
    li a0, 4
    la a1, msg_alloc2
    ecall
    
    li a0, 10
    call my_malloc
    mv s1, a0
    
    # print address b
    li a0, 4
    la a1, msg_addrB
    ecall
    
    mv a1, s1
    li a0, 34
    ecall
    
    # newline
    li a0, 11
    li a1, 13
    ecall
    
    # check equal
    beq s0, s1, print_success
    
    # if not
    li a0, 4
    la a1, msg_fail
    ecall
    j end_program

print_success:
    li a0, 4
    la a1, msg_success
    ecall

end_program:
    li a0, 10
    ecall

# void * my_malloc(int size)
my_malloc:
    addi sp, sp, -16
    sw s0, 12(sp) # requested size
    sw s1, 8(sp)  # current block ptr
    sw ra, 0(sp)
    
    mv s0, a0     # Size needed
    
    # Load head
    la t0, heap_head
    lw s1, 0(t0)
    
malloc_search:
    # end of list -> create new
    beq s1, zero, malloc_new
    
    # check if free (offset 4)
    lw t1, 4(s1)  
    bne t1, zero, malloc_next
    
    # check size (offset 0)
    lw t2, 0(s1)  

    # if block too small
    blt t2, s0, malloc_next
    
    # mark -> free and useable block
    li t3, 1
    sw t3, 4(s1)
    
    # return pointer to area
    addi a0, s1, 16
    j malloc_ret

# goes next block
malloc_next:
    lw s1, 12(s1)
    j malloc_search

malloc_new:
    # alloc => Size + 16 bytes header
    
    addi a1, s0, 16
    li a0, 9
    ecall
    mv s1, a0
    
    # Setup Header
    sw s0, 0(s1)  # size
    li t0, 1
    sw t0, 4(s1)  # busy
    # Offset 8 is 'data' ptr
    addi t1, s1, 16
    sw t1, 8(s1)  
    sw zero, 12(s1) # next = null
    
    # insert into list
    la t0, heap_head
    lw t1, 0(t0)
    beq t1, zero, malloc_first
    
    # Traverse to end
    mv t2, t1
find_tail:
    lw t3, 12(t2)
    beq t3, zero, append_block
    mv t2, t3
    j find_tail
    
append_block:
    sw s1, 12(t2)
    j malloc_finish

# update heap
malloc_first:
    sw s1, 0(t0)

# return data address
malloc_finish:
    addi a0, s1, 16
    
malloc_ret:
    lw ra, 0(sp)
    lw s1, 8(sp)
    lw s0, 12(sp)
    addi sp, sp, 16
    ret

# void my_free(void *ptr)
my_free:
    # ptr points to data, header is 16 bytes back
    addi t0, a0, -16
    
    # mark set to false (0)
    sw zero, 4(t0)
    ret