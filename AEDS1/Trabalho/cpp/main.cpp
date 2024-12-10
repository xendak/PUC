#include <iostream>

#include "pessoa.h"
#include "manager.h"
#include "list.h"
#include "data.h"

using namespace std;

bool valid_option(int op, int sb);
void main_menu();
void sub_menu(int op);
int execute_option(int op, int* sb);


int main(int argc, char** argv) {
    List<Person> pessoas;

    int menu = -1;
    int curr_menu = 0;
    while (execute_option(menu, &curr_menu) != -1) {
        cout << "Current state - menu: " << menu << ", curr_menu: " << curr_menu << endl;
        if (curr_menu == 0)
            main_menu();
        else
            sub_menu(curr_menu);

        cin >> menu;
    }

    return 0;
}

int execute_option(int op, int* sb) {
    if (op == 0 && *sb == 0) return -1;
    if (!valid_option(op, *sb)) return 0;

    if (*sb == 0) { *sb = op; }
    else { *sb = 0; }

    //do function.

    return 1;
}

bool valid_option(int op, int sb) {
    bool ans = false;
    int sub_op[7] = {2, 2, 2, 2, 2, 2, 3};

    if (sb == 0)
        ans = op > 0 && op <= 7;
    else
        ans = op >= 0 && op <= sub_op[sb - 1];

    return ans;
}

void main_menu() {
    cout << "Opções: " << endl;
    cout << "0. Sair do programa." << endl;
    cout << "1. Cadastrar pessoa." << endl;
    cout << "2. Listar todas as pessoas." << endl;
    cout << "3. Pesquisar por nome." << endl;
    cout << "4. Pesquisar por cpf." << endl;
    cout << "5. Excluir pessoa." << endl;
    cout << "6. Apagar todas as pessoas cadastradas." << endl;
    cout << "7. Aniversariantes do mês." << endl;
}

void sub_menu(int op) {
    cout << "0. Retornar ao menu principal." << endl;
    switch (op) {
        case 1:
            cout << "1. Cadastrar professor." << endl;
            cout << "2. Cadastrar aluno." << endl;
            break;
        case 2:
            cout << "1. Listar professores." << endl;
            cout << "2. Listar alunos." << endl;
            break;
        case 3:
            cout << "1. Pesquisar professor por nome." << endl;
            cout << "2. Pesquisar aluno por nome." << endl;
            break;
        case 4:
            cout << "1. Pesquisar professor por CPF." << endl;
            cout << "2. Pesquisar aluno por CPF." << endl;
            break;
        case 5:
            cout << "1. Excluir professor por CPF." << endl;
            cout << "2. Excluir aluno por CPF" << endl;
            break;
        case 6:
            cout << "1. Excluir todos os professores." << endl;
            cout << "2. Excluir todos os alunos." << endl;
            break;
        case 7:
            cout << "1. Pesquisar por mês." << endl;
            cout << "2. Listar todos os professores aniversariantes do mês atual." << endl;
            cout << "3. Listar todos os alunos aniversariantes do mês atual." << endl;
            break;
        default:
            cout << "err" << endl;
            break;
    }
}
