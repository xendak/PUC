#pragma once

#include <iostream>

template<typename T>
class List {
    private:
        struct Node {
            Node* next;
            Node* prev;
            T data;

            Node(T val);
        };
        typedef struct Node* nodeptr;

        Node* head;
        int size;

    public:
        List();
        List(T obj);
        ~List();

        // LIFO
        bool push(T obj);
        bool pop();
        bool remove_by_index(int index);
        template<typename Comparator = std::equal_to<T>>
        bool remove_by_valor(const T& val, Comparator comp = Comparator{});
        void print();
};

template <typename T>
List<T>::Node::Node(T val) {
    data = val;
    next = nullptr;
    prev = nullptr;
}

template <typename T>
List<T>::List() {
    head = nullptr;
    size = 0;
}

template <typename T>
List<T>::List(T obj) {
   head = new Node(obj);
   head->next = head;
   head->prev = head;
   size = 1;
}

template <typename T>
List<T>::~List() {
    while(size)
        pop();
}

template <typename T>
bool List<T>::pop() {
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

template <typename T>
bool List<T>::remove_by_index(int index) {
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

template <typename T>
template <typename Comparator>
bool List<T>::remove_by_valor(const T& val, Comparator comp) {
    bool res = false;
    if (size == 1 && comp(head->data, val)) { 
        delete head;
        head = nullptr;
        res = true;
    }
    else if (size > 1) {
        nodeptr curr = head;
        do {
            if (comp(val, curr->data)) {
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


template <typename T>
bool List<T>::push(T obj) {
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

template <typename T>
void List<T>::print() {
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
