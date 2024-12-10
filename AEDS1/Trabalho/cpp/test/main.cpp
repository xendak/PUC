#include "list.h"

int main() {
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
    testing.remove_by_valor(5);
    testing.remove_by_valor(2);
    testing.remove_by_valor(7);
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

    return 0;
}
