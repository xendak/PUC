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
        
        virtual ~Person() = default; 

        // this makes it an abstract class
        virtual bool print() = 0;
        virtual std::string get_type() = 0;
        /*bool print();*/

        // const since we want to make sure we cant be allowed to make changes
        std::string get_name() const { return name; }
        std::string get_cpf() const { return cpf; }
        Date get_birthday() const { return bday; }
        int get_age() const { return age; }

        void operator=(const Person& np);


        // the first [name = this->name], captures current->name, inside var name.
        // then we pass it as value to the function we're creating, which will use
        // a const Person& other (to prevent changes), and our captured value.
        // then we return the actual function because we're creating a comparator
        // function to pass to some class that will need this.
        static auto compare_by_name(const std::string& to_find) {
            return [to_find](const Person* person) {
                return person->get_name() == to_find;
            };
        }
        static auto compare_by_cpf(const std::string& to_find) {
            return [to_find](const Person* person) {
                return person->get_cpf() == to_find;
            };
        }
};

class Teacher : public Person {
    private:
        std::string department;
        double salary;
        
    public:
        Teacher();
        Teacher(std::string name, std::string cpf, int age, Date bday,
                std::string department, double salary) : Person(name, cpf, age, bday), department(department), salary(salary) {} ;
        ~Teacher() override;

        std::string get_type() override { return "Teacher"; } ;
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
                std::string course, int enrollment) : Person(name, cpf, age, bday), course(course), enrollment(enrollment) {} ;

        ~Student() override;

        std::string get_type() override { return "Student"; };
        bool print() override;

        std::string get_course() const { return course; }
        int get_enrollment() const { return enrollment; }
};
