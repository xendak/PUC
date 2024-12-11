#pragma once

#include "list.h"
#include "pessoa.h"
#include "data.h"

class PersonManager {
    private:
        List<Person *> people;

    public:
        PersonManager() {};
        ~PersonManager();

        bool add_person(Person* p);
        Person* find_by_name(const std::string& name);
        Person* find_by_cpf(const std::string& cpf);
};
