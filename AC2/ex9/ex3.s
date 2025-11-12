.data
# (x << 16) | y
t_left: 
    .word 0x00020002
t_right: 
    .word 0x00080002
b_left: 
    .word 0x00020008
b_right: 
    .word 0x00080008
add_col:
    .word 0x00010000
add_row:
    .word 0x00000001

.text

main:
    # clear screen
    li a0, 0x101
    li a1, 0x00FFFFFF
    ecall

    call paint

    li a0, 10
    ecall


paint:
    lw t1, t_left
    lw t2, t_right
    lw t3, b_left
    lw t5, add_col
    lw t6, add_row
    li a0, 0x100
    
    # row counter
    li s3, 0

    for_v: 
        beq t1, t3, end_v

        # column counter
        li s4, 0
        # current pos(horizontal)        
        mv a3, t1

        for_h:
            beq a3, t2, end_h

            # Calculate base color for this row
            li t0, 6
            # s5 = row % 6 (6 colors)
            rem s5, s3, t0
    
            # RGB components
            li s6, 0
            li s7, 0 
            li s8, 0
    
            beq s5, x0, color_red
            li t0, 1
            beq s5, t0, color_yellow
            li t0, 2
            beq s5, t0, color_green
            li t0, 3
            beq s5, t0, color_cyan
            li t0, 4
            beq s5, t0, color_blue
            j color_magenta

        end_h:
            add t1, t1, t6
            add t2, t2, t6
            addi s3, s3, 1
            j for_v

    end_v:
        ret

color_red:
    li s6, 255
    li s7, 0
    li s8, 0
    j apply_brightness
    
color_yellow:
    li s6, 255
    li s7, 255
    li s8, 0
    j apply_brightness
    
color_green:
    li s6, 0
    li s7, 255
    li s8, 0
    j apply_brightness
    
color_cyan:
    li s6, 0
    li s7, 255
    li s8, 255
    j apply_brightness
    
color_blue:
    li s6, 0
    li s7, 0
    li s8, 255
    j apply_brightness
    
color_magenta:
    li s6, 255
    li s7, 0
    li s8, 255

apply_brightness:
    # brightness = 100 + (s4 * 30); (100 -> 250)
    li t0, 30
    mul t0, s4, t0
    addi t0, t0, 100
    
    # R
    mul s6, s6, t0
    li t4, 255
    div s6, s6, t4
    
    # G
    mul s7, s7, t0
    div s7, s7, t4
    
    # B
    mul s8, s8, t0
    div s8, s8, t4
    
    # Combine into RGB
    slli a2, s6, 16
    slli t0, s7, 8
    or a2, a2, t0
    or a2, a2, s8
    
    # Draw
    mv a1, a3
    ecall

    # increment counter
    add a3, a3, t5
    addi s4, s4, 1
    j for_h
