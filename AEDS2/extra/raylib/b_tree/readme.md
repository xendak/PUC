# 2-3-4 Tree: Comprehensive Guide to Operations and Recursive Processes

## Core Properties

A 2-3-4 tree is a self-balancing search tree with the following properties:

1. **Node Types**:
   - **2-node**: 1 key, 2 children
   - **3-node**: 2 keys, 3 children
   - **4-node**: 3 keys, 4 children
2. **Balanced Structure**: All leaves are at the same depth
3. **Sorted Order**: Keys in a node are in ascending order; subtree keys are
   between parent keys

---

## Insertion with Recursion

### Process (Top-down approach)

1. **Split full nodes on descent**:
   - If root is full (4-node), split it first
   - For any full child encountered during descent:
     - Move middle key to parent
     - Split remaining keys into two new nodes
     - Adjust parent's child pointers
2. **Insert at leaf**:
   - Find appropriate leaf (non-full due to pre-splitting)
   - Insert new key in sorted position

### Recursive Workflow

```c
void insertNonFull(Node* node, int key) {
  if (leaf) {
    // Insert key in sorted position
  } else {
    int child_index = find_child_index(key);
    if (child is full) {
      splitChild(node, child_index);  // Modify current node
      // After split, adjust child_index if needed
      if (key > node->keys[child_index]) {
        child_index++;  // Move to new right sibling
      }
    }
    insertNonFull(appropriate_child, key); // Recurse deeper
  }
}
```

### Key Insight

- Preemptively split full nodes during descent to guarantee leaf space
- No backward propagation needed after modification

#### Adjusting Child Index After Split

When splitting a child node:

1. Middle key moves up to parent
2. Original child is split into two nodes
3. Parent gains a new child pointer

**Example**:

```
Parent (before): [10, 30] with children C0, C1, C2
Child C1 (full): [15, 20, 25]

After splitChild(parent, 1):
Parent (after): [10, 20, 30] with children:
  C0: keys < 10
  C1 (new): [15]
  C2 (new): [25]
  C3: keys > 30

Inserting key=22:
- Before split: Would go to C1 (15-20-25)
- After split: 22 > 20 (new parent key at index 1)
- Adjust child_index from 1 → 2 (pointing to C2)
```

---

## Deletion with Recursion

### Process (Ensure min keys before descent)

1. **Handle key in internal node**:
   - Replace with predecessor/successor
   - Recursively delete replacement key
2. **Ensure min keys before descent**:
   - Borrow from sibling if possible
   - Merge with sibling if borrowing fails
3. **Delete from leaf**:
   - Remove key if node has > min keys

### Recursive Workflow

```c
void deleteInternal(Node* node, int key) {
  if (key in node) {
    if (leaf) remove_key();
    else {
      // Replace with predecessor/successor
      deleteInternal(child, replacement_key); // Recurse
    }
  } else {
    Node* child = next_child(key);
    if (child has min keys) {
      // Check borrowing options
      if (can_borrow_left) rotate_right();
      else if (can_borrow_right) rotate_left();
      else mergeWithSibling();
    }
    deleteInternal(child, key); // Recurse to child
  }
}
```

### Key Insight

- Ensure every node visited during descent has > min keys (≥2) through
  borrowing/merging
- Operations are local to current node + direct children

---

## Borrowing Operations

### Borrow from Left Sibling (Rotate Right)

**Conditions**:

```c
bool can_borrow_left = (leftSibling != NULL) &&
                       (leftSibling->num_keys > MIN_KEYS);
```

**Process**:

1. Move parent separator key down to child
2. Move rightmost key from left sibling to parent
3. Move rightmost child from left sibling if exists

**Example**:

```
Before:
  Parent: [20]
  Left: [10,15]   Right: [25] (min keys!)

After rotate:
  Parent: [15]
  Left: [10]      Right: [20,25]
```

### Borrow from Right Sibling (Rotate Left)

**Conditions**:

```c
bool can_borrow_right = (rightSibling != NULL) &&
                        (rightSibling->num_keys > MIN_KEYS);
```

**Process**:

1. Move parent separator key down to child
2. Move leftmost key from right sibling to parent
3. Move leftmost child from right sibling if exists

**Example**:

```
Before:
  Parent: [20]
  Left: [15] (min keys!)   Right: [25,30]

After rotate:
  Parent: [25]
  Left: [15,20]    Right: [30]
```

---

## Merging Siblings (mergeWithSibling)

### Process

```c
void mergeChildren(Node* parent, int index) {
  Node* left = parent->children[index];
  Node* right = parent->children[index+1];

  // 1. Bring down parent separator key
  left->keys[left->num_keys] = parent->keys[index];

  // 2. Copy keys/children from right to left
  for (int i = 0; i < right->num_keys; i++) {
    left->keys[left->num_keys+1+i] = right->keys[i];
  }
  if (right->children[0]) { // Internal node
    for (int i = 0; i <= right->num_keys; i++) {
      left->children[left->num_keys+1+i] = right->children[i];
    }
  }

  // 3. Update key count
  left->num_keys += 1 + right->num_keys;

  // 4. Remove separator and right child from parent
  // 5. Handle root reduction if needed
}
```

### Example

```
Before:
  Parent: [20]
    Left: [15]    Right: [25]   (both min keys)

After merge:
  Parent: [] → becomes empty!
  New node: [15,20,25] (now a 4-node)

Result:
  If parent was root and becomes empty,
  merged node becomes new root
```

---

## Key Insights

1. **Insertion**:
   - Always split full nodes _during descent_
   - Prevents leaf overflow
   - Tree grows only at root

2. **Deletion**:
   - Ensure nodes have > min keys _before descent_
   - Prevents leaf underflow
   - Tree shrinks only at root

3. **Recursion**:
   - Operations local to current node + children
   - No backtracking needed after modification
   - Balanced structure maintained automatically

