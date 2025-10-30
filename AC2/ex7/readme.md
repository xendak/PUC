# Atividades - Assembly RISC-V

- Autor: Rafael Grossi


## Atividade 1

Complete o código acima para que ele imprima a soma dos 3 números armazenados no vetor na tela.

```asm
.data
vec: 
    .word 10
    .word 20
    .word 30

.text
main:
    lui s0, %hi(vec)
    addi s0, s0, %lo(vec)
    
    add t3, zero, zero
    
    lw t0, 0(s0)
    add t3, t3, t0
    
    lw t1, 4(s0)
    add t3, t3, t1
    
    lw t2, 8(s0)
    add t3, t3, t2
    
    add a0, t3, zero
    addi t0, zero, 1
    ecall
    ret
 ```

## Atividade 2

Altere o código anterior para que ele incremente cada um dos elementos do vetor (some o valor 1 a cada elemento e guarde o resultado na mesma posição de memória) e imprima o novo vetor na tela.

```asm
.data
vec: 
    .word 10
    .word 20
    .word 30

.text
main:
    lui s0, %hi(vec)
    addi s0, s0, %lo(vec)
    
    lw t0, 0(s0)
    addi t0, t0, 1
    sw t0, 0(s0)
  
    lw t1, 4(s0)
    addi t1, t1, 1
    sw t1, 4(s0)
  
    lw t2, 8(s0)
    addi t2, t2, 1
    sw t2, 8(s0)
  
    lw a0, 0(s0)
    addi t0, zero, 1
    ecall
  
    addi a0, zero, 32
    addi t0, zero, 2
    ecall
  
    lw a0, 4(s0)
    addi t0, zero, 1
    ecall
    
    addi a0, zero, 32
    addi t0, zero, 2
    ecall
  
    lw a0, 8(s0)
    addi t0, zero, 1
    ecall
  
    ret
```

## Atividade 3

Declare 2 vetores com 5 elementos cada um e some os elementos de mesmo índice dos vetores e guarde o resultado em um terceiro vetor. Imprima a soma de todos os elementos do terceiro vetor na tela.

```asm
.data
vec1: 
    .word 10
    .word 20
    .word 30
    .word 40
    .word 50

vec2:
    .word 5
    .word 15
    .word 25
    .word 35
    .word 45

vec3:
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0

.text
main:
    lui s0, %hi(vec1)
    addi s0, s0, %lo(vec1)
    lui s1, %hi(vec2)
    addi s1, s1, %lo(vec2)
    lui s2, %hi(vec3)
    addi s2, s2, %lo(vec3)
    addi t3, zero, 0
    addi t4, zero, 5
    addi t5, zero, 0
loop:
    beq t3, t4, end
    slli t6, t3, 2
    add a0, s0, t6
    lw t0, 0(a0)
    add a1, s1, t6
    lw t1, 0(a1)
    add t2, t0, t1
    add a2, s2, t6
    sw t2, 0(a2)
    add t5, t5, t2
    addi t3, t3, 1
    j loop

end:
    add a0, t5, zero
    addi t0, zero, 1
    ecall
    ret
```

## Atividade 4

Declare uma matriz de dimensões 2x3, com valor zero em todas as posições. Faça um programa que preencha a posição i, j com o valor (i+j).

```asm
.data
matrix:
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0

.text
main:
    lui s0, %hi(matrix)
    addi s0, s0, %lo(matrix)
    
    addi t0, zero, 0
    
loop_i:
    addi t3, zero, 2
    beq t0, t3, end
    
    addi t1, zero, 0
    
loop_j:
    addi t4, zero, 3
    beq t1, t4, next
    
    addi t5, zero, 3
    # mul t2, t0, t5
    slli t2, t0, 1
    add t2, t2, t0
    add t2, t2, t1
    
    slli t2, t2, 2
    
    add t6, t0, t1
    
    add a0, s0, t2
    sw t6, 0(a0)
    
    addi t1, t1, 1
    j loop_j

next:
    addi t0, t0, 1
    j loop_i

end:
    addi t0, zero, 0
    addi t1, zero, 6
    ret
```

## Atividade 5

Declare uma string com capacidade para armazenar 20 caracteres e faça a leitura da string pelo teclado. Como seu usuário não precisa ter digitado exatamente 20 caracteres, você deve contar quantos caracteres ele digitou e imprimir o tamanho da string digitada na tela.

```asm
.data
string:
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0  

.text
main:
    
    lui s0, %hi(string)
    addi s0, s0, %lo(string)
    
    add a0, s0, zero     
    addi a1, zero, 20    
    addi t0, zero, 6     
    ecall
    
    add t0, s0, zero     
    addi t1, zero, 0     
    addi t2, zero, 32    
    addi t3, zero, 0     
    
count_loop:
    lb t4, 0(t0)
    beq t4, t3, print_count
    beq t4, t2, check_end
    addi t1, t1, 1
    
next_char:
    addi t0, t0, 1
    j count_loop

check_end:
    lb t5, 1(t0)
    beq t5, t2, print_count
    addi t1, t1, 1
    j next_char

print_count:
    add a0, t1, zero
    addi t0, zero, 1
    ecall
    
    ret
```

## Atividade 6

Declare um vetor com 5 pontos, defina os valores iniciais na declaração e, supondo que esses são pontos no espaço, implemente um programa que detecte o ponto mais à direita. Se houver empate, escolha o mais acima. Imprima as coordenadas desse ponto na tela.

```asm
.data
point:
    .word 10 # x
    .word 20 # y
    .word 30 # x
    .word 15 # y
    .word 20 # x
    .word 25 # y
    .word 30 # x
    .word 30 # y
    .word 45 # x
    .word 40 # y

.text
main:
    lui s0, %hi(point)
    addi s0, s0, %lo(point)
    
    lw s1, 0(s0)
    lw s2, 4(s0)
    
    addi t0, zero, 1
    addi t1, zero, 5
    
loop_point:
    beq t0, t1, print
    
    slli t2, t0, 3
    
    add a0, s0, t2
    lw t3, 0(a0)
    lw t4, 4(a0)
    
    blt t3, s1, next
    bgt t3, s1, max
    
    blt t4, s2, next
    
max:
    add s1, t3, zero
    add s2, t4, zero
    
next:
    addi t0, t0, 1
    j loop_point

print:
    add a0, s1, zero
    addi t0, zero, 1
    ecall
    
    addi a0, zero, 44
    addi t0, zero, 2
    ecall
    
    addi a0, zero, 32
    addi t0, zero, 2
    ecall
    
    add a0, s2, zero
    addi t0, zero, 1
    ecall
    
    ret
```
