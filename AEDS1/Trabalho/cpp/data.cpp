#include <iostream>

#include "data.h"

Date::Date(int day, int month, int year) {
    set_day(day);
    set_month(month);
    set_year(year);
}

void Date::set_day(int day) {
    this->day = day;
}

void Date::set_month(int month) {
    this->month = month;
}

void Date::set_year(int year) {
    this->year = year;
}

    /**/
    /*public:*/
    /*    Date New(int day, int month, int year);*/
    /*    bool check_date();*/
    /*    bool change_date();*/
    /*    std::string list_month_by_name();*/
    /*    int get_days_in_month();*/
    /*    bool print();*/
    /**/
    /*private:*/
    /*    bool is_leap_year();*/
    /*    bool is_valid_date();*/
