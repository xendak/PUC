#include <iostream>
#include <limits>

#include "manager.h"

using namespace std;

void Clear() {};
/*{*/
/*#if defined _WIN32*/
/*#include "conio.h"*/
/*    clrscr(); // including header file : conio.h*/
/*#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)*/
/*    std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences */
/*#endif*/
/*}*/

void debuggin();

void main_menu();
void sub_menu(int op);

bool valid_option(int op, int sb);
int execute_option(int op, int* sb, PersonManager& manager);

std::string get_from_user(std::string type);

bool add_student(PersonManager& manager);
bool add_teacher(PersonManager& manager);

void delete_all_students(PersonManager& manager);
void delete_all_teachers(PersonManager& manager);

void search_birthday_by_month(PersonManager& manager);
void search_birthday_students(PersonManager& manager);
void search_birthday_teachers(PersonManager& manager);

void search_by_name_teacher(PersonManager& manager);
void search_by_cpf_teacher(PersonManager& manager);
void delete_by_cpf_teacher(PersonManager& manager);

void search_by_name_student(PersonManager& manager);
void search_by_cpf_student(PersonManager& manager);
void delete_by_cpf_student(PersonManager& manager);


void press_enter_to_continue();

int main(int argc, char** argv) {
    PersonManager people;
    people.load_from_file("saved.file"); // Load data from file if exists

    int menu = -1;
    int curr_menu = 0;
    while (execute_option(menu, &curr_menu, people) != -1) {
        Clear();
        if (curr_menu == 0)
            main_menu();
        else
            sub_menu(curr_menu);

        cin >> menu;
    }

    people.save_to_file("saved.file"); // Save data to file before exiting
    return 0;
}
void press_enter_to_continue() { 
    std::cout << "Aperte Enter para continuar..." << std::endl; 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    std::cin.get();
}

void delete_all_teachers(PersonManager& manager) {
    manager.remove_all_by_type("Professor");
}

void delete_all_students(PersonManager& manager) {
    manager.remove_all_by_type("Aluno");
}


void search_birthday_by_month(PersonManager& manager) {
    int month;
    cout << "Digite um mes: " << endl;
    cin >> month;
    manager.list_bday(month);
}
void search_birthday_teachers(PersonManager& manager) {
    manager.list_bday_by_type(Date::get_current_date().get_month(), "Professor");
}

void search_birthday_students(PersonManager& manager) {
    manager.list_bday_by_type(Date::get_current_date().get_month(), "Aluno");
}

std::string get_from_user(std::string type) {
    string res;
    cout << "Digite um " << type << ": " << endl;
    cin.ignore();
    getline(cin, res);
    return res;
}

void search_by_name_teacher(PersonManager& manager) {
    string name = get_from_user("nome");
    auto p = manager.find_type_by_name(name, "Professor");
    if (p != nullptr) p->print();
}

void search_by_cpf_teacher(PersonManager& manager) {
    string cpf = get_from_user("CPF");
    auto p = manager.find_type_by_cpf(cpf, "Professor");
    if (p != nullptr) p->print();
}

void delete_by_cpf_teacher(PersonManager& manager) {
    string cpf = get_from_user("CPF");
    manager.remove_type_by_cpf(cpf, "Professor");
}

void search_by_name_student(PersonManager& manager) {
    string name = get_from_user("nome");
    auto p = manager.find_type_by_name(name, "Aluno");
    if (p != nullptr) p->print();
}

void search_by_cpf_student(PersonManager& manager) {
    string cpf = get_from_user("CPF");
    auto p = manager.find_type_by_cpf(cpf, "Aluno");
    if (p != nullptr) p->print();
}

void delete_by_cpf_student(PersonManager& manager) {
    string cpf = get_from_user("CPF");
    manager.remove_type_by_cpf(cpf, "Aluno");
}

bool add_teacher(PersonManager& manager) {
    string name, cpf, department;
    int age, day, month, year;
    double salary;

    cout << "Coloque as informaçoes do professor" << endl;
    cout << "(Name, CPF, Idade, Data de Nascimento (DD MM YYYY), Departamento, Salário): " << endl;
    cin >> name >> cpf >> age >> day >> month >> year >> department >> salary;
    cout << endl;
    return manager.add_person(new Teacher(name, cpf, age, Date(day, month, year), department, salary));
}

bool add_student(PersonManager& manager) {
    string name, cpf, course;
    int age, day, month, year, student_id;

    cout << "Coloque as informaçoes do aluno" << endl;
    cout << "(Name, CPF, Idade, Data de Nascimento (DD MM YYYY), Curso, Matrícula): " << endl;
    cin >> name >> cpf >> age >> day >> month >> year >> course >> student_id;
    cout << endl;
    return manager.add_person(new Student(name, cpf, age, Date(day, month, year), course, student_id));
}


int execute_option(int op, int* sb, PersonManager& manager) {
    if (op == 0 && *sb == 0) return -1;
    if (!valid_option(op, *sb)) return 0;

    if (*sb == 0) { 
        *sb = op; 
    } else { 
        switch (*sb) {
            case 1: // Register person
                if (op == 1)
                    cout << "Resultado: " << add_teacher(manager) << endl;
                else if (op == 2)
                    cout << "Resultado: " << add_student(manager) << endl;
                break;
            case 2: // List people
                if (op == 1) {
                    cout << "Listando todos os professores: " << endl;
                    manager.list_by_type("Professor");
                } else if (op == 2) {
                    cout << "Listando todos os alunos: " << endl;
                    manager.list_by_type("Aluno");
                }
                break;
            case 3: // Search by name
                if (op == 1)
                    search_by_name_teacher(manager);
                if (op == 2)
                    search_by_name_student(manager);
                break;
            case 4: // Search by CPF
                if (op == 1)
                    search_by_cpf_teacher(manager);
                if (op == 2)
                    search_by_cpf_student(manager);
                break;
            case 5: // Delete by CPF
                if (op == 1)
                    delete_by_cpf_teacher(manager);
                if (op == 2)
                    delete_by_cpf_student(manager);
                break;
            case 6: // Delete all
                if (op == 1) 
                    delete_all_teachers(manager);
                else if (op == 2)
                    delete_all_students(manager);
                break;
            case 7: // Birthdays
                if (op == 1) 
                    search_birthday_by_month(manager);
                else if (op == 2)
                    search_birthday_teachers(manager);
                else if (op == 3)
                    search_birthday_students(manager);
                break;
        }

        press_enter_to_continue();
        *sb = 0; // Return to the main menu after execution
    }

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
/**/
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

void debugging() {
    PersonManager manager;
    Date d = Date();

    manager.add_person(new Student("John Doe", "123456789", 20, d, "Computer Science", 12345));
    manager.add_person(new Teacher("Jane Smith", "987654321", 35, d, "CS Department", 75000.0));
    manager.add_person(new Student("Alice Johnson", "456789123", 22, d, "Physics", 12346));
    // Search by name
    manager.print();
    manager.remove_by_cpf("456789123");
    manager.print();
    manager.remove_by_name("John Doe");
    manager.print();

    Person* found = manager.find_by_name("John Doe");
    if (found) {
        std::cout << "Found: " << found->get_name() << std::endl;
    } else {
        std::cout << "Not found: " << found << std::endl;
    }
    found = manager.find_by_cpf("456789123");
    if (found) {
        std::cout << "Found: " << found->get_name() << std::endl;
    } else {
        std::cout << "Not found: " << found << std::endl;
    }
}
