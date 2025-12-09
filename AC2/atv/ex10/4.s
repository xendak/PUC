.data
buffer_safe: .space 10
prompt_safe: .string "Digite (max 9 chars): "
written: .string "Digitado (max 9 chars): "

.text
main:
    li a0, 4
    la a1, prompt_safe
    ecall

    # newline
    li a0, 11
    li a1, 13
    ecall

    la a0, buffer_safe
    # Max size N
    li a1, 10 
    call fgets

    li a0, 4
    la a1, written
    ecall

    li a0, 4
    la a1, buffer_safe
    ecall

    # newline
    li a0, 11
    li a1, 13
    ecall

    li a0, 10
    ecall

# char * fgets(char *s, int N)
# a0 = buffer, a1 = N (size)
fgets:
    mv t0, a0
    # t3 = Max characters to read (N - 1) to leave room for null
    addi t3, a1, -1
    # Counter for chars read
    li t4, 0

    # Enable keyboard
    li a0, 0x130
    ecall

fgets_poll:
    # Check limit
    bge t4, t3, fgets_end

    li a0, 0x131
    ecall
    
    li t1, 2
    beq a0, t1, fgets_read
    beq a0, zero, fgets_end
    j fgets_poll

fgets_read:
    # Check newline
    li t2, 10
    beq a1, t2, fgets_end

    # Store char
    sb a1, 0(t0)
    
    # Increment pointer and counter
    addi t0, t0, 1
    addi t4, t4, 1
    j fgets_poll

fgets_end:
    # Null terminate
    sb zero, 0(t0)
    ret