Pergunta 1:
Qual é método que deve ser usado na instrução abaixo, para que acrescentemos um novo valor ao fim do vetor?

js
let cores = ['azul', 'vermelho', 'verde'];
cores.push('amarelo');
Resposta: push

Pergunta 2:
Qual é a sintaxe correta para um código JavaScript que tem por objetivo declarar uma nova função de nome myFunction?

function myFunction() { [CÓDIGO DA FUNÇÃO] }

Pergunta 3:
Que informação será escrita no console, após a execução do seguinte trecho de código?

js
let a = 5;
let b = a + "3";
console.log(typeof b);
Resposta: string

Pergunta 4:
Que informação será escrita no console, após a execução do seguinte trecho de código?

js
let a = 5;
let b = 15;
let c = (a <= 10) && !(b < 20) == "0";
console.log(c);
Resposta: false

Pergunta 5:
Dado o código JavaScript abaixo que utiliza a tecnologia JSON na sua declaração, informe o tipo correto da expressão data.genres[0].id na Linguagem JavaScript:

js
var data = {
  "adult": false,
  "budget": 80000000,
  "genres": [
    {
      "id": 16,
      "name": "Animação"
    },
    {
      "id": 10751,
      "name": "Família"
    }
  ]
}
Resposta: number

Pergunta 6:
Quais devem ser as expressões na instrução abaixo para que ela testar se um determinado número é primo (divisível apenas por 1 e ele mesmo) ou não?

js
let n = 17; // os comandos abaixo podem funcionar para quaisquer valores de n

let primo = true;
for(let i = Math.floor(Math.sqrt(n)); i > 1; i--)
  if(n % i == 0) // Testa se n é divisível por i
    primo = false;
console.log(`${n} ${!primo ? "não " : ""}é um número primo.`);
Resposta: Math.floor(Math.sqrt(n));i>1

Pergunta 7:
Que informação será escrita no console, após a execução do seguinte trecho de código?

js
let a = 10; 
if(a > 15) 
  console.log(1); 
else if(a > 3) 
  if(a > 15)  
    console.log(2); 
  else if(a > 5) 
    console.log(3); 
  else 
    console.log(4);
else
  console.log(5);
Resposta: 3

Pergunta 8:
Uma template string é uma string que:

permite que uma expressão embutida.

Pergunta 9:
Que valor será apresentado no console, após a execução do seguinte trecho de código?

js
let a = 5;
let b = ++a / 2;
console.log(b--);
Resposta: 3

Pergunta 10:
Qual é a instrução que declara uma variável nome com escopo local, isto é, com existência apenas dentro do bloco em que foi declarada?

let nome = 'João';
