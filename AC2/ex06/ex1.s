.globl main
main:
    li t0, 4
    ecall
    add s0, zero, a0  

    bgez s0, handle_positive

handle_negative:
    addi s1, s0, -7   
    j print_result

handle_positive:
    addi s1, s0, 7    

print_result:
    bltz s1, print_is_negative

print_is_positive:
    add a0, s1, zero  
    li t0, 1          
    ecall
    j end

print_is_negative:
    li a0, 45         
    li t0, 2          
    ecall

    neg a0, s1
    
    li t0, 1          
    ecall

end:
    ret
