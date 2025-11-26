LeVetor:
    addi  sp, sp, -56

    # Save at top
    sw    s2, 52(sp)
    sw    s1, 48(sp)
    sw    s0, 44(sp)
    sw    ra, 40(sp)

    mv    s0, a0
    mv    s1, a1

l2:
    blt   s1, zero, fiml2
    li    a0, 4
    la    a1, mensagem1
    ecall

    # Pass buffer address
    mv    a0, sp
    call  LeString

    # Convert string at buffer to number
    mv    a0, sp
    call  ConverteNumero

    sw    a0, 0(s0)
    addi  s0, s0, 4
    addi  s1, s1, -1
    j     l2

fiml2:
    # Restore registers from the top of the frame
    lw    ra, 40(sp)
    lw    s0, 44(sp)
    lw    s1, 48(sp)
    lw    s2, 52(sp)
    addi  sp, sp, 56
    ret