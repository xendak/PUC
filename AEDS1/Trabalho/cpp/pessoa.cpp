#include "pessoa.h"
#include "data.h"
#include <iostream>

Person::Person(std::string name, std::string cpf, int age, Date bday) {
    this->name = name;
    this->cpf = cpf;
    this->age = age;
    this->bday = bday;
}
Person::Person() {
    name = "";
    cpf = "";
    age = 0;
    bday = Date();
}

void Person::operator=(const Person& p) {
    this->name = p.name;
    this->cpf = p.cpf;
    this->age = p.age;
    this->bday = p.bday;
}

int Person::find_age() const {
    Date today = Date::get_current_date();
    int calculated_age = today.get_year() - bday.get_year();

    if (today.get_day() < bday.get_day() || (today.get_month() == bday.get_month() && today.get_day() < bday.get_day())) {
        calculated_age--;
    }

    return calculated_age;
}

Student::~Student() {};
Teacher::~Teacher() {};

bool Student::print() {
    std::cout << get_type() << std::endl;
    std::cout << "\t" << "Nome: " << name << std::endl;
    std::cout << "\t" << "CPF: " << cpf << std::endl;
    std::cout << "\t" << "Idade: " << age << std::endl;
    std::cout << "\t" << "Anivesário: " << bday.print_as_string() << std::endl;
    /*std::cout << "\t" << "Aniversário: "; */
    /*bday.print();*/
    /*std::cout << std::endl;*/
    std::cout << "\t" << "Curso: " << course << std::endl;
    std::cout << "\t" << "Matrícula: " << student_id << std::endl;
    return true;
}

bool Teacher::print() {
    std::cout << get_type() << std::endl;
    std::cout << "\t" << "Nome: " << name << std::endl;
    std::cout << "\t" << "CPF: " << cpf << std::endl;
    std::cout << "\t" << "Idade: " << age << std::endl;
    std::cout << "\t" << "Anivesário: " << bday.print_as_string() << std::endl;
    /*std::cout << "\t" << "Aniversário: "; */
    /*bday.print();*/
    /*std::cout << std::endl;*/
    std::cout << "\t" << "Departamento: " << department << std::endl;
    std::cout << "\t" << "Salário: " << salary << std::endl;
    return true;
}
