Gerenciamento de Candidatos

Objetivo
O objetivo deste exercício é praticar a manipulação de vetores de ponteiros para objetos em C++. Deverá ser criada uma classe Candidato, armazenar objetos dessa classe em um vetor de ponteiros, calcular a média das notas e listar os candidatos que obtiveram nota acima da média.

Enunciado
Você deverá criar um programa em C++ que gerencie um conjunto de candidatos. O programa deverá ler o número de candidatos, os dados de cada candidato (nome e nota), e em seguida listar os candidatos que obtiveram nota acima da média.

Especificações
Definição da Classe Candidato

Crie uma classe chamada Candidato com os seguintes atributos privados:
string nome: Nome do candidato.
double nota: Nota do candidato.

A classe deve possuir:
Um construtor que inicialize os atributos com os parâmetros fornecidos.
Métodos setNome e setNota para atribuir valores aos atributos.
Métodos getNome e getNota para acessar os atributos.

Definição de Constante
Defina uma constante _MAX que represente o número máximo de candidatos permitidos (por exemplo, _MAX = 100).

Função Principal
Na função main, execute as seguintes etapas:

Declare um vetor de ponteiros para objetos do tipo Candidato com tamanho _MAX.

Leia o número de candidatos (não deve exceder _MAX). Preferencialmente, planeje uma função específica para esta funcionalidade.

Para cada candidato, leia o nome e a nota, e crie um objeto Candidato, armazenando o ponteiro no vetor. Preferencialmente, planeje uma função específica para esta funcionalidade. A função deverá retornar o objeto candidato criado.

Calcule a média das notas dos candidatos. Preferencialmente, planeje uma função específica para esta funcionalidade. A função deverá retornar um valor real referente à média calculada.

Liste os candidatos que obtiveram nota acima da média. Preferencialmente, planeje uma função específica para esta funcionalidade.

Entrada:
O número N de candidatos
Nome e nota de cada um dos N candidatos

Saída:
Linhas com nome e nota de cada candidato com nota acima da média

Exemplo:

input:

3
"João" 10
"Maria" 20
"José" 3

output:
"Maria" 20

