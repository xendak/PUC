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

        bool push(int obj);
        bool pop();
        bool pop_by(int obj);
        void print();
};

// WITH tail pointer


List::Node::Node(int val) {
    this->data = val;
    this->next = nullptr;
    this->prev = nullptr;
}

List::List() {
    this->head = nullptr;
    this->size = 0;
}

List::List(int obj) {
   head = new Node(obj);
   size = 1;
}

List::~List() {
    nodeptr curr = head;
    while (curr != nullptr) {
        nodeptr next = curr->next;
        delete curr;
        curr = next;
    }
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
        } else {
            nodeptr curr = head;
            while (curr->next) {
                curr = curr->next;
            }
            curr->next = newNode;
            newNode->prev = curr;
            head->prev = newNode;
        }
        
        res = true;
    }
    return res;
}

bool List::pop() {

}

void List::print() {
    nodeptr curr = head;
    int i = 0;
    std::cout << "Size: " << size << std::endl;

    while(curr) {
        std::cout << i << ": " << curr->data << std::endl;
        curr = curr->next;
        i++;
    }
    std::cout << "Head: " << head->data << "\tTail: " << head->prev->data << std::endl;
}

int main() {
    List testing = List(7);
    testing.push(5);
    testing.push(13);
    testing.print();
    testing.push(25);
    testing.print();
    std::cout << "does it reach here" << std::endl;

    return 0;
}
