import 'package:flutter/material.dart';
import 'package:sqflite/sqflite.dart';
import 'package:path/path.dart';

void main() {
  runApp(const App());
}

class App extends StatelessWidget {
  const App({super.key});

  @override
  Widget build(BuildContext context) {
    return const MaterialApp(debugShowCheckedModeBanner: false, home: Home());
  }
}

class Home extends StatefulWidget {
  const Home({super.key});

  @override
  State<Home> createState() => _HomeState();
}

class _HomeState extends State<Home> {
  // Controladores para o cadastro
  final TextEditingController _nomeController = TextEditingController();
  final TextEditingController _idadeController = TextEditingController();
  final TextEditingController _matriculaController = TextEditingController();
  final TextEditingController _cursoController = TextEditingController();

  // Controlador para as operações (listar um, atualizar, excluir)
  final TextEditingController _matriculaAcaoController =
      TextEditingController();

  // Método para recuperar ou abrir o banco de dados
  _recuperarBD() async {
    final caminho = await getDatabasesPath();
    // Mudamos o nome do arquivo do banco para forçar a criação de uma nova tabela com a estrutura atualizada
    final local = join(caminho, "bancodados_alunos.db");

    var retorno = await openDatabase(
      local,
      version: 1,
      onCreate: (db, dbVersaoRecente) {
        // SQL para criar a tabela 'alunos' com matrícula e curso
        // A matrícula foi definida como UNIQUE para garantir que não haja repetições
        String sql =
            "CREATE TABLE alunos ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "matricula VARCHAR UNIQUE, "
            "nome VARCHAR, "
            "idade INTEGER, "
            "curso VARCHAR)";
        db.execute(sql);
      },
    );

    print("Aberto ${retorno.isOpen.toString()}");
    return retorno;
  }

  // Método para inserir um novo aluno
  _salvarDados(
    BuildContext context,
    String matricula,
    String nome,
    int idade,
    String curso,
  ) async {
    if (matricula.isEmpty || nome.isEmpty || curso.isEmpty) {
      _mostrarDialogo(
        context,
        "Por favor, preencha os campos de Matrícula, Nome e Curso.",
      );
      return;
    }

    Database db = await _recuperarBD();

    Map<String, dynamic> dadosAluno = {
      "matricula": matricula,
      "nome": nome,
      "idade": idade,
      "curso": curso,
    };

    try {
      int id = await db.insert("alunos", dadosAluno);
      print("Salvo com id $id");
      _mostrarDialogo(context, "Aluno(a) salvo(a) com sucesso!");

      // Limpar os campos após salvar
      _matriculaController.clear();
      _nomeController.clear();
      _idadeController.clear();
      _cursoController.clear();
    } catch (e) {
      _mostrarDialogo(
        context,
        "Erro ao salvar: Matrícula já existe ou dados inválidos.",
      );
    }
  }

  // Método para exibir diálogos
  _mostrarDialogo(BuildContext context, String mensagem) {
    showDialog(
      context: context,
      builder: (BuildContext context) {
        return AlertDialog(
          title: const Text("Resultado"),
          content: Text(mensagem),
          actions: [
            TextButton(
              onPressed: () {
                Navigator.of(context).pop();
              },
              child: const Text("OK"),
            ),
          ],
        );
      },
    );
  }

  // Método para listar todos os alunos
  _listarAlunos() async {
    Database db = await _recuperarBD();
    String sql = "SELECT * FROM alunos";
    List alunos = await db.rawQuery(sql);

    for (var aluno in alunos) {
      print(
        " Matrícula: ${aluno['matricula']} | Nome: ${aluno['nome']} | Idade: ${aluno['idade']} | Curso: ${aluno['curso']}",
      );
    }
  }

  // Método para listar um aluno específico pela MATRÍCULA
  _listarUmAluno(BuildContext context, String matricula) async {
    Database db = await _recuperarBD();

    List alunos = await db.query(
      "alunos",
      columns: ["matricula", "nome", "idade", "curso"],
      where: "matricula = ?",
      whereArgs: [matricula],
    );

    if (alunos.isNotEmpty) {
      var aluno = alunos.first;
      _mostrarDialogo(
        context,
        "Matrícula: ${aluno['matricula']} \nNome: ${aluno['nome']} \nIdade: ${aluno['idade']} \nCurso: ${aluno['curso']}",
      );
    } else {
      _mostrarDialogo(
        context,
        "Aluno(a) com matrícula $matricula não encontrado(a).",
      );
    }
  }

  // Método para excluir um aluno pela MATRÍCULA
  _excluirAluno(BuildContext context, String matricula) async {
    Database db = await _recuperarBD();

    int retorno = await db.delete(
      "alunos",
      where: "matricula = ?",
      whereArgs: [matricula],
    );

    if (retorno > 0) {
      _mostrarDialogo(
        context,
        "Aluno(a) com matrícula $matricula excluído(a) com sucesso.",
      );
    } else {
      _mostrarDialogo(
        context,
        "Nenhum aluno encontrado com a matrícula $matricula.",
      );
    }
  }

  // Método para atualizar informações de um aluno pela MATRÍCULA
  _atualizarAluno(
    BuildContext context,
    String matricula,
    String? nome,
    int? idade,
    String? curso,
  ) async {
    Database db = await _recuperarBD();

    Map<String, dynamic> dadosAluno = {};
    if (nome != null && nome.isNotEmpty) {
      dadosAluno["nome"] = nome;
    }
    if (idade != null) {
      dadosAluno["idade"] = idade;
    }
    if (curso != null && curso.isNotEmpty) {
      dadosAluno["curso"] = curso;
    }

    if (dadosAluno.isNotEmpty) {
      int retorno = await db.update(
        "alunos",
        dadosAluno,
        where: "matricula = ?",
        whereArgs: [matricula],
      );

      if (retorno > 0) {
        _mostrarDialogo(
          context,
          "Aluno(a) com matrícula $matricula atualizado(a) com sucesso.",
        );
      } else {
        _mostrarDialogo(
          context,
          "Nenhum aluno encontrado com a matrícula $matricula.",
        );
      }
    } else {
      _mostrarDialogo(
        context,
        "Nenhuma informação para atualizar. Preencha Nome, Idade ou Curso.",
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text("Cadastro de Alunos")),
      // SingleChildScrollView adicionado para evitar overflow de tela
      body: SingleChildScrollView(
        child: Container(
          alignment: Alignment.center,
          padding: const EdgeInsets.all(16.0),
          child: Column(
            mainAxisSize: MainAxisSize.max,
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              const Text(
                "CADASTRAR NOVO ALUNO",
                style: TextStyle(fontWeight: FontWeight.bold),
              ),
              const Divider(),
              TextField(
                controller: _matriculaController,
                decoration: const InputDecoration(
                  label: Text("Digite a matrícula:"),
                ),
              ),
              TextField(
                controller: _nomeController,
                decoration: const InputDecoration(
                  label: Text("Digite o nome:"),
                ),
              ),
              TextField(
                controller: _idadeController,
                decoration: const InputDecoration(
                  label: Text("Digite a idade:"),
                ),
                keyboardType: TextInputType.number,
              ),
              TextField(
                controller: _cursoController,
                decoration: const InputDecoration(
                  label: Text("Digite o curso:"),
                ),
              ),
              const SizedBox(height: 15),
              ElevatedButton(
                onPressed: () {
                  _salvarDados(
                    context,
                    _matriculaController.text,
                    _nomeController.text,
                    int.tryParse(_idadeController.text) ?? 0,
                    _cursoController.text,
                  );
                },
                child: const Text("Salvar aluno"),
              ),
              const SizedBox(height: 10),
              ElevatedButton(
                onPressed: _listarAlunos,
                child: const Text("Listar todos alunos (Ver Console)"),
              ),

              const SizedBox(height: 30),
              const Text(
                "AÇÕES POR MATRÍCULA",
                style: TextStyle(fontWeight: FontWeight.bold),
              ),
              const Divider(),

              TextField(
                controller: _matriculaAcaoController,
                decoration: const InputDecoration(
                  label: Text(
                    "Digite a matrícula para listar/excluir/atualizar:",
                  ),
                ),
              ),
              const SizedBox(height: 15),
              ElevatedButton(
                onPressed: () {
                  String matricula = _matriculaAcaoController.text;
                  if (matricula.isNotEmpty) {
                    _listarUmAluno(context, matricula);
                  } else {
                    _mostrarDialogo(
                      context,
                      "Por favor, insira uma matrícula válida.",
                    );
                  }
                },
                child: const Text("Listar um aluno"),
              ),
              const SizedBox(height: 10),
              ElevatedButton(
                onPressed: () {
                  String matricula = _matriculaAcaoController.text;
                  if (matricula.isNotEmpty) {
                    _excluirAluno(context, matricula);
                  } else {
                    _mostrarDialogo(
                      context,
                      "Por favor, insira uma matrícula válida para excluir.",
                    );
                  }
                },
                child: const Text("Excluir aluno"),
              ),
              const SizedBox(height: 10),
              ElevatedButton(
                onPressed: () {
                  String matricula = _matriculaAcaoController.text;
                  if (matricula.isNotEmpty) {
                    // Pega os dados dos campos de cima para atualizar
                    String? nome = _nomeController.text.isNotEmpty
                        ? _nomeController.text
                        : null;
                    int? idade = int.tryParse(_idadeController.text);
                    String? curso = _cursoController.text.isNotEmpty
                        ? _cursoController.text
                        : null;

                    _atualizarAluno(context, matricula, nome, idade, curso);
                  } else {
                    _mostrarDialogo(
                      context,
                      "Por favor, insira uma matrícula válida no campo de ação.",
                    );
                  }
                },
                child: const Text("Atualizar aluno"),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
