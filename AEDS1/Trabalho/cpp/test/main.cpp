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
        bool remove_by_valor(int obj);
        void print();
};

// WITH tail pointer


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
   size = 1;
}

List::~List() {
    if (size == 1) {
        delete head;
    } else {
        nodeptr curr = head;
        while (size) {
            nodeptr next = curr->next;
            delete curr;
            curr = next;
            size--;
        }
        /*delete head;*/
    }
}

bool List::pop() {
    if (size < 1) { return false; }
    else if (size == 1) {
        head->prev = nullptr;
        head->next = nullptr;
        delete head;

    } else {
        nodeptr tail = head->prev;
        if (tail == nullptr) { return false; }

        std::cout << "Deleting: " << tail->data << std::endl;
        tail->next = nullptr;
        head->prev = tail->prev;
        std::cout << "Head: " << head->data << std::endl;
        std::cout << "New: Head->prev: " << head->prev->data << std::endl;
        tail->prev = nullptr;
        head->prev->next = head;
        std::cout << "New: Head->prev->next: " << head->prev->next->data << std::endl;
        std::cout << "New: Head->next->next: " << head->next->next->data << std::endl;
        /*tail->prev->next = head;*/
        delete tail;
    }

    size--;
    return true;
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
            nodeptr curr = head;
            while (curr->next != head) {
                curr = curr->next;
            }
            /*std::cout << "Curr: " << curr->data << "\t";*/
            /*std::cout << "Curr->next: " << curr->next->data << "\t";*/
            /*std::cout << "Curr->prev: " << curr->prev->data << "\t" << std::endl;*/
            curr->next = newNode;
            newNode->prev = curr;
            head->prev = newNode;
            newNode->next = head;
            /*std::cout << "Curr: " << curr->data << "\t";*/
            /*std::cout << "Curr->next: " << curr->next->data << "\t";*/
            /*std::cout << "Curr->prev: " << curr->prev->data << "\t" << std::endl;*/

        }
        
        res = true;
    }
    return res;
}

void List::print() {
    nodeptr curr = head;
    std::cout << "Size: " << size << std::endl;

    for(int i = 0; i < size; i++) {
        std::cout << i << ": " << curr->data << std::endl;
        curr = curr->next;
    }
    if (size)
        std::cout << "Head: " << head->data << "\tTail: " << head->prev->data << std::endl;
}

int main() {
    List testing = List();
    testing.push(5);
    testing.push(7);
    testing.push(2);
    /*testing.push(5);*/
    /*testing.push(22);*/
    /*testing.print();*/
    /*testing.push(13);*/
    /*testing.print();*/
    /*testing.push(25);*/
    /*testing.print();*/
    testing.print();
    testing.pop();
    testing.print();
    testing.pop();
    testing.pop();
    testing.print();
    // use after free?
    /*testing.push(2);*/
    /*testing.print();*/
    /*std::cout << "does it reach here" << std::endl;*/

    return 0;
}
