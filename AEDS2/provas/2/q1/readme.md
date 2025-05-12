# Jogadores de Futebol, Java
Neste Trabalho Prático sua tarefa é organizar as informações dos jogadores disponíveis para exibição ao usuário. Os dados foram obtidos a partir de uma busca no site Kaggle. Você deve ler, organizar e armazenar os dados de cada jogador em memória, utilizando as estruturas de dados em aula. Em seguida executar as operações descritas nos arquivos de entrada. Muito cuidado ao realizar o parser do texto. Fique atento a descrição dos dados que serão lidos e manipulados pelo seu sistema.

Crie uma classe Jogadores. Sua classe terá os atributos Nome (String), Foto (String), Nascimento (Data), Id(int) e Times(Array de inteiros). Ela terá também os métodos imprimir e ler. O método imprimir mostra a String ’id nome nascimento foto (times)’, contendo todos os atributos da classe. O método ler deve efetuar a leitura dos atributos de um registro. A entrada padrão é composta por várias linhas e cada uma contém dados do jogador que devem ser tratados e armazenados em objetos da classe Jogador. A última linha da entrada contém FIM. A saída padrão também contém várias linhas, uma para cada registro contido na entrada padrão, conforme o exemplo abaixo: 42373 Diego Alves 24/06/1985 https://tmssl.akamaized.net/images/portrait/header/42373-1543845950.jpg (614, 330)

### Entrada  q1.in
117,Frickson Erazo,https://tmssl.akamaized.net//bilder/spielerfotos/s_163434_614_2014_01_23_1.jpg,5/05/1988,/frickson-erazo/profil/spieler/163434,163434,"[614, 210, 330, 978]"

### Saida    q1.out
42373 Diego Alves 24/06/1985 https://tmssl.akamaized.net/images/portrait/header/42373-1543845950.jpg (614, 330)

# O Menor da Pilha, C
Todo Natal o bom velhinho consegue ir em todas as casas do mundo e deixar presentes para as crianças que foram boazinhas ao longo do ano, mas isso só é possível por causa do seu saco mágico de presentes. Seria impossível para o Papai Noel levar todos os presentes no seu saco, o volume e peso de todos eles torna isso obviamente inviável. O que acontece na verdade é que seu saco é uma espécie de portal mágico para sua fábrica de presentes no Polo Norte. Onde os presentes são empilhados pelos seus elfos e o Noel tira sempre o presente do topo dessa pilha quando acessa sua sacola mágica.

Os presentes possuem uma medição numérica do grau de diversão que podem proporcionar às crianças e o Papai Noel tem sempre a preocupação de saber qual o presente menos divertido que ele irá entregar ao longo da noite porque ele não quer que nenhuma criança se sinta mal com o que receber. Porém, isso não é possível de ser feito antecipadamente porque ao longo da noite enquanto o bom velhinho retira presentes da pilha para entregar, ainda estão sendo feitos outros e colocados na pilha. Então o máximo que ele pode saber é o valor do presente menos divertido na pilha até aquele momento.

Sua tarefa é, dado a sequência de operações feitas sobre a pilha de presentes, responder as consultas do Papai Noel sobre o valor do presente menos divertido na pilha até o momento.

### Entrada q2.in
A primeira linha da entrada contém um inteiro N (1 ≤ N ≤ 106) correspondedendo ao número de operações feitas sobre a pilha de presentes. As operações podem ser de três tipos: "PUSH V" onde V (1 ≤ V ≤ 109) é um inteiro que representa o grau de diversão do presente sendo colocado na pilha; "POP" que representa que o papai Noel está tirando um presente da pilha para entregar e "MIN" que representa uma consulta do Noel para saber o menor valor de presente na pilha.

### Saída q2.out
A saída consiste em uma linha contendo um inteiro com o menor valor de presente na pilha para as consultas do tipo "MIN" ou a mensagem "EMPTY" para as operações "MIN" e "POP" quando a pilha estiver vazia.
