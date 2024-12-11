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

// method one by using a comparator function inside Person class itself;
Person* PersonManager::find_by_name(const std::string& name) {
    auto comparator = Person::compare_by_name(name);
    auto person = people.find_by_value(nullptr, comparator);
    return person ? person->data : nullptr;
}

// method 2, by using the iterator class i was trying to make :)
Person* PersonManager::find_by_cpf(const std::string& cpf) {
    /*auto comparator = Person::compare_by_cpf(cpf);*/
    /*auto person = people.find_by_value(nullptr, comparator);*/
    /*return person ? person->data : nullptr;*/

    Person* person = nullptr;
    for (auto it = people.begin(); it != people.end(); ++it) {
        if ((*it)->get_cpf() == cpf) {
            person = (*it);
        }
    }
    return person;
}
