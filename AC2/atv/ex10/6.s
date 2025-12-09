.data
prompt: .string "Digite algo: "
input_rev: .space 50
msg_rev: .string "Invertida: "

.text
main:
    # Load prompt
    li a0, 4
    la a1, prompt
    ecall

    # newline
    li a0, 11
    li a1, 13
    ecall

    # Use our previous fgets to read safely
    la a0, input_rev
    li a1, 50
    call fgets

    la a0, input_rev
    call strrev

    li a0, 4
    la a1, msg_rev
    ecall

    li a0, 4
    la a1, input_rev
    ecall

    # newline
    li a0, 11
    li a1, 13
    ecall

    li a0, 10
    ecall

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

# void strrev(char *s)
strrev:
    # Save return address and s0
    addi sp, sp, -8
    sw ra, 4(sp)
    sw s0, 0(sp)

    # start address in s0
    mv s0, a0

    # Calculate length: strlen(s) => a0
    call strlen

    mv t1, s0
    add t2, s0, a0
    addi t2, t2, -1

strrev_loop:
    bge t1, t2, strrev_end

    # Load bytes
    lbu t3, 0(t1)
    lbu t4, 0(t2)

    # Swap
    sb t4, 0(t1)
    sb t3, 0(t2)

    # Move pointers
    addi t1, t1, 1
    addi t2, t2, -1
    j strrev_loop

strrev_end:
    lw s0, 0(sp)
    lw ra, 4(sp)
    addi sp, sp, 8
    ret