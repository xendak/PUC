#include <iostream>
#include "data.h"


class Person {
    protected:
        std::string name;
        std::string cpf;
        int age;
        Date bday;

    public:
        Person();
        Person(std::string name, std::string cpf, int age, Date bday);
        
        // nada é alocado dinamicamente nessa classe, mas é bom tratar of destruturos individucalmente caso exista divergencia
        virtual ~Person(); 

        virtual bool print() = 0;

        std::string get_name() const { return name; }
        std::string get_cpf() const { return cpf; }
        Date get_birthday() const { return bday; }
        int get_age() const { return age; }

        void operator=(const Person& np);
};

class Teacher : public Person {
    private:
        std::string department;
        double salary;
        
    public:
        Teacher();
        Teacher(std::string name, std::string cpf, int age, Date bday,
                std::string department, double salary);
        ~Teacher() override;

        bool print() override;
        std::string get_department() const { return department; }
        double get_salary() const { return salary; }
};

class Student : public Person {
    private:
        std::string course;
        int enrollment;
        
    public:
        Student();
        Student(std::string name, std::string cpf, int age, Date bday,
                std::string course, int enrollment);
        ~Student() override;

        bool print() override;

        std::string get_course() const { return course; }
        int get_enrollment() const { return enrollment; }
};
