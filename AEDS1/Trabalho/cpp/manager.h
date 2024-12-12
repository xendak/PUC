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

        Person* find_type_by_name(const std::string& name, const std::string& type);
        Person* find_type_by_cpf(const std::string& cpf, const std::string& type);

        bool remove_by_name(const std::string& name);
        bool remove_by_cpf(const std::string& cpf);

        bool remove_type_by_name(const std::string& name, const std::string& type);
        bool remove_type_by_cpf(const std::string& cpf, const std::string& type);

        bool remove_all_by_type(const std::string& type);
        bool remove_all();
        
        void print();
        void list_all();
        void list_by_type(const std::string& type);
        void list_bday(const int& month);
        void list_bday_by_type(const int& month, const std::string& type);

        // file handling
        void save_to_file(const std::string& filename);
        void load_from_file(const std::string& filename);
};
