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