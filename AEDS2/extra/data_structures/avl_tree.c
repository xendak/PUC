#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// AVL Tree Node structure
typedef struct AVLNode {
  int data;
  int height;
  struct AVLNode *left;
  struct AVLNode *right;
} AVLNode;

// Function to get height of a noden
int get_height(AVLNode *node) {
  if (node == NULL)
    return 0;
  return node->height;
}

// Function to get maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }

// Function to calculate balance factor of a node
int get_balance_factor(AVLNode *node) {
  if (node == NULL)
    return 0;
  return get_height(node->left) - get_height(node->right);
}

// Function to update height of a node
void update_height(AVLNode *node) {
  if (node != NULL) {
    node->height = 1 + max(get_height(node->left), get_height(node->right));
  }
}

// Function to create a new AVL node
AVLNode *create_AVL_node(int data) {
  AVLNode *newNode = (AVLNode *)malloc(sizeof(AVLNode));
  if (newNode == NULL) {
    printf("Memory allocation failed!\n");
    exit(1);
  }
  newNode->data = data;
  newNode->height = 1; // New node starts at height 1
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

// RIGHT ROTATION (RR Rotation)
// Used when left subtree is heavier (balance factor > 1)
//     y                x
//    / \              / \
//   x   T3    -->    T1  y
//  / \                  / \
// T1  T2               T2 T3
AVLNode *rotate_right(AVLNode *y) {
  printf("Performing RIGHT rotation on node %d\n", y->data);

  AVLNode *x = y->left;
  AVLNode *T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights (order matters: update y first, then x)
  update_height(y);
  update_height(x);

  // Return new root of subtree
  return x;
}

// LEFT ROTATION (LL Rotation)
// Used when right subtree is heavier (balance factor < -1)
//   x                  y
//  / \                / \
// T1  y      -->     x   T3
//    / \            / \
//   T2 T3          T1 T2
AVLNode *rotate_left(AVLNode *x) {
  printf("Performing LEFT rotation on node %d\n", x->data);

  AVLNode *y = x->right;
  AVLNode *T2 = y->left;

  // Perform rotation
  y->left = x;
  x->right = T2;

  // Update heights (order matters: update x first, then y)
  update_height(x);
  update_height(y);

  // Return new root of subtree
  return y;
}

// LEFT-RIGHT ROTATION (LR Rotation)
// Used when left child's right subtree is heavier
// First left rotate on left child, then right rotate on root
AVLNode *rotate_left_right(AVLNode *node) {
  printf("Performing LEFT-RIGHT rotation on node %d\n", node->data);
  node->left = rotate_left(node->left);
  return rotate_right(node);
}

// RIGHT-LEFT ROTATION (RL Rotation)
// Used when right child's left subtree is heavier
// First right rotate on right child, then left rotate on root
AVLNode *rotate_right_left(AVLNode *node) {
  printf("Performing RIGHT-LEFT rotation on node %d\n", node->data);
  node->right = rotate_right(node->right);
  return rotate_left(node);
}

// Function to rebalance the tree after insertion/deletion
AVLNode *rebalance(AVLNode *node) {
  // Update height of current node
  update_height(node);

  // Get balance factor
  int balance = get_balance_factor(node);

  // Left Heavy (balance > 1)
  if (balance > 1) {
    // Left-Left case: simple right rotation
    if (get_balance_factor(node->left) >= 0) {
      return rotate_right(node);
    }
    // Left-Right case: left-right rotation
    else {
      return rotate_left_right(node);
    }
  }

  // Right Heavy (balance < -1)
  if (balance < -1) {
    // Right-Right case: simple left rotation
    if (get_balance_factor(node->right) <= 0) {
      return rotate_left(node);
    }
    // Right-Left case: right-left rotation
    else {
      return rotate_right_left(node);
    }
  }

  // Tree is balanced, no rotation needed
  return node;
}

// Insert function for AVL tree
AVLNode *insert_AVL(AVLNode *root, int data) {
  // Step 1: Perform normal BST insertion
  if (root == NULL) {
    printf("Inserting %d as new node\n", data);
    return create_AVL_node(data);
  }

  if (data < root->data) {
    root->left = insert_AVL(root->left, data);
  } else if (data > root->data) {
    root->right = insert_AVL(root->right, data);
  } else {
    // Duplicate values not allowed
    printf("Value %d already exists in tree\n", data);
    return root;
  }

  // Step 2: Rebalance the tree
  return rebalance(root);
}

// Function to find node with minimum value (leftmost node)
AVLNode *find_min_AVL(AVLNode *root) {
  while (root && root->left != NULL) {
    root = root->left;
  }
  return root;
}

// Delete function for AVL tree
AVLNode *delete_AVL(AVLNode *root, int data) {
  // Step 1: Perform normal BST deletion
  if (root == NULL) {
    return root;
  }

  if (data < root->data) {
    root->left = delete_AVL(root->left, data);
  } else if (data > root->data) {
    root->right = delete_AVL(root->right, data);
  } else {
    // Node to be deleted found
    printf("Deleting node %d\n", data);

    // Case 1: Node has no children or only one child
    if (root->left == NULL || root->right == NULL) {
      AVLNode *temp = root->left ? root->left : root->right;

      if (temp == NULL) {
        // No child case
        temp = root;
        root = NULL;
      } else {
        // One child case
        *root = *temp; // Copy contents of non-empty child
      }
      free(temp);
    } else {
      // Case 2: Node has two children
      // Find inorder successor (smallest in right subtree)
      AVLNode *temp = find_min_AVL(root->right);

      // Copy successor's data to this node
      root->data = temp->data;

      // Delete the successor
      root->right = delete_AVL(root->right, temp->data);
    }
  }

  // If tree had only one node, return
  if (root == NULL) {
    return root;
  }

  // Step 2: Rebalance the tree
  return rebalance(root);
}

// Search function for AVL tree
bool search_AVL(AVLNode *root, int data) {
  if (root == NULL) {
    return false;
  }

  if (root->data == data) {
    return true;
  }

  if (data < root->data) {
    return search_AVL(root->left, data);
  } else {
    return search_AVL(root->right, data);
  }
}

// Inorder traversal
void inorder_traversal_AVL(AVLNode *root) {
  if (root != NULL) {
    inorder_traversal_AVL(root->left);
    printf("%d(h:%d,bf:%d) ", root->data, root->height, get_balance_factor(root));
    inorder_traversal_AVL(root->right);
  }
}

// Preorder traversal
void preorder_traversal_AVL(AVLNode *root) {
  if (root != NULL) {
    printf("%d(h:%d,bf:%d) ", root->data, root->height, get_balance_factor(root));
    preorder_traversal_AVL(root->left);
    preorder_traversal_AVL(root->right);
  }
}

// Function to print tree structure (visual representation)
void print_tree(AVLNode *root, int space) {
  const int COUNT = 10;
  if (root == NULL)
    return;

  space += COUNT;
  print_tree(root->right, space);

  printf("\n");
  for (int i = COUNT; i < space; i++) {
    printf(" ");
  }
  printf("%d(h:%d,bf:%d)\n", root->data, root->height, get_balance_factor(root));

  print_tree(root->left, space);
}

// Function to free all nodes in AVL tree
void free_AVL_Tree(AVLNode *root) {
  if (root != NULL) {
    free_AVL_Tree(root->left);
    free_AVL_Tree(root->right);
    free(root);
  }
}

// Function to display menu
void menu() {
  printf("\n=== AVL Tree Operations ===\n");
  printf("1. Insert\n");
  printf("2. Search\n");
  printf("3. Delete\n");
  printf("4. Display (Inorder with height & balance factor)\n");
  printf("5. Display (Preorder with height & balance factor)\n");
  printf("6. Display Tree Structure\n");
  printf("7. Test with sample data\n");
  printf("8. Exit\n");
  printf("Enter your choice: ");
}

// Function to test AVL tree with sample data
void test_AVL_tree(AVLNode **root) {
  printf("\n=== Testing AVL Tree with Sample Data ===\n");
  printf("Inserting sequence: 10, 20, 30, 40, 50, 25\n");
  printf("This will demonstrate various rotations:\n\n");

  int testData[] = {10, 20, 30, 40, 50, 25};
  int n = sizeof(testData) / sizeof(testData[0]);

  for (int i = 0; i < n; i++) {
    printf("--- Inserting %d ---\n", testData[i]);
    *root = insert_AVL(*root, testData[i]);
    printf("Tree after insertion:\n");
    print_tree(*root, 0);
    printf("\n");
  }
}

// Main function
int main() {
  AVLNode *root = NULL;
  int choice, value;

  printf("AVL Tree Implementation with Rotations in C\n");
  printf("==========================================\n");
  printf("AVL trees maintain balance through rotations:\n");
  printf("- Balance Factor = height(left) - height(right)\n");
  printf("- Valid range: -1, 0, +1\n");
  printf("- Four rotation types: LL, RR, LR, RL\n\n");

  while (1) {
    menu();
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("Enter value to insert: ");
      scanf("%d", &value);
      printf("\n--- Inserting %d ---\n", value);
      root = insert_AVL(root, value);
      printf("Insertion complete!\n");
      break;

    case 2:
      printf("Enter value to search: ");
      scanf("%d", &value);
      if (search_AVL(root, value)) {
        printf("Value %d found in the tree!\n", value);
      } else {
        printf("Value %d not found in the tree.\n", value);
      }
      break;

    case 3:
      printf("Enter value to delete: ");
      scanf("%d", &value);
      if (search_AVL(root, value)) {
        printf("\n--- Deleting %d ---\n", value);
        root = delete_AVL(root, value);
        printf("Deletion complete!\n");
      } else {
        printf("Value %d not found in the tree.\n", value);
      }
      break;

    case 4:
      printf("Inorder traversal (data(height:balance_factor)): ");
      if (root == NULL) {
        printf("Tree is empty.\n");
      } else {
        inorder_traversal_AVL(root);
        printf("\n");
      }
      break;

    case 5:
      printf("Preorder traversal (data(height:balance_factor)): ");
      if (root == NULL) {
        printf("Tree is empty.\n");
      } else {
        preorder_traversal_AVL(root);
        printf("\n");
      }
      break;

    case 6:
      printf("Tree Structure (data(height:balance_factor)):\n");
      if (root == NULL) {
        printf("Tree is empty.\n");
      } else {
        print_tree(root, 0);
      }
      break;

    case 7:
      if (root != NULL) {
        printf("Tree is not empty. Clear it first? (This will free current "
               "tree)\n");
        printf("Continue? (1=Yes, 0=No): ");
        int confirm;
        scanf("%d", &confirm);
        if (confirm) {
          free_AVL_Tree(root);
          root = NULL;
        } else {
          break;
        }
      }
      test_AVL_tree(&root);
      break;

    case 8:
      printf("Freeing memory and exiting...\n");
      free_AVL_Tree(root);
      exit(0);

    default:
      printf("Invalid choice! Please try again.\n");
    }
  }

  return 0;
}
