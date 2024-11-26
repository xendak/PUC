Chuva

Está chovendo tanto na Obilândia que começaram a aparecer goteiras dentro da casa do prefeito. Uma dessas goteiras está fazendo escorrer água verticalmente, a partir de um ponto no teto, numa parede onde há várias prateleiras horizontais. Quando a água bate em uma prateleira, ela começa a escorrer horizontalmente para os dois lados, direita e esquerda, até as extremidades da prateleira, quando volta a escorrer verticalmente.

Vamos representar a parede por uma matriz de N linhas e M colunas de caracteres, como mostrado abaixo. As prateleiras serão representadas por "#" e a parede por ".". Só existem prateleiras nas linhas pares e elas nunca encostam na borda da parede. Há apenas um ponto de vazamento representado pelo caractere " o" na primeira linha.

      .......o......
      .###...####.#.
      ..............
      ..######......
      ..............
      .#.####....##.
      ..............
      .....####.....
      ..............

Para deixar mais rigorosa a forma como a água vai escorrer, seja c(i,j) o caractere na linha i coluna j. Se c(i,j)= ".", então ele deve virar "o" sempre que:

    c(i-1,j)= "o"; ou
    c(i,j-1)= "o" e c(i+1,j-1)= "#"; ou
    c(i,j+1)= "o" e c(i+1,j+1)= "#". 

      ......oooooo..
      .###..o####o#.
      .oooooooo..o..
      .o######o..o..
      ooo.....o.oooo
      o#o####.o.o##o
      o.o.ooooooo..o
      o.o.o####oo..o
      o.o.o....oo..o

Neste problema, dada a matriz representando a parede no início do vazamento, seu programa deve imprimir na saída uma matriz representando a parede usando o caractere "o" exatamente nas posições que serão molhadas pelo vazamento, como ilustrado acima.
Entrada
A primeira linha da entrada contém dois inteiros N e M, respectivamente o número de linhas e colunas da matriz. As N linhas seguintes da entrada contêm, cada uma, uma sequência de M caracteres entre três possíveis: ".", "#" ou "o".
Saída
Seu programa deve imprimir N linhas, cada uma contendo uma sequência de M caracteres, representando a matriz da entrada usando o caractere "o" exatamente nas posições que serão molhadas pelo vazamento.
Restrições

    3 ≤ N ≤ 500 e 3 ≤ M ≤ 500;
    O número de linhas N é ímpar;
    Há exatamente um caractere "o" na primeira linha;
    As linhas ímpares, a primeira coluna e a última coluna não possuem o caractere "#". 

#Exemplos
    Entrada

9 14
.......o......
.###...####.#.
..............
..######......
..............
.#.####....##.
..............
.....####.....
..............

	Saída

......oooooo..
.###..o####o#.
.oooooooo..o..
.o######o..o..
ooo.....o.oooo
o#o####.o.o##o
o.o.ooooooo..o
o.o.o####oo..o
o.o.o....oo..o
	

 
    Entrada

7 5
.o...
.#...
.....
.....
.....
..#..
.....

	Saída

ooo..
o#o..
o.o..
o.o..
oooo.
oo#o.
oo.o.
	

 
    Entrada

3 3
..o
.#.
...

	Saída

..o
.#o
..o
	
