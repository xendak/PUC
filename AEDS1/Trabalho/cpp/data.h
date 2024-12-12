#ifndef DATA_H
#define DATA_H

#include <iostream>

class Date {
    private:
        int day;
        int month;
        int year;

    public:
        Date();
        Date(int day, int month, int year);
        ~Date();

        bool check_date();
        bool change_date();
        std::string list_month_by_name();
        int get_days_in_month();
        void print();
        std::string print_as_string();

        // inline
        int get_day() const { return day; }
        int get_month() const { return month; }
        int get_year() const { return year; }

        static int get_current_month();
        static Date get_current_date();

        void set_day(int day);
        void set_month(int month);
        void set_year(int year);

        bool is_leap_year();
        bool is_valid_date();

};

#endif // DATA_H


