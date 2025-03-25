## Q1 - java
Maria acabou de iniciar seu curso de graduação na faculdade de medicina e precisa de sua ajuda para organizar os experimentos de um laboratório o qual ela é responsável. Ela quer saber no final do ano, quantas cobaias foram utilizadas no laboratório e o percentual de cada tipo de cobaia utilizada.

Este laboratório em especial utiliza três tipos de cobaias: sapos, ratos e coelhos. Para obter estas informações, ela sabe exatamente o número de experimentos que foram realizados, o tipo de cobaia utilizada e a quantidade de cobaias utilizadas em cada experimento.


Entrada
A primeira linha de entrada contém um valor inteiro N que indica os vários casos de teste que vem a seguir. Cada caso de teste contém um inteiro Quantia (1 ≤ Quantia ≤ 15) que representa a quantidade de cobaias utilizadas e um caractere Tipo ('C', 'R' ou 'S'), indicando o tipo de cobaia (R:Rato S:Sapo C:Coelho).


Saída
Apresente o total de cobaias utilizadas, o total de cada tipo de cobaia utilizada e o percentual de cada uma em relação ao total de cobaias utilizadas, sendo que o percentual deve ser apresentado com dois dígitos após o ponto.

## Q2 - c
Mark e Leti adoram brincar com suas bolas Bakugan. Essas bolas são pequenas esferas de plástico com um pequeno brinquedo-monstro dentro. Quando jogada ao chão, a bola Bakugan se abre, fazendo um som incrível e liberando um monstro Bakugan assustador. Mark e Leti adoram brincar com seus monstros, mas abrir as bolas Bakugan também é bem divertido.


Cada um deles recebeu uma bolsa com bolas Bakugan e eles inventaram um jogo para abrir as bolas. Existem 10 monstros diferentes, e para o jogo Mark e Leti associaram cada monstro a um inteiro diferente de 1 a 10, de acordo com o nível de feiura do monstro. O jogo é composto de R rodadas. A cada rodada:

Os dois jogadores jogam suas bolas ao chão simultaneamente; Cada jogador acumula um número de pontos coincidente com o número associado ao monstro liberado por sua bola; O primeiro (e apenas o primeiro) jogador que liberar o mesmo monstro em três rodadas consecutivas ganha 30 pontos adicionais; se essa condição acontecer na mesma rodada para ambos os jogadores então ninguém ganha pontos extras. O vencedor do jogo é o jogador que acumular mais pontos. Por favor ajude Mark e Leti anunciar o vencedor do jogo!


Entrada
Cada caso de testo é descrito por três linhas. A primeira linha contém um inteiro R indicando o número de rodadas do jogo (1 ≤ R ≤ 10). A segunda linha contém R inteiros Mi indicando os monstros liberados por Mark a cada rodada (1 ≤ Mi ≤ 10, para 1 ≤ i ≤ R). A terceira linha contém R inteiros Li indicando os monstros liberados por Leti a cada rodada (1 ≤ Li ≤ 10, para 1 ≤ i ≤ R).

O último caso de teste é composto por uma linha contendo zero.


Saída
Para cada caso de teste imprima uma linha com um caractere representando o resultado do jogo: "M" caso o vencedor seja Mark, "L" caso o vencedor seja Leti, ou "T" caso haja um empate (tie).

