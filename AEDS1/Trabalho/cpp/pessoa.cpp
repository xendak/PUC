#include "pessoa.h"
#include "data.h"
#include <iostream>

Person::Person(std::string name, int age, float wage, Date bday) {
    this->name = name;
    this->age = age;
    this->wage = wage;
    this->bday = bday;
}

void Person::operator=(Person const& p) {
    this->name = p.name;
    this->age = p.age;
    this->wage = p.wage;
    this->bday = p.bday;
}

bool Person::print() {
    try{
        std::cout << "Name: " << this->name << std::endl;
        std::cout << "Age: " << this->age << std::endl;
        std::cout << "Birthday: " << this->bday.print() << std::endl;
        return true;
    } catch(...) {
        return false;
    }
}

People::People() {
    this->size = 0;
    this->p = NULL;
}

bool People::add_person(Person* np) {
    try {
        this->p[this->size] = *np;
        this->size++;
        return true;
    } catch(...) {
        return false;
    }
}

bool People::delete_person() {
    return false;
}

/*Pessoa pesquisa_pessoa(Pessoa p, char* str) {*/
/*    Pessoa result = criar_pessoa();*/
/**/
/*    for (int i = 0; i < p.tam; i++) {*/
/*        if (strstr(p.p[i].nome, str) != NULL)*/
/*            escreve_pessoas(&result, str, NULL);*/
/*    }*/
/**/
/*    return result;*/
/*}*/
/**/
/*s_Pessoa* pesquisa_pessoa_cpf(Pessoa p, char* cpf) {*/
/*    s_Pessoa* res = NULL;*/
/*    int sz = p.tam;*/
/**/
/*    while(!strcmp(p.p[sz].cpf, cpf) && sz) {*/
/*        if(strcmp(p.p[sz].cpf, cpf)) res = &p.p[sz];*/
/*        sz--;*/
/*    }*/
/**/
/*    return res;*/
/*}*/
/**/
/*bool delete_pessoa_por_cpf(Pessoa* p, char* cpf) {*/
/*    return false;*/
/*}*/

