# Exercício 4

- Autor: Rafael Grossi

## Atividade 1

### a)

- O que representa o rótulo main: no programa?

Representa o ponto de entrada de um bloco de função

### b)

- Por que o uso de rótulos facilita a leitura e a manutenção do código em vez de
  usar endereços numéricos diretos?

Legibilidade: mais facil ler imprimir_positivo, do que 0x00019c
Manutenibilidade: caso exista uma mudança em algum dos labels, é facil o montador fazer a varredura e atualizar, mas caso o endereço fosse utilizado, teriamos que substituir manualmente todos os pontos de jump/return, que é muito facil de errar, e também implicaria que nosso código ficasse exatamente naquele ponto de memoria.

### c)

- Quando você cria um rótulo como main ou fim, o montador trata esse nome como
  um símbolo. Explique, em suas palavras, qual a diferença entre um símbolo e o
  endereço numérico que será realmente usado na memória.

O símbolo (ex: main) é um nome abstrato, um identificador para o programador, é um "atalho" para local na memória. Ele existe no código-fonte e é significativo para humanos apenas.

O endereço numérico (ex: 0x1000007c) é a localização concreta e real na memória do computador. É o que a CPU utiliza para achar e executar as instruçṍes.

O montador é um "tradutor", ele cria uma tabela de símbolos, onde cada símbolo corresponde a um endereço real na memória. Quando o símbolo é usado no código (ex: j main) o montador consulta sua tabela e substitui o nome pelo endereço correto, gerando o código de máquina que a CPU pode entender.

### 2)

- Complete as instruções no código acima para que seu programa cumpra exatamente
  o que está dito no comentário. Você deve usar a instrução j para fazer o loop
  infinito.

```riscv
main:
  # Le um numero do teclado e armazena em a0
  addi, t0, zero, 4
  ecall

  # Soma 2 ao valor de a0
  add a0, a0, 2

  # Imprima o valor de a0 na tela
  addi, t0, zero, 1
  ecall

  # Va novamente para o main e recomece a execucao
  j main
  ret
```

## Atividade 2

- Altere seu programa para executar enquanto o número digitado for diferente de
  zero. Você deve usar a instrução beq para fazer o loop.

```riscv
main:
  addi t0, zero, 4
  ecall
  beq a0, zero, end 
  addi a0, a0, 2
  addi t0, zero, 1
  ecall
  j main

end:
  ret
```

## Atividade 3

Ficou meio estranho calcular a soma com 2 para o valor 0 que é o valor utilizado
para sair do programa. Altere seu programa para não imprimir o resultado da soma
com 2 se o número digitado for zero. Não se esqueça de atualizar o comentário ou
colocar novos se achar conveniente.

```riscv
main:
  addi t0, zero, 4
  ecall
  beq a0, zero, end 
  addi a0, a0, 2
  addi t0, zero, 1
  ecall
  j main

end:
  ret
```

## Atividade 4

- Altere seu programa para que ele execute exatamente 10 vezes. Você deve usar a
  instrução bge para fazer o loop.

```riscv
loop:
  bge t1, s1, end
  addi t1, t1, 1
  addi t0, zero, 4
  ecall
  beq a0, zero, end 
  addi a0, a0, 2
  addi t0, zero, 1
  ecall
  j loop

main:
  addi s1, zero, 10
  addi t1, zero, 0
  j loop

end:
  ret
```

## Atividade 5

- Altere seu programa para que ele leia de 2 em 2 números e sempre imprima o
  maior deles. Você deve encerrar quando qualquer um dos dois for zero.

```riscv
main:
  addi t0, zero, 4
  ecall
  beq a0, zero, end
  add t1, zero, a0
  addi t0, zero, 4
  ecall
  beq a0, zero, end 
  add t2, zero, a0
  bge t1, t2, M1
  bge t1, t2, M2 
  M1:
    addi a0, zero, 0
    add a0, zero, t1
    j M3
  M2:
    addi a0, zero, 0
    add a0, zero, t2
    j M3
  M3:
    addi t0, zero, 1
    ecall
  j main

end:
  ret
```


## Desafio

```riscv
main:
    addi t0, zero, 4
    ecall

    addi a0, a0, -10

    blt a0, zero, negative
    addi t0, zero, 1
    ecall
    j end

negative:
    mv t1, a0
    
    addi a0, zero, 45
    addi t0, zero, 2
    ecall
    neg a0, t1

    addi t0, zero, 1
    ecall

end:
    ret
```
