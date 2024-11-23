#include <iostream>

#include "data.h"


class Person {
    private:
        std::string name;
        int age;
        float wage;
        Date bday;

    public:
        Person(std::string name, int age, float wage, Date bday);
        bool print();
        void operator=(Person const& np);
        /*bool delete_person();*/
        /*bool add_person();*/

};

class People {
    private:
        Person* p;
        int size;

    public:
        People();
        bool add_person(Person* p);
        bool delete_person();
        Person* search_person();
};


class List {
    private:

};
