.data
source: .string "Copy this string."
dest:   .space 30

.text
main:
    # Print
    li a0, 4
    la a1, source
    ecall

    # newline
    li a0, 11
    li a1, 13
    ecall

    # Load arguments for strcpy
    la a0, dest
    la a1, source
    call strcpy

    # Print
    li a0, 4
    la a1, dest
    ecall

    li a0, 10
    ecall

# char * strcpy(char *s1, char *s2)
# a0 = destination (s1), a1 = source (s2)
strcpy:
    mv t0, a0

strcpy_loop:
    lbu t1, 0(a1)
    sb t1, 0(t0)
    # Check if null terminator
    beq t1, zero, strcpy_end

    # Increment pointers
    addi a1, a1, 1
    addi t0, t0, 1
    j strcpy_loop

strcpy_end:
    ret