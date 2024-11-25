#include <iostream>

#include "data.h"


class Person {
    private:
        std::string name;
        int age;
        Date bday;

    public:
        Person();
        Person(std::string name, int age, Date bday);
        ~Person();

        bool print();
        void operator=(Person const& np);
        /*bool delete_person();*/
        /*bool add_person();*/

};

// tentativa de simular <LIST>
class People {
    private:
        Person p;
        void* next;
        void* prev;
        static int size;

    public:
        People();
        People(Person p);
        ~People();

        bool add_person(Person p);
        bool delete_person(); // acccept some kind of search eventually
        Person* search_person();
};


class List {
    private:

};
