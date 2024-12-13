#include <iostream>
#include <sstream>
#include <fstream>

#include "manager.h"

PersonManager::~PersonManager() {}

bool PersonManager::add_person(Person* person) {
    return people.push(person);
}

// method 1, use a formatter and pass to the list class method
void PersonManager::list_all() {
    auto person_formatter = [](Person* const& person) {
        if (person) {
            person->print();
            std::cout << "------------------------" << std::endl;
        }
    };
    
    people.print(person_formatter);
}

// method 2, iterate manually and print using inherited class print()
void PersonManager::list_by_type(const std::string& type) {
    for (auto it = people.begin(); it != people.end(); ++it) {
        if ((*it)->get_type() == type) {
            (*it)->print();
            std::cout << "------------------------" << std::endl;
        }
    }
}

// method 2: but for the list_all :) 
void PersonManager::print() {
    for (Person* p : people) { p->print(); }
}

void PersonManager::list_bday(const int& month) {
    for (auto it = people.begin(); it != people.end(); ++it) {
        if ((*it)->get_birthday().get_month() == month) {
            (*it)->print();
            std::cout << "------------------------" << std::endl;
        }
    }

}
void PersonManager::list_bday_by_type(const int& month, const std::string& type) {
    for (auto it = people.begin(); it != people.end(); ++it) {
        if ((*it)->get_type() == type && (*it)->get_birthday().get_month() == month) {
            (*it)->print();
            std::cout << "------------------------" << std::endl;
        }
    }
}


// method one by using a comparator function inside Person class itself;
Person* PersonManager::find_by_name(const std::string& name) {
    auto comparator = Person::compare_by_name(name);
    auto person = people.find_by_value(nullptr, comparator);
    return person ? person->data : nullptr;
}

// method 2, by using the iterator class i was trying to make :)
Person* PersonManager::find_by_cpf(const std::string& cpf) {
    Person* person = nullptr;
    for (auto it = people.begin(); it != people.end(); ++it) {
        // dereference it, so we get the List instead of the iterator, then check
        if ((*it)->get_cpf() == cpf) {
            person = (*it);
        }
    }
    return person;
}

Person* PersonManager::find_type_by_name(const std::string& name, const std::string& type) { 
    Person* person = nullptr;
    for (auto it = people.begin(); it != people.end(); ++it) {
        if ((*it)->get_name() == name && (*it)->get_type() == type) {
            person = *it; // since we don't break, this will match the last found.
        }
    }
    return person;
}

Person* PersonManager::find_type_by_cpf(const std::string& cpf, const std::string& type) { 
    Person* person = nullptr;
    for (auto it = people.begin(); it != people.end(); ++it) {
        if ((*it)->get_cpf() == cpf && (*it)->get_type() == type) {
            person = *it;
        }
    }
    return person;
}

bool PersonManager::remove_by_name(const std::string& name) {
    auto comparator = Person::compare_by_name(name);
    return people.remove_by_value(nullptr, comparator);
}

bool PersonManager::remove_type_by_name(const std::string& name, const std::string& type) {
    auto comparator = Person::compare_by_name_and_type(name, type);
    return people.remove_by_value(nullptr, comparator);
}

bool PersonManager::remove_by_cpf(const std::string& cpf) {
    // method 2 so we learn a new way of iterating :)
    // will be "ineficient" since we dont have access to remove_node(nodeptr) since nodeptr
    // is private, so we traverse the list twice to get what we want :)
    bool ans = false;
    int i = 0, to_delete = -1;
    for (auto it = people.begin(); it != people.end(); ++it) {
        if ((*it)->get_cpf() == cpf) {
            to_delete = i;
        }
        i++;
    }

    if (to_delete >= 0) {
        ans = people.remove_by_index(to_delete);
    }

    return ans;
}

bool PersonManager::remove_type_by_cpf(const std::string& cpf, const std::string& type) {
    auto comparator = Person::compare_by_cpf_and_type(cpf, type);
    return people.remove_by_value(nullptr, comparator);
}

// previous attempt didnt work...
// revising this code, i believe i can make it work by manually increment my iterator
/*bool PersonManager::remove_all_by_type(const std::string& type) {*/
/*    auto comparator = Person::compare_by_type(type);*/
/*    bool removed_any = false;*/
/**/
/*    // Keep removing while we can find matches*/
/*    int i = 0;*/
/*    for (auto it = people.begin(); it != people.end(); i++) {*/
/*        auto next = it.next();*/
/*        if ((*it)->get_type() == type) {*/
/*            people.remove_by_index(i);*/
/*            removed_any = true;*/
/*        } */
/*        it = next;*/ // cant do this, needs to overload the equal_to
/*    }*/
/**/
/*    return removed_any;*/
/*}*/

// thought of a better way to implement.
/*bool PersonManager::remove_all_by_type(const std::string& type) {*/
/*    bool removed_any = false;*/
/*    bool found;*/
/**/
/*    do {*/
/*        found = false;*/
/*        int i = 0;*/
/*        for (auto it = people.begin(); it != people.end(); ++it, ++i) {*/
/*            if ((*it)->get_type() == type) {*/
/*                people.remove_by_index(i);*/
/*                found = true;*/
/*                removed_any = true;*/
/*                break;  // this break is actually essential, idk how to remove this...*/
/*            }*/
/*        }*/
/*    } while (found);  // did double loop siunce my previous attempt ^ up there is not working.*/
/**/
/*    return removed_any;*/
/*}*/

//using new list function
bool PersonManager::remove_all_by_type(const std::string& type) {
    bool removed_any = false;

    for (auto it = people.begin(); it != people.end(); ) {
        if ((*it)->get_type() == type) {
            // remove returns end() or does next()
            it = people.remove(it);
            removed_any = true;
        } else {
            // manually increment the iterator in case we didnt need to delete this.
            ++it;
        }
    }

    return removed_any;
}


bool PersonManager::remove_all() {
    while(people.pop());
    return people.is_empty();
}

// file handler

void PersonManager::save_to_file(const std::string& filename) {
    try {
        std::ofstream file(filename, std::ios::out);
        if (!file.is_open()) {
            throw std::ios_base::failure("Failed to open file for writing.");
        }

        for (auto it = people.begin(); it != people.end(); ++it) {
            Person* person = *it;
            file << person->get_type() << ",";
            file << person->get_name() << ",";
            file << person->get_cpf() << ",";
            file << person->get_age() << ",";
            file << person->get_birthday().get_day() << "/";
            file << person->get_birthday().get_month() << "/";
            file << person->get_birthday().get_year();
            if (person->get_type() == "Professor") {
                Teacher* teacher = static_cast<Teacher*>(person);
                file << "," << teacher->get_department() << "," << teacher->get_salary();
            } else if (person->get_type() == "Aluno") {
                Student* student = static_cast<Student*>(person);
                file << "," << student->get_course() << "," << student->get_student_id();
            }
            file << std::endl;
        }

        file.close();
    } catch (const std::ios_base::failure& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while saving to the file." << std::endl;
    }
}

void PersonManager::load_from_file(const std::string& filename) {
    try {
        std::ifstream file(filename, std::ios::in);
        if (!file.is_open()) {
            throw std::ios_base::failure("File not found or cannot be opened for reading.");
        }

        std::string line;
        while (std::getline(file, line)) {
            try {
                // by line so we can get the most out of what is saved.
                std::stringstream ss(line);
                std::string type, name, cpf, department, course;
                int age, day, month, year, student_id;
                double salary;

                std::getline(ss, type, ',');
                std::getline(ss, name, ',');
                std::getline(ss, cpf, ',');
                ss >> age;
                ss.ignore(1); // Skip comma
                ss >> day;
                ss.ignore(1);
                ss >> month;
                ss.ignore(1);
                ss >> year;

                if (type == "Professor") {
                    ss.ignore(1); // Skip comma
                    std::getline(ss, department, ',');
                    ss >> salary;
                    add_person(new Teacher(name, cpf, age, Date(day, month, year), department, salary));
                } else if (type == "Aluno") {
                    ss.ignore(1); // Skip comma
                    std::getline(ss, course, ',');
                    ss >> student_id;
                    add_person(new Student(name, cpf, age, Date(day, month, year), course, student_id));
                }
            } catch (...) {
                std::cerr << "Error parsing line: " << line << std::endl;
            }
        }

        file.close();
    } catch (const std::ios_base::failure& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while loading from the file." << std::endl;
    }
}

