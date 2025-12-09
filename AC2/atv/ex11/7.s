.data
buffer_temp: .space 100
msg_input: .string "Digite uma string: "
msg_out: .string "String alocada no Heap: "

.text
main:
    li a0, 4
    la a1, msg_input
    ecall
    
    # newline
    li a0, 11
    li a1, 13
    ecall
    
    call LeString
    mv s0, a0
    
    li a0, 4
    la a1, msg_out
    ecall
    
    # Print string from heap
    li a0, 4
    mv a1, s0
    ecall
    
    # newline
    li a0, 11
    li a1, 13
    ecall
    
    li a0, 10
    ecall

# char * LeString()
# Allocates exact memory on Heap and returns pointer
LeString:
    addi sp, sp, -16
    sw ra, 12(sp)
    sw s0, 8(sp)
    
    # Read into temp
    la a0, buffer_temp
    li a1, 100       # Max size
    call fgets
    
    la a0, buffer_temp
    call strlen
    mv s1, a0        # s1 = length
    
    # proper strlen -> len + \0
    addi a0, s1, 1
    li a7, 9
    ecall
    mv s0, a0        # s0 = new heap address
    
    # copy to heap
    mv a0, s0
    la a1, buffer_temp
    call strcpy
    
    # Return new address
    mv a0, s0
    
    lw s0, 8(sp)
    lw ra, 12(sp)
    addi sp, sp, 16
    ret

# From last week exercise.
fgets:
    mv t0, a0
    addi t3, a1, -1
    li t4, 0
    li a0, 0x130
    ecall
fgets_poll:
    bge t4, t3, fgets_end
    li a0, 0x131
    ecall
    li t1, 2
    beq a0, t1, fgets_read
    beq a0, zero, fgets_end
    j fgets_poll
fgets_read:
    li t2, 10
    beq a1, t2, fgets_end
    sb a1, 0(t0)
    addi t0, t0, 1
    addi t4, t4, 1
    j fgets_poll
fgets_end:
    sb zero, 0(t0)
    ret

# int strlen(char *s)
strlen:
    li t0, 0
strlen_loop:
    add t1, a0, t0
    lbu t2, 0(t1)
    beq t2, zero, strlen_end
    addi t0, t0, 1
    j strlen_loop
strlen_end:
    mv a0, t0
    ret

# char * strcpy(char *dest, char *src)
strcpy:
    mv t0, a0 # dest
    mv t1, a1 # src
strcpy_loop:
    lbu t2, 0(t1)
    sb t2, 0(t0)
    beq t2, zero, strcpy_done
    addi t0, t0, 1
    addi t1, t1, 1
    j strcpy_loop
strcpy_done:
    ret