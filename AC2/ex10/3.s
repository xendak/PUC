.data
buffer: .space 100
prompt: .string "Digite algo: "
written: .string "Digitado: "

.text
main:
    # Load prompt
    li a0, 4
    la a1, prompt
    ecall

    # this was bugging without this newline :)
    li a0, 11
    li a1, 13
    ecall

    # Load buffer
    la a0, buffer
    call gets

    # Print
    li a0, 4
    la a1, written
    ecall

    # Print read
    li a0, 4
    la a1, buffer
    ecall

    # newline
    li a0, 11
    li a1, 13
    ecall

    li a0, 10
    ecall

# char * gets(char *s)
gets:
    mv t0, a0
    
    li a0, 0x130
    ecall

gets_poll:
    # Check for char
    li a0, 0x131
    ecall
    
    # Check return status in a0
    # 0x00 = All read (finished/empty for now)
    # 0x01 = Nothing yet
    # 0x02 = Char available in a1
    
    li t1, 2

    beq a0, t1, gets_read
    beq a0, zero, gets_end_null 
    
    # Keep polling
    j gets_poll

gets_read:
    # a1, c = char
    # Check for newline (ASCII 10) to stop
    li t2, 10
    beq a1, t2, gets_end

    # Store in buffer
    sb a1, 0(t0)

    addi t0, t0, 1
    j gets_poll

gets_end:
    # Add null terminator
    sb zero, 0(t0)
    ret

gets_end_null:
    # terminate
    sb zero, 0(t0)
    ret