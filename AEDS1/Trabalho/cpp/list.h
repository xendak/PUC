#pragma once

#include <iostream>
#include <functional>

#include <type_traits> // std::is_pointer

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

        bool remove_node(nodeptr current_node);

    public:
        // attempt at Iterators

        class Iterator {
            private:
                nodeptr current;
                int pos;
                int list_size;

            public:
                // trying to use forward iterator like vecs, i liked that :)
                using value_type = T;
                using reference = T&;
                using pointer = T*;
                using iterator_category = std::forward_iterator_tag;

                // trying one liner? idk if this is better than declaring after the class...
                Iterator(nodeptr node, int pos, int size) : current(node), pos(pos), list_size(size) {}

                // get actual value, dereference.
                T& operator*();

                // apparently this is pre increment , so i++;
                Iterator& operator++();

                // this should be ++i;
                Iterator operator++(int);

                bool operator==(const Iterator& other) const;
                bool operator!=(const Iterator& other) const;

                T* next();

                friend class List;
        };

        // Public List Methods
        List();
        List(T obj);
        ~List();

        // LIFO
        bool push(T obj);
        bool pop();
        bool is_empty() { return size == 0; }


        nodeptr find_by_index(int index);
        bool remove_by_index(int index);

        Iterator begin() const;
        Iterator end() const;

        template<typename Comparator = std::equal_to<T>>
        nodeptr find_by_value(const T& val, Comparator comp = Comparator());
        template<typename Comparator = std::equal_to<T>>
        bool remove_by_value(const T& val, Comparator comp = Comparator());

        typename List<T>::Iterator remove(Iterator it);

        template<typename Formatter = std::function<void (const T&)>>
        void print(Formatter fmt = [](const T& val) { std::cout << val; });

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
    while(pop());
}

template<typename T>
bool List<T>::remove_node(nodeptr to_remove) {
    bool res = false;
    if (size < 1 || to_remove == nullptr) { res = false; }
    else if (size == 1) {
        if constexpr (std::is_pointer<T>::value) 
            delete head->data;
        delete head;

        head = nullptr;
        res = true;
    } else {
        if (to_remove == head) { head = head->next; }

        to_remove->next->prev = to_remove->prev;
        to_remove->prev->next = to_remove->next;

        if constexpr (std::is_pointer<T>::value)
            delete to_remove->data;
        delete to_remove;
        res = true;
    }

    if (res) size--;

    return res;
}

template <typename T>
bool List<T>::pop() {
    bool res = false;
    if (size < 1) 
        res = false;
    else
        res = remove_node(head->prev);

    return res;
}

template <typename T>
typename List<T>::nodeptr List<T>::find_by_index(int index) {
    nodeptr ret = nullptr;

    if (index > size || index < 0) 
        ret = nullptr;
    else {
        nodeptr curr = head;
        for (int i = 0; i < index; i++)
            curr = curr->next;

        ret = curr;
    }

    return ret;
}

template <typename T>
bool List<T>::remove_by_index(int index) {
    bool res = false;
    if (index < 0 || index > size) 
        res = false;
    else {
        nodeptr to_remove = find_by_index(index);
        if (to_remove == nullptr)
            res = false;
        else {
            res = remove_node(to_remove);
        }
    }

    return res;
}

template <typename T>
template <typename Comparator>
typename List<T>::nodeptr List<T>::find_by_value(const T& val, Comparator comp) {
    nodeptr ret = nullptr;
    nodeptr curr = head;

    do {
        if (comp(curr->data))
            ret = curr;
        else
            curr = curr->next;
    } while (curr != head && !ret);

    return ret;
}

template <typename T>
template <typename Comparator>
bool List<T>::remove_by_value(const T& val, Comparator comp) {
    bool res = false;
    nodeptr to_remove = find_by_value(val, comp);

    if(to_remove)
        res = remove_node(to_remove);

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
            // be smart and grab the tail
            // since we are making a doubly linked list
            // might aas well use O(1)
            nodeptr tail = head->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
        res = true;
    }
    return res;
}

template<typename T>
template<typename Formatter>
void List<T>::print(Formatter fmt) {
    nodeptr curr = head;

    std::cout << "Size: " << size << std::endl;

    if (size) {
        for(int i = 0; i < size; i++) {
            fmt(curr->data);
            curr = curr->next;
        }
    }
    std::cout << std::endl;
}

// Iterators implementation

template<typename T>
T& List<T>::Iterator::operator*() {
    return current->data;
}

template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
    if (pos < list_size) {
        current = current->next;
        ++pos;
    }
    return *this;
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    if (pos < list_size) {
        current = current->next;
        ++pos;
    }
    return temp;
}

template<typename T>
bool List<T>::Iterator::operator==(const Iterator& other) const {
    return pos == other.pos && current == other.current;
}

template<typename T>
bool List<T>::Iterator::operator!=(const Iterator& other) const {
    return pos != other.pos;
}

template<typename T>
typename List<T>::Iterator List<T>::remove(Iterator it) {
    if (it == end()) return end();

    nodeptr to_remove = it.current;
    Iterator next(it.current->next, it.pos + 1, it.list_size);

    remove_node(to_remove);
    return next;
}

template<typename T>
T* List<T>::Iterator::next() {
    if (!current || pos >= list_size) {
        return nullptr; // End of list
    }
    T* data = &current->data;
    current = current->next;
    ++pos;
    return data;
}

// List iterator begin
template<typename T>
typename List<T>::Iterator List<T>::begin() const {
    return Iterator(head, 0, size);
}

template<typename T>
typename List<T>::Iterator List<T>::end() const {
    return Iterator(head, size, size);
}
