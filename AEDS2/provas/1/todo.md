# Q1
    - [ ] use java stuff that i didn't have time to do on the exam because i didn't remember how to use proper java functions.
    - [ ] remove bubble sort, either selection or insertion at minimum ?
    - [ ] user proper struct to hold the terms (does java have struct? or need to use classes.)
    - [ ] implement a proper lineParsing
    - [ ] after we do our proper lineParse, then we need to actually use java inbuilt ones so i can learn.
    - [x] finished implementing in C.
# Q2
    - maybe we can try removing the strict checking? and do a heuristic? we don't really need to check all chars.


# in C lets try more stuff.
To create a **generic bubble sort** that works on both **arrays** and **linked lists**, you need to abstract the following operations:
1. **Accessing elements** (e.g., indices for arrays, node pointers for lists),
2. **Comparing elements** (same as before),
3. **Swapping elements/nodes** (different logic for arrays vs. lists).

Here’s how to design it:

---

### 1. **Define Function Pointers for Data Structure Operations**
```c
// Function pointer types
typedef void* (*GetNextFunc)(void* current);  // Get next element/node
typedef void (*SwapFunc)(void** ds, void* a, void* b); // Swap elements/nodes
```

---

### 2. **Implement Bubble Sort Using These Functions**
```c
void bubble_sort_generic(
    void** ds,               // Data structure (array or list head)
    bool (*cmp)(const void*, const void*), // Comparison function
    GetNextFunc get_next,    // How to traverse to the next element
    SwapFunc swap            // How to swap elements/nodes
) {
    bool swapped;
    void *current, *next;
    
    do {
        swapped = false;
        current = *ds;
        next = get_next(current);

        while (next != NULL) {
            if (cmp(current, next)) {
                swap(ds, current, next); // Swap elements/nodes
                swapped = true;
            } else {
                current = next;
            }
            next = get_next(current);
        }
    } while (swapped);
}
```

---

### 3. **Array-Specific Functions**
#### For arrays, track indices internally. Use a helper struct:
```c
typedef struct {
    void* array;    // Pointer to the array
    size_t index;   // Current index
    size_t elem_size; // Size of each element
} ArrayIterator;

// Get next element in the array
void* array_get_next(void* iterator) {
    ArrayIterator* it = (ArrayIterator*)iterator;
    it->index++;
    return (char*)it->array + (it->index * it->elem_size);
}

// Swap two array elements by indices
void array_swap(void** ds, void* a, void* b) {
    ArrayIterator* it = (ArrayIterator*)*ds;
    size_t i = ((char*)a - (char*)it->array) / it->elem_size;
    size_t j = ((char*)b - (char*)it->array) / it->elem_size;

    char temp[it->elem_size];
    memcpy(temp, a, it->elem_size);
    memcpy((char*)it->array + i * it->elem_size, b, it->elem_size);
    memcpy((char*)it->array + j * it->elem_size, temp, it->elem_size);
}
```

---

### 4. **Linked List-Specific Functions**
Assume a linked list node structure:
```c
typedef struct Node {
    struct Node* next;
    // ... data fields (e.g., country, car)
} Node;

// Get next node in the list
void* list_get_next(void* current) {
    return ((Node*)current)->next;
}

// Swap two adjacent nodes in the list
void list_swap(void** ds, void* a, void* b) {
    Node** head = (Node**)ds;
    Node* nodeA = (Node*)a;
    Node* nodeB = (Node*)b;
    Node* prev = NULL;
    Node* curr = *head;

    // Find the node before A
    while (curr != NULL && curr != nodeA) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == NULL) { // A is the head
        *head = nodeB;
    } else {
        prev->next = nodeB;
    }
    nodeA->next = nodeB->next;
    nodeB->next = nodeA;
}
```

---

### 5. **Usage Examples**
#### Sorting an **array** of `country` structs:
```c
country countries[100];
// Initialize array...

ArrayIterator it = {
    .array = countries,
    .index = 0,
    .elem_size = sizeof(country)
};

bubble_sort_generic(
    (void**)&it,        // Pass iterator as "data structure"
    compare_countries,  // Comparison function
    array_get_next,     // Array traversal
    array_swap          // Array swap
);
```

#### Sorting a **linked list** of `car` structs:
```c
Node* head = /* ... linked list initialization ... */;

bubble_sort_generic(
    (void**)&head,      // Pass head pointer
    compare_cars,       // Comparison function
    list_get_next,      // List traversal
    list_swap           // List node swap
);
```

---

### Key Ideas:
- **Generic Traversal**: Use `GetNextFunc` to abstract element access (indices for arrays, `next` pointers for lists).
- **Generic Swapping**: Use `SwapFunc` to handle swaps (memory copy for arrays, pointer adjustments for lists).
- **Data Structure Handle**: Pass a `void**` that can represent either an array iterator or a list head pointer.

This approach allows the same `bubble_sort_generic` function to work with **any data structure** by providing the appropriate traversal and swap functions.
