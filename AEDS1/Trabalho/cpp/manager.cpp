#include <iostream>

#include "manager.h"

PersonManager::~PersonManager() {
    // we need to clear ourselves, since list only empties itself, not the data we create
    // and since we allocate memory (Person* ), then we need to make sure we free it...
    // or i could learn how to use smart pointers i guess?
    for (auto person : people) {
        delete person;
    }
}

bool PersonManager::add_person(Person* person) {
    return people.push(person);
}

Person* PersonManager::find_by_name(const std::string& name) {
    auto comparator = Person::compare_by_name(name);
    auto person = people.find_by_value(nullptr, comparator);
    return person ? person->data : nullptr;
}

Person* PersonManager::find_by_cpf(const std::string& cpf) {
    auto comparator = Person::compare_by_cpf(cpf);
    auto person = people.find_by_value(nullptr, comparator);
    return person ? person->data : nullptr;
}
