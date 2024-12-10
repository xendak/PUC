#include <iostream>

#include "manager.h"

bool PersonManager::add_person(const Person& p) {
    people.push(p);
    return true;
}
