.data
buffer_temp: .space 100 
msg_nome: .string "Digite o nome: "
msg_idade: .string "Digite a idade: "
msg_res: .string "\nDados da Pessoa (Struct com nome dinamico):\n"

.text
main:
    # read person struct
    call LePessoa
    mv s0, a0        # s0 = struct pointer
    
    # print msg
    li a0, 4
    la a1, msg_res
    ecall
    
    # print person
    mv a0, s0
    call ImprimePessoa
    
    li a0, 10
    ecall
    
# Pessoa* LePessoa()
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

# void ImprimePessoa(Pessoa *p)
ImprimePessoa:
    mv t0, a0
    
    # print name
    li a0, 4
    lw a1, 0(t0)
    ecall
    
    # Print Space
    li a0, 11
    li a1, 32
    ecall
    
    # print age
    li a0, 1
    lw a1, 4(t0)
    ecall
    
    # newline
    li a0, 11
    li a1, 13
    ecall
    ret


# HELPERS
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
    
    addi a1, s1, 1   # Size = len + 1 (\0)
    li a0, 9         # sbrk ID
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