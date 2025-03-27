## Q1 - java
A família toda ficou excitada pela novidade. Todos sabiam que o meu avô tinha sido um excelente jogador de bridge por décadas, mas quando foi anunciado que ele estaria no Guinness Book, o livro dos recordes, como o jogador de bridge de maior sucesso de todos os tempos, wow, aquilo foi surpreendente.

A Associação Internacional de Bridge (AIB) tem mantido, por diversos anos, um ranking semanal dos melhores jogadores do mundo. Considerando que cada aparição em um ranking semanal constitui um ponto para o jogador, meu avô foi nominado o melhor jogador de todos os tempos porque ele conseguiu o maior número de pontos.

Tendo muitos amigos que também estavam competindo com ele, meu avô está extremamente curioso para saber que jogador(es) ficou(aram) com o segundo lugar. Ele precisa de um programa, o qual, dada uma lista com os ranking semanais, descubra que jogador(es) ficou(aram) com o segundo lugar, de acordo com o número de pontos.

### Entrada

A entrada contém diversos casos de teste. Jogadores são identificados por inteiros de 1 a 10000. A primeira linha de um caso de teste contém dois inteiros N e M, indicando, respectivamente, o número de rankings disponíveis (2 ≤ N ≤ 500) e o número de jogadores em cada ranking (2 ≤ M ≤ 500). Cada uma das próximas N linhas contém a descrição de um ranking semanal. Cada descrição é composta por uma sequência de M inteiros, separados por um espaço em branco, identificando os jogadores que apareceram naquele ranking semanal. Você pode assumir que:

- Em cada caso de teste há exatamente um melhor jogador e ao menos um segundo melhor jogador,
- Cada ranking semanal consiste de M jogadores distintos.
- O final da entrada é indicado por N = M = 0.

### Saída

Para cada caso de teste da entrada seu programa deve produzir uma linha de saída, contendo o identificador do jogador que é o segundo melhor, em número de aparições nos rankings. Se há um empate para segundo lugar, imprima os identificadores de todos os segundo colocados, em ordem crescente. Cada identificador produzido deve ser seguido por um espaço em branco.

## Q2 - c
Muitos sites na internet adicionam uma sessão chamada “Perguntas mais Frequentes” que, como o nome já diz, contém as perguntas mais feitas pelos usuários que utilizam o site.

O portal do URI costuma receber muitas perguntas de seus usuários, então Neilor imaginou que seria uma boa ideia adicionar uma sessão de Perguntas mais Frequentes no site. Como o Neilor anda muito ocupado ultimamente, ele pediu a sua ajuda para adicionar essa sessão.

Dados os identificadores de perguntas feitas pelos usuários, diga o número de perguntas que serão adicionadas na nova sessão do site. Uma pergunta é classificada como “frequente” quando ela é feita ao menos K vezes.

### Entrada

Haverá diversos casos de teste. Cada caso de teste inicia com dois inteiros N e K (1 ≤ N ≤ 1000, 1 ≤ K ≤ 100), indicando o número de perguntas realizadas, e o número de vezes que uma pergunta deve ser feita para ser considerada “frequente”, respectivamente.

Em seguida haverá N inteiros P (1 ≤ P ≤ 100), cada um indicando o número de uma determinada pergunta.

O último caso de teste é indicado quando N = K = 0, o qual não deverá ser processado.

### Saída

Para cada caso de teste imprima uma linha, contendo um inteiro, indicando o número de perguntas que serão adicionadas na nova sessão do site.
