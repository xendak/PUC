.data
strA: .string "Ola "
strB: .string "Mundo"
strComp1: .string "Abc"
strComp2: .string "Abd"
res_len: .string "Tamanho strA: "
res_lenb: .string " | Tamanho strB: "

res_cmp: .string "\nComparacao: "
res_cat: .string "\nConcatenacao: "

.text
main:
    # strlen A
    li a0, 4
    la a1, res_len
    ecall
    
    la a0, strA
    call strlen
    # Print result (integer)
    mv a1, a0
    li a0, 1
    ecall

    # strlen B
    li a0, 4
    la a1, res_lenb
    ecall

    la a0, strB
    call strlen
    # Print result (integer)
    mv a1, a0
    li a0, 1
    ecall

    # strcmp(a, b)
    li a0, 4
    la a1, res_cmp
    ecall

    la a0, strComp1
    la a1, strComp2
    call strcmp
    # Print result (negative means s1 < s2)
    mv a1, a0
    li a0, 1
    ecall

    # srtcat(a, b)
    li a0, 4
    la a1, res_cat
    ecall
    
    # We concat strB into strA
    # assumes we actually have enough space
    la a0, strA
    la a1, strB
    call strcat
    
    # Print result string
    li a0, 4
    la a1, strA
    ecall

    # newline
    li a0, 11
    li a1, 13
    ecall

    li a0, 10
    ecall

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

# int strcmp(char *s1, char *s2)
strcmp:
strcmp_loop:
    lbu t0, 0(a0)
    lbu t1, 0(a1)
    # Compare bytes
    sub t2, t0, t1
    bne t2, zero, strcmp_diff
    
    # If both are zero (end of string), strings are equal
    beq t0, zero, strcmp_equal
    
    addi a0, a0, 1
    addi a1, a1, 1
    j strcmp_loop

strcmp_diff:
    mv a0, t2
    ret
strcmp_equal:
    li a0, 0
    ret

# char * strcat(char *s1, char *s2)
strcat:
    mv t0, a0
    
strcat_find_end:
    lbu t1, 0(t0)
    beq t1, zero, strcat_copy
    addi t0, t0, 1
    j strcat_find_end

strcat_copy:
    lbu t1, 0(a1)
    sb t1, 0(t0)
    beq t1, zero, strcat_end
    addi t0, t0, 1
    addi a1, a1, 1
    j strcat_copy

strcat_end:
    ret