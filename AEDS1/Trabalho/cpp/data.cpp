#include <iostream>
#include <chrono>
#include <ctime>

#include "data.h"

Date::Date() {
    day = 0;
    month = 0;
    year = 0;
}

Date::~Date() {}

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

int Date::get_current_month() {
    return get_current_date().get_month();
}

Date Date::get_current_date() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    struct tm *parts = std::localtime(&now_c);

    return Date(1900 + parts->tm_year, 1    + parts->tm_mon, parts->tm_mday);
}

std::string Date::print_as_string() {
    std::string s = std::to_string(day);
    s.append("/");
    s.append(std::to_string(month));
    s.append("/");
    s.append(std::to_string(year));
    return s; 
}

void Date::print() {
    std::cout << day  << "/"  << month  << "/"  << year  << "/";

}
