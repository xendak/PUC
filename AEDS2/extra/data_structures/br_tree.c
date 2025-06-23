#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Color enumeration
typedef enum { RED, BLACK } Color;

// Red-Black Tree Node structure
typedef struct RBNode {
  int data;
  Color color;
  struct RBNode *left;
  struct RBNode *right;
  struct RBNode *parent;
} RBNode;

// Global NIL sentinel node
RBNode *NIL;

// Function to initialize NIL sentinel
void init_sentinel() {
  NIL = (RBNode *)malloc(sizeof(RBNode));
  NIL->color = BLACK;
  NIL->left = NIL->right = NIL->parent = NIL;
  NIL->data = 0; // Dummy value
}

// Function to create a new Red-Black tree node
RBNode *create_Node(int data) {
  RBNode *new_node = (RBNode *)malloc(sizeof(RBNode));
  if (new_node == NULL) {
    printf("Memory allocation failed!\n");
    exit(1);
  }
  new_node->data = data;
  new_node->color = RED; // New nodes are initially RED
  new_node->left = NIL;
  new_node->right = NIL;
  new_node->parent = NIL;
  return new_node;
}

// Function to get color name as string
const char *get_color(Color color) { return (color == RED) ? "RED" : "BLACK"; }

// LEFT ROTATION
// Same as AVL but we also need to update parent pointers
//     x                y
//    / \              / \
//   α   y     -->    x   γ
//      / \          / \
//     β   γ        α   β
RBNode *rotate_left(RBNode *root, RBNode *x) {
  printf("Left rotating node %d\n", x->data);

  RBNode *y = x->right;

  // Turn y's left subtree into x's right subtree
  x->right = y->left;
  if (y->left != NIL) {
    y->left->parent = x;
  }

  // Link x's parent to y
  y->parent = x->parent;
  if (x->parent == NIL) {
    root = y; // y becomes new root
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }

  // Put x on y's left
  y->left = x;
  x->parent = y;

  return root;
}

// RIGHT ROTATION
// Same as AVL but we also need to update parent pointers
//       y            x
//      / \          / \
//     x   γ   -->  α   y
//    / \              / \
//   α   β            β   γ
RBNode *right_rotate(RBNode *root, RBNode *y) {
  printf("Right rotating node %d\n", y->data);

  RBNode *x = y->left;

  // Turn x's right subtree into y's left subtree
  y->left = x->right;
  if (x->right != NIL) {
    x->right->parent = y;
  }

  // Link y's parent to x
  x->parent = y->parent;
  if (y->parent == NIL) {
    root = x; // x becomes new root
  } else if (y == y->parent->left) {
    y->parent->left = x;
  } else {
    y->parent->right = x;
  }

  // Put y on x's right
  x->right = y;
  y->parent = x;

  return root;
}

// INSERTION FIXUP
// Restores Red-Black properties after insertion
RBNode *post_insert(RBNode *root, RBNode *z) {
  printf("Fixing up insertion for node %d\n", z->data);

  while (z->parent->color == RED) {
    if (z->parent == z->parent->parent->left) {
      // Case A: z's parent is left child of grandparent
      RBNode *uncle = z->parent->parent->right;

      if (uncle->color == RED) {
        // Case A1: Uncle is RED - Recoloring
        printf("Case A1: Uncle %d is RED, recoloring\n", uncle->data);
        z->parent->color = BLACK;
        uncle->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          // Case A2: Uncle is BLACK, z is right child - Left rotate
          printf("Case A2: Uncle is BLACK, z is right child\n");
          z = z->parent;
          root = rotate_left(root, z);
        }
        // Case A3: Uncle is BLACK, z is left child - Right rotate
        printf("Case A3: Uncle is BLACK, z is left child\n");
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        root = right_rotate(root, z->parent->parent);
      }
    } else {
      // Case B: z's parent is right child of grandparent (symmetric)
      RBNode *uncle = z->parent->parent->left;

      if (uncle->color == RED) {
        // Case B1: Uncle is RED - Recoloring
        printf("Case B1: Uncle %d is RED, recoloring\n", uncle->data);
        z->parent->color = BLACK;
        uncle->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          // Case B2: Uncle is BLACK, z is left child - Right rotate
          printf("Case B2: Uncle is BLACK, z is left child\n");
          z = z->parent;
          root = right_rotate(root, z);
        }
        // Case B3: Uncle is BLACK, z is right child - Left rotate
        printf("Case B3: Uncle is BLACK, z is right child\n");
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        root = rotate_left(root, z->parent->parent);
      }
    }
  }

  root->color = BLACK; // Root is always BLACK
  return root;
}

// INSERT function for Red-Black tree
RBNode *insert(RBNode *root, int data) {
  printf("\n--- Inserting %d ---\n", data);

  // Create new node
  RBNode *z = create_Node(data);

  // Standard BST insertion
  RBNode *y = NIL;
  RBNode *x = root;

  while (x != NIL) {
    y = x;
    if (z->data < x->data) {
      x = x->left;
    } else if (z->data > x->data) {
      x = x->right;
    } else {
      // Duplicate value
      printf("Value %d already exists\n", data);
      free(z);
      return root;
    }
  }

  z->parent = y;
  if (y == NIL) {
    root = z; // Tree was empty
  } else if (z->data < y->data) {
    y->left = z;
  } else {
    y->right = z;
  }

  // If z is root, color it black and return
  if (z->parent == NIL) {
    z->color = BLACK;
    return root;
  }

  // If z's parent is black, no violation
  if (z->parent->color == BLACK) {
    return root;
  }

  // Fix any violations
  return post_insert(root, z);
}

// Function to find minimum node in subtree
RBNode *find_min(RBNode *root) {
  while (root->left != NIL) {
    root = root->left;
  }
  return root;
}

// Function to replace node u with node v
RBNode *transplant(RBNode *root, RBNode *u, RBNode *v) {
  if (u->parent == NIL) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
  return root;
}

// DELETION FIXUP
// Restores Red-Black properties after deletion
RBNode *post_delete(RBNode *root, RBNode *x) {
  printf("Fixing up deletion\n");

  while (x != root && x->color == BLACK) {
    if (x == x->parent->left) {
      RBNode *w = x->parent->right; // w is x's sibling

      if (w->color == RED) {
        // Case 1: Sibling is RED
        printf("Delete Case 1: Sibling is RED\n");
        w->color = BLACK;
        x->parent->color = RED;
        root = rotate_left(root, x->parent);
        w = x->parent->right;
      }

      if (w->left->color == BLACK && w->right->color == BLACK) {
        // Case 2: Sibling is BLACK with BLACK children
        printf("Delete Case 2: Sibling is BLACK with BLACK children\n");
        w->color = RED;
        x = x->parent;
      } else {
        if (w->right->color == BLACK) {
          // Case 3: Sibling is BLACK, left child RED, right child BLACK
          printf("Delete Case 3: Sibling's right child is BLACK\n");
          w->left->color = BLACK;
          w->color = RED;
          root = right_rotate(root, w);
          w = x->parent->right;
        }
        // Case 4: Sibling is BLACK, right child RED
        printf("Delete Case 4: Sibling's right child is RED\n");
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->right->color = BLACK;
        root = rotate_left(root, x->parent);
        x = root;
      }
    } else {
      // Symmetric cases (x is right child)
      RBNode *w = x->parent->left;

      if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        root = right_rotate(root, x->parent);
        w = x->parent->left;
      }

      if (w->right->color == BLACK && w->left->color == BLACK) {
        w->color = RED;
        x = x->parent;
      } else {
        if (w->left->color == BLACK) {
          w->right->color = BLACK;
          w->color = RED;
          root = rotate_left(root, w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->left->color = BLACK;
        root = right_rotate(root, x->parent);
        x = root;
      }
    }
  }
  x->color = BLACK;
  return root;
}

// DELETE function for Red-Black tree
RBNode *delete(RBNode *root, int data) {
  printf("\n--- Deleting %d ---\n", data);

  // Find node to delete
  RBNode *z = root;
  while (z != NIL && z->data != data) {
    if (data < z->data) {
      z = z->left;
    } else {
      z = z->right;
    }
  }

  if (z == NIL) {
    printf("Value %d not found\n", data);
    return root;
  }

  RBNode *y = z;
  RBNode *x;
  Color yOriginalColor = y->color;

  if (z->left == NIL) {
    x = z->right;
    root = transplant(root, z, z->right);
  } else if (z->right == NIL) {
    x = z->left;
    root = transplant(root, z, z->left);
  } else {
    y = find_min(z->right);
    yOriginalColor = y->color;
    x = y->right;
    if (y->parent == z) {
      x->parent = y;
    } else {
      root = transplant(root, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    root = transplant(root, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }

  free(z);

  if (yOriginalColor == BLACK) {
    root = post_delete(root, x);
  }

  return root;
}

// SEARCH function
bool search(RBNode *root, int data) {
  RBNode *current = root;
  while (current != NIL) {
    if (data == current->data) {
      return true;
    } else if (data < current->data) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return false;
}

// Inorder traversal
void in_order_traversal(RBNode *root) {
  if (root != NIL) {
    in_order_traversal(root->left);
    printf("%d(%s) ", root->data, get_color(root->color));
    in_order_traversal(root->right);
  }
}

// Preorder traversal
void preorder_traversal(RBNode *root) {
  if (root != NIL) {
    printf("%d(%s) ", root->data, get_color(root->color));
    preorder_traversal(root->left);
    preorder_traversal(root->right);
  }
}

// Function to print tree structure
void print_tree(RBNode *root, int space) {
  const int COUNT = 10;
  if (root == NIL)
    return;

  space += COUNT;
  print_tree(root->right, space);

  printf("\n");
  for (int i = COUNT; i < space; i++) {
    printf(" ");
  }
  printf("%d(%s)\n", root->data, get_color(root->color));

  print_tree(root->left, space);
}

// Function to validate Red-Black properties
bool validate_tree(RBNode *root, int *blackHeight) {
  if (root == NIL) {
    *blackHeight = 1;
    return true;
  }

  int leftBlackHeight = 0, rightBlackHeight = 0;

  // Check property 4: Red node cannot have red children
  if (root->color == RED) {
    if (root->left->color == RED || root->right->color == RED) {
      printf("Violation: Red node %d has red child\n", root->data);
      return false;
    }
  }

  // Recursively validate subtrees
  if (!validate_tree(root->left, &leftBlackHeight) ||
      !validate_tree(root->right, &rightBlackHeight)) {
    return false;
  }

  // Check property 5: Equal black heights
  if (leftBlackHeight != rightBlackHeight) {
    printf("Violation: Unequal black heights at node %d\n", root->data);
    return false;
  }

  *blackHeight = leftBlackHeight + (root->color == BLACK ? 1 : 0);
  return true;
}

// Free Red-Black tree
void free_tree(RBNode *root) {
  if (root != NIL) {
    free_tree(root->left);
    free_tree(root->right);
    free(root);
  }
}

// Test function
void test_tree(RBNode **root) {
  printf("\n=== Testing Red-Black Tree ===\n");
  printf("Inserting sequence: 7, 3, 18, 10, 22, 8, 11, 26\n");
  printf("This will demonstrate recoloring and rotations:\n\n");

  int testData[] = {7, 3, 18, 10, 22, 8, 11, 26};
  int n = sizeof(testData) / sizeof(testData[0]);

  for (int i = 0; i < n; i++) {
    *root = insert(*root, testData[i]);
    printf("Tree after inserting %d:\n", testData[i]);
    print_tree(*root, 0);
    printf("\n");
  }
}

// Menu function
void menu() {
  printf("\n=== Red-Black Tree Operations ===\n");
  printf("1. Insert\n");
  printf("2. Search\n");
  printf("3. Delete\n");
  printf("4. Display (Inorder)\n");
  printf("5. Display (Preorder)\n");
  printf("6. Display Tree Structure\n");
  printf("7. Validate Tree Properties\n");
  printf("8. Test with Sample Data\n");
  printf("9. Exit\n");
  printf("Enter your choice: ");
}

int main() {
  // Initialize NIL sentinel
  init_sentinel();

  RBNode *root = NIL;
  int choice, value;

  printf("Red-Black Tree Implementation in C\n");
  printf("==================================\n");
  printf("Red-Black Tree Properties:\n");
  printf("1. Every node is RED or BLACK\n");
  printf("2. Root is BLACK\n");
  printf("3. All leaves (NIL) are BLACK\n");
  printf("4. Red nodes have BLACK children\n");
  printf("5. All paths have same number of BLACK nodes\n\n");

  while (1) {
    menu();
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("Enter value to insert: ");
      scanf("%d", &value);
      root = insert(root, value);
      break;

    case 2:
      printf("Enter value to search: ");
      scanf("%d", &value);
      if (search(root, value)) {
        printf("Value %d found!\n", value);
      } else {
        printf("Value %d not found.\n", value);
      }
      break;

    case 3:
      printf("Enter value to delete: ");
      scanf("%d", &value);
      root = delete (root, value);
      break;

    case 4:
      printf("Inorder traversal: ");
      if (root == NIL) {
        printf("Tree is empty.\n");
      } else {
        in_order_traversal(root);
        printf("\n");
      }
      break;

    case 5:
      printf("Preorder traversal: ");
      if (root == NIL) {
        printf("Tree is empty.\n");
      } else {
        preorder_traversal(root);
        printf("\n");
      }
      break;

    case 6:
      printf("Tree Structure:\n");
      if (root == NIL) {
        printf("Tree is empty.\n");
      } else {
        print_tree(root, 0);
      }
      break;

    case 7:
      if (root == NIL) {
        printf("Tree is empty.\n");
      } else {
        int blackHeight;
        if (root->color != BLACK) {
          printf("Violation: Root is not BLACK\n");
        } else if (validate_tree(root, &blackHeight)) {
          printf("Tree satisfies all Red-Black properties!\n");
          printf("Black height: %d\n", blackHeight);
        } else {
          printf("Tree violates Red-Black properties!\n");
        }
      }
      break;

    case 8:
      if (root != NIL) {
        printf("Clear current tree? (1=Yes, 0=No): ");
        int confirm;
        scanf("%d", &confirm);
        if (confirm) {
          free_tree(root);
          root = NIL;
        } else {
          break;
        }
      }
      test_tree(&root);
      break;

    case 9:
      printf("Freeing memory and exiting...\n");
      free_tree(root);
      free(NIL);
      exit(0);

    default:
      printf("Invalid choice!\n");
    }
  }

  return 0;
}
