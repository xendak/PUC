#include <iostream>

class List {
    private:
        struct Node {
            Node* next;
            Node* prev;
            int data;

            Node(int val);
        };
        typedef struct Node* nodeptr;

        Node* head;
        int size;

    public:
        int num;

        List();
        List(int obj);
        ~List();

        // LIFO
        bool push(int obj);
        bool pop();
        bool remove_by_index(int index);
        bool remove_by_valor(int val);
        void print();
};

List::Node::Node(int val) {
    data = val;
    next = nullptr;
    prev = nullptr;
}

List::List() {
    head = nullptr;
    size = 0;
}

List::List(int obj) {
   head = new Node(obj);
   head->next = head;
   head->prev = head;
   size = 1;
}

List::~List() {
    while(size)
        pop();
}

bool List::pop() {
    bool res = false;
    if (size < 1) { res = false; }
    else if (size == 1) {
        delete head;
        head = nullptr;
        res = true;
    } else {
        // get the last(tail) object, make its pointers next/prev point through the tail, delete tail.
        nodeptr tail = head->prev;
        head->prev = tail->prev;
        head->prev->next = head;
        delete tail;
        res = true;
    }

    if (res) size--;

    return res;
}

bool List::remove_by_index(int index) {
    bool res = false;
    if (index > size || index < 0) { res = false; }
    else if (size == 1 && index == 0) {
        delete head;
        head = nullptr;
        res = true;
    } else if (size > 1) {
        nodeptr curr = head;
        int i = 0;
        while (!res) {
            if (index == i) {
                if (index == 0) { head = head->next; }
                curr->next->prev = curr->prev;
                curr->prev->next = curr->next;
                delete curr;
                res = true;
            } else {
                curr = curr->next;
                i++;
            }
        }
    }

    if (res)
        size--;
    return res;
}

bool List::remove_by_valor(int val) {
    bool res = false;
    if (size == 1 && head->data == val) { 
        delete head;
        head = nullptr;
        res = true;
    }
    else if (size > 1) {
        nodeptr curr = head;
        do {
            if (val == curr->data) {
                if (head == curr) { head = head->next; }
                curr->next->prev = curr->prev;
                curr->prev->next = curr->next;
                delete curr;
                res = true;
            } else {
                curr = curr->next;
            }
        } while(curr != head && !res);
    }
    if (res)
        size--;
    // if errror catching, val not found.
    return res;
}


bool List::push(int obj) {
    nodeptr newNode = new Node(obj);
    bool res = false;
    if (newNode != nullptr) { 
        // increment one since we already created a new node regardless
        // possibly cant fail anymore?
        size++;

        if (head == nullptr) {
            head = newNode;
            head->next = head;
            head->prev = head;
        } else {
            // using tail is O(1), while my old method was O(n)....
            nodeptr tail = head->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
        }
        res = true;
    }
    return res;
}

void List::print() {
    nodeptr curr = head;
    std::cout << "Size: " << size << "\t||\t";

    if (size) {
        for(int i = 0; i < size; i++) {
            std::cout << i << ": " << curr->data << "\t";
            curr = curr->next;
        }
    }
    std::cout << std::endl;
}

int main() {
    List testing = List();
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
