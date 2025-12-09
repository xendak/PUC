# Pessoa* LePessoa()
# Allocates a Person struct and allocates memory for the name.
LePessoa:
    addi sp, sp, -16
    sw ra, 12(sp)
    sw s0, 8(sp)
    
    # struct (12 bytes)
    # [0: name*] [4: age] [8: next*]
    
    # FIX: ID goes to a0, Argument goes to a1
    li a0, 9      # sbrk ID
    li a1, 12     # Size (12 bytes)
    ecall
    mv s0, a0     # s0 = struct address
    
    # 2. Read Name
    li a0, 4
    la a1, msg_nome
    ecall

    # newline
    li a0, 11
    li a1, 13
    ecall
    
    # read string and store in struct
    call LeString 
    sw a0, 0(s0)
    
    # read age
    li a0, 4
    la a1, msg_idade
    ecall
    
    # store age
    call LeNumero
    sw a0, 4(s0)
    
    # pointer start as null
    sw zero, 8(s0)
    
    # return struct address
    mv a0, s0
    
    lw s0, 8(sp)
    lw ra, 12(sp)
    addi sp, sp, 16
    ret