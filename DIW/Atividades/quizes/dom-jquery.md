Pergunta 1:
Qual método do objeto window abre uma janela modal que contém uma mensagem para leitura e os botões OK e Cancelar?

confirm

Pergunta 2:
Em JavaScript, qual é a instrução correta para selecionarmos o parágrafo abaixo, que faz parte de um documento HTML:

html
<p id="titulo">Introdução</p>
document.getElementById('titulo')

Pergunta 3:
Quando o evento focus é disparado por um campo de formulário?

Quando começa a interação com o campo.

Pergunta 4:
Qual é o atributo do objeto evento, recebido pelas funções de tratamento de eventos, que identifica o elemento que disparou o evento?

target

Pergunta 5:
Qual é o evento que é disparado quando o formulário deve ser enviado ao script definido no atributo action do elemento <form>?

submit

Pergunta 6:
Em jQuery, usamos a instrução

js
$(document)
Para selecionar o objeto documento. E qual é a instrução jQuery para se selecionar um elemento cujo atributo id contém o valor "principal" em uma página?

$('#principal')

Pergunta 7:
Indique qual é o seletor correto para cada um dos elementos descritos abaixo:

Todos os parágrafos que são filhos diretos de elementos da classe "classe".

.classe > p

Todos os parágrafos que são imediatamente precedidos por um elemento irmão da classe "classe".

.classe + p

Todos os parágrafos que possuem um irmão anterior da classe "classe".

.classe ~ p

Todos os parágrafos que são descendentes de um elemento da classe "classe".

.classe p

Todos os elementos da classe "classe", bem como todos os parágrafos.

.classe, p

Pergunta 8:
Qual é o método de uma seleção jQuery que permite a alteração do conteúdo HTML dos elementos selecionados?

html()

Pergunta 9:
Por que o código que criarmos em jQuery deve ser iniciado por meio do método ready() do objeto $(document)?

Porque esse método é chamado quando todos recursos da página já estão carregados.

Pergunta 10:
Complete o código abaixo, de tal forma que o botão permaneça desativado, caso o campo fique em branco após uma alteração. Se algum valor for informado no campo, então ele deve ser ativado.

html
<!DOCTYPE html>
<html lang="pt-BR">
  <head>
    <title>Teste</title>
    <meta charset="utf-8" />
    <script src="jquery-3.5.0.min.js"></script>
    <script>
      $(document).ready(function () {
        $('#nome').on('input', (e) => {
          if (e.target.value.length > 0)
            $('#btn').prop('disabled', false);
          else
            $('#btn').prop('disabled', true);
        });
      });
    </script>
  </head>
  <body>
    <form id="login">
      <input id="nome" type="text" value="" />
      <button id="btn" type="submit" disabled>OK</button>
    </form>
  </body>
</html>
