#include <iostream>

int sz = 200;
int MAX = 500000000;
#include <new>
using std::bad_alloc;

int main() {
    double* ptr[sz];

    std::cout << "before" << std::endl;
    for (int i = 0; i < sz; i++) {
        ptr[i] = new double[MAX];
        std::cout << i << "\t";
    }

    for (int i = 0; i < sz; i++) {
        delete(ptr[i]);
        std::cout << i << "\t";
    }

    try {
        std::cout << "trying" << std::endl;
        for (int i = 0; i < sz; i++) {
            ptr[i] = new double[MAX];
            std::cout << i << "\t";
            throw i;
        }

        std::cout << "this doesnt print, post throw" << std::endl;
    } catch ( int x ) {
        std::cout << "caught x = " << x <<  std::endl;
    } catch ( bad_alloc memoryAllocationException ) {
        std::cout << "err i = " << std::endl;
    } catch (...) {
        std::cout << "general case" << std::endl;
    }

    std::cout << "after" << std::endl;

    return 0;
}
