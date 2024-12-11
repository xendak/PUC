#include "list.h"

void full_test();
void pop_test();

void remove_by_index_test();
void find_by_index_test();

void remove_by_value_test();
void find_by_value_test();

void print_formatter_test();

void iterator_test();

int main() {
    iterator_test();
    return 0;
}

void iterator_test() {
    List<int> list;
    list.push(10);
    list.push(20);
    list.push(30);

    auto it = list.begin();
    while (int* val = it.next()) {
        std::cout << *val << std::endl;
    }
    std::cout << "implementation 2\n";
    for (int v : list)
        std::cout << v << "\t";
    
    std::cout << "\nimplementation 3\n";
    /*for (auto i = list.begin(); i != list.end(); ++i) {*/
    // this line can so also have ++i or i++;, ++i being the ideal solution
    // since no copy would be needed.
    for (auto i = list.begin(); i != list.end(); i.next()) {
        std::cout << *i << "\t";
    }
}

void print_formatter_test() {
    List<int> list;
    list.push(10);
    list.push(20);

    // Use a custom formatter
    list.print([](const int& val) { std::cout << "Value: " << val << "\n"; });

    // Use a simple formatter for default behavior
    list.print([](const int& val) { std::cout << val << " "; });
}

void find_by_value_test() {
    List<int> testing;
    testing.push(15);
    testing.push(5);
    testing.push(7);
    testing.push(2);
    testing.print();
    testing.find_by_value(5);
}

void full_test() {
    List<int> testing;
    testing.push(5);
    testing.push(7);
    testing.push(2);
    testing.print();
    testing.pop();
    testing.pop();
    testing.pop();
    testing.print();
    testing.push(5);
    testing.push(7);
    testing.push(2);
    testing.print();
    testing.remove_by_value(5);
    testing.remove_by_value(2);
    testing.remove_by_value(7);
    testing.print();
    testing.push(5);
    testing.push(7);
    testing.push(2);
    testing.print();
    testing.remove_by_index(0);
    testing.print();
    testing.remove_by_index(1);
    testing.print();
    testing.remove_by_index(0);
    testing.print();
}

void pop_test() {
    List<int> testing;
    testing.push(5);
    testing.push(7);
    testing.push(2);
    testing.print();
    testing.pop();
    testing.print();
    testing.pop();
    testing.print();
    testing.pop();
    testing.print();
}

void remove_by_index_test() {
    List<int> testing;
    testing.push(5);
    testing.push(7);
    testing.push(2);
    testing.print();
    testing.remove_by_index(0);
    testing.print();
    testing.remove_by_index(1);
    testing.print();
    testing.remove_by_index(0);
    testing.print();
}

void remove_by_value_test() {
    List<int> testing;
    testing.push(5);
    testing.push(7);
    testing.push(2);
    testing.print();
    testing.remove_by_value(5);
    testing.print();
    testing.remove_by_value(2);
    testing.print();
    testing.remove_by_value(7);
    testing.print();
}

