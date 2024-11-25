#include <iostream>
#include <stdio.h>

class List {
    private:
        List* next;
        List* prev;

    public:
        int size;
        int num;

        /*List();*/
        List(int obj);
        ~List();

        bool push(int n);
        bool pop(int n);
        void print();
};

/**/
/*List::List() {*/
/*    this->next = NULL;*/
/*    this->prev = NULL;*/
/*    this->size = 1;*/
/*}*/
/**/

List::List(int obj) {
    this->next = NULL;
    this->prev = NULL;
    this->size = 1;
    this->num = obj;
}

List::~List() {
    List* curr = this;
    for (int i = 0; i < this->size; i++) {
        if (this->next != NULL)
            curr->next = this->next;
        delete this->next;
        delete this->prev;
    }
    delete this;
    delete curr;
}

bool List::push(int n) {
    List* to_be_pushed = new List(n);
    if (to_be_pushed == NULL) { return false; }
    List* curr = this;
    if (curr == NULL) { return false; }

    this->prev = to_be_pushed;

    do {
        if (curr->next == NULL)  {
            // add new element here
            this->next = to_be_pushed;
            to_be_pushed->prev = this;
        }
        if (this->next != NULL)
            curr = this->next;
    } while(curr->next != NULL);
    this->size++;
    return true;
}

void List::print() {
    /*List* curr = this;*/
    int i = 0;

    std::cout << "size: " << this->size << std::endl;
    for (List* curr = this; curr->next != NULL ; curr = curr->next) {
        std::cout << i << " = " << curr->num << std::endl;
        i++;
        /*curr = this->next;*/
    }
}

int main() {
    List testing = List(7);
    testing.push(5);
    testing.print();

    return 0;
}
