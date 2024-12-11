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
        // dereference it, so we get the List instead of the iterator, then check
        if ((*it)->get_cpf() == cpf) {
            person = (*it);
        }
    }
    return person;
}

bool PersonManager::remove_by_name(const std::string& name) {
    auto comparator = Person::compare_by_name(name);
    return people.remove_by_value(nullptr, comparator);
}

bool PersonManager::remove_by_cpf(const std::string& cpf) {
    //method 2 so we learn a new way of iterating :)
    // will be "ineficient" since my remove_node is private, so we
    // traverse the list twice to get what we want :)
    bool ans = false;
    auto to_delete = people.begin();
    for (auto it = people.begin(); it != people.end(); ++it) {
        if ((*it)->get_cpf() == cpf) {
            to_delete = it;
        }
    }

    if (!(*to_delete == nullptr)) {
        delete (*to_delete);
        ans = people.remove_node(*to_delete);

    }

    return ans;
}

void PersonManager::print() {
    int i = 0;
    for (Person* p : people) {
        std::cout << i << ". Nome: " << p->get_name() << std::endl;
        i++;
    }
}
