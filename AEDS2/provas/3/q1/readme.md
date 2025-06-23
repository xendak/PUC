# Prova 3

Q1 -> java (q1.java java.in java.out) Q2 -> c (q2.c pub.in pub.out)

## Java
Descrição: Leia os dados de vários carros e insira-os em uma árvore binária
ordenada pela placa.
Em seguida, imprima os carros em ordem alfabética da placa.

Entrada: Cada linha contém os dados de um carro, no formato:
`placa,modelo,tipo,chassi`

A entrada termina com a linha: FIM

Saída: Lista ordenada dos carros conforme critério acima, um por linha, no
formato:
```
[placa] [modelo] [tipo] [chassi]
```

```java
class Carro {
    String placa, modelo, tipo, chassi;
    void ler(String linha) {
        String[] partes = linha.split(",");
        placa = partes[0]; modelo = partes[1]; tipo = partes[2]; chassi = partes[3];
    }

    void imprimir() {
        System.out.println(placa + " " + modelo + " " + tipo + " " + chassi);
    }

}
```
## C

Rafael está se preparando para o vestibular mas ele não sabe qual é a nota
mínima que ele terá que tirar para ser selecionado para o curso de Ciência da
Computação, então pediu sua ajuda, já que ele supõe que você já tem experiência
com programação. Será dado a você um inteiro N representando a quantidade de
notas e um valor K. Em seguida você terá um conjunto de N notas. Sua tarefa é
determinar qual a soma de todas as K-ésima maiores notas deste conjunto. Este
valor irá corresponder a nota que Rafael precisa.

Entrada

A entrada é composta por vários casos de teste e termina com EOF, na primeira
linha da entrada possui dois inteiros N e K, N <= 10⁶,K > 0, K <= N. Na próxima
linhas haverá N valores representando as nota NI,NI <= 10⁵

Saída

A saída será composta por um número representando a nota que Rafael precisa para
ser aprovado no vestibular, imprima resposta como modulo de 10⁹+7.
