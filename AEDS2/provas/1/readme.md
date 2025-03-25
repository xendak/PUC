# Provas no Verde.
Entrada e Saida Q(x).in e Q(x).out

## Q1
Alguém deixou o quadro de medalhas das olimpíadas fora de ordem. Seu programa deve colocá-lo na ordem correta. A ordem dos países no quadro de medalhas é dada pelo número de medalhas de ouro. Se há empate em medalhas de ouro, a nação que tiver mais medalhas de prata fica a frente. Havendo empate em medalhas de ouro e prata, fica mais bem colocado o país com mais medalhas de bronze. Se dois ou mais países empatarem nos três tipos de medalhas, seu programa deve mostrá-los em ordem alfabética.

#### Entrada
A entrada é dada pelo número de países participantes N (0 ≤ N ≤ 500) seguido pela lista dos países, com suas medalhas de ouro O (0 ≤ O ≤ 10000), prata P (0 ≤ P ≤ 10000) e bronze B (0 ≤ B ≤ 10000).

#### Saída
A saída deve ser a lista de países, com suas medalhas de ouro, prata e bronze, na ordem correta do quadro de medalhas, com as nações mais premiadas aparecendo primeiro.

## Q2
As placas usadas nos carros em circulação no Brasil possuem dois padrões com formatos diferentes: algumas placas estão no antigo padrão Brasileiro, enquanto outras estão no novo padrão Mercosul.

O antigo padrão Brasileiro é sempre formado por 8 caracteres:

    - os três primeiros caracteres são letras maiúsculas (de A a Z);
    - o quarto caractere é um hífen (-);
    - os últimos quatro caracteres são dígitos (de 0 a 9).

Por exemplo, OBI-2024 é uma placa válida no antigo padrão Brasileiro.
O novo padrão Mercosul, por sua vez, é sempre formado por 7 caracteres:

    - os três primeiros caracteres são letras maiúsculas;
    - o quarto caractere é um dígito;
    - o quinto caractere é uma letra maiúscula;
    - os últimos dois caracteres são dígitos.

Assim, OBI2P24 é uma placa válida no novo padrão Mercosul.

Há também um grande contigente de carros em situação irregular – carros com placas falsificadas que não estão nem no antigo padrão Brasileiro, nem no novo padrão Mercosul. Por exemplo, um carro com a placa OBI-24 está em situação irregular, pois a placa não é válida em nenhum dos dois padrões.

O Departamento Nacional de Trânsito identificou que seus funcionários gastam muito tempo verificando manualmente quais placas estão em qual padrão e quais são falsificadas.

Por isso, eles pediram sua ajuda para automatizar o processo: dada uma placa formada por uma sequência de letras maiúsculas, dígitos e hífens, determine se a placa está no antigo padrão Brasileiro, está no novo padrão Mercosul, ou é uma placa falsificada.

#### Entrada
A entrada é composta de uma única linha, contendo uma sequência de caracteres representando a placa a ser analisada.

#### Saída
Seu programa deverá imprimir uma linha contendo um único número inteiro:

    1, se a placa está no antigo padrão Brasileiro;
    2, se a placa está no novo padrão Mercosul;
    0, se a placa é falsificada.
