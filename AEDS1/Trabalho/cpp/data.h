#ifndef DATA_H
#define DATA_H

#include <iostream>

class Date {
    private:
        int day;
        int month;
        int year;

    public:
        Date(int day, int month, int year);
        bool check_date();
        bool change_date();
        std::string list_month_by_name();
        int get_days_in_month();
        bool print();

    private:
        bool is_leap_year();
        bool is_valid_date();
        void set_day(int day);
        void set_month(int month);
        void set_year(int year);

};

#endif // DATA_H


