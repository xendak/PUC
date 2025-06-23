#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Node structure for binary search tree
typedef struct Node {
  int data;
  struct Node *left;
  struct Node *right;
} Node;

// Function to create a new node
Node *create_node(int data) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    printf("Memory allocation failed!\n");
    exit(1);
  }
  new_node->data = data;
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}

// Insert function - adds a new node to the BST
Node *insert(Node *root, int data) {
  // Base case: if tree is empty or we've found the insertion point
  if (root == NULL) {
    return create_node(data);
  }

  // Recursive case: traverse left or right based on BST property
  if (data < root->data) {
    root->left = insert(root->left, data);
  } else if (data > root->data) {
    root->right = insert(root->right, data);
  }
  // If data equals root->data, we don't insert (no duplicates)

  return root;
}

// Search function - returns true if value is found, false otherwise
bool search(Node *root, int data) {
  // Base case: empty tree or value not found
  if (root == NULL) {
    return false;
  }

  // Base case: value found
  if (root->data == data) {
    return true;
  }

  // Recursive case: search left or right subtree
  if (data < root->data) {
    return search(root->left, data);
  } else {
    return search(root->right, data);
  }
}

// Helper function to find the minimum value node (leftmost node)
Node *find_min(Node *root) {
  while (root && root->left != NULL) {
    root = root->left;
  }
  return root;
}

// Delete function - removes a node from the BST
Node *delete(Node *root, int data) {
  // Base case: empty tree
  if (root == NULL) {
    return root;
  }

  // Recursive case: find the node to delete
  if (data < root->data) {
    root->left = delete (root->left, data);
  } else if (data > root->data) {
    root->right = delete (root->right, data);
  } else {
    // Node to be deleted found

    // Case 1: Node has no children (leaf node)
    if (root->left == NULL && root->right == NULL) {
      free(root);
      return NULL;
    }
    // Case 2: Node has only right child
    else if (root->left == NULL) {
      Node *temp = root->right;
      free(root);
      return temp;
    }
    // Case 3: Node has only left child
    else if (root->right == NULL) {
      Node *temp = root->left;
      free(root);
      return temp;
    }
    // Case 4: Node has both children
    else {
      // Find inorder successor (smallest value in right subtree)
      Node *temp = find_min(root->right);

      // Replace current node's data with successor's data
      root->data = temp->data;

      // Delete the successor
      root->right = delete (root->right, temp->data);
    }
  }

  return root;
}

// Inorder traversal - prints tree in sorted order
void in_order_traversal(Node *root) {
  if (root != NULL) {
    in_order_traversal(root->left);
    printf("%d ", root->data);
    in_order_traversal(root->right);
  }
}

// Preorder traversal - prints root, then left, then right
void preorder_traversal(Node *root) {
  if (root != NULL) {
    printf("%d ", root->data);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
  }
}

// Function to free all nodes in the tree
void free_tree(Node *root) {
  if (root != NULL) {
    free_tree(root->left);
    free_tree(root->right);
    free(root);
  }
}

int tree_height(Node *root) {
  if (root == NULL)
    return 0;
  int left_height = tree_height(root->left);
  int right_height = tree_height(root->right);
  return (left_height > right_height ? left_height : right_height) + 1;
}

// Function to print tree visually
void print_tree(Node *root) {
  if (root == NULL) {
    printf("Tree is empty.\n");
    return;
  }

  int h = tree_height(root);
  int max_nodes = pow(2, h) - 1;
  Node **queue = (Node **)malloc(max_nodes * sizeof(Node *));
  int front = 0, rear = 0;

  // Initialize queue with root node
  queue[rear++] = root;

  // Level-order traversal
  for (int level = 0; level < h; level++) {
    int nodes_in_level = pow(2, level);
    int spacing = pow(2, h - level) - 1;
    int branch_spacing = spacing;
    int indent = pow(2, h - level - 1) - 1;

    // Print indentation for current level
    for (int i = 0; i < indent; i++)
      printf(" ");

    for (int i = 0; i < nodes_in_level; i++) {
      Node *current = queue[front++];

      // Print node or space
      if (current) {
        printf("%d", current->data);
        queue[rear++] = current->left;
        queue[rear++] = current->right;
      } else {
        printf(" ");
        queue[rear++] = NULL;
        queue[rear++] = NULL;
      }

      // Print spacing between nodes
      if (i < nodes_in_level - 1) {
        for (int j = 0; j < spacing; j++)
          printf(" ");
      }
    }
    printf("\n");

    // Print branches if not last level
    if (level < h - 1) {
      // Print indentation for branches
      for (int i = 0; i < indent; i++)
        printf(" ");

      for (int i = 0; i < nodes_in_level; i++) {
        Node *current = queue[front - nodes_in_level + i];
        if (current && (current->left || current->right)) {
          printf("/");
        } else {
          printf(" ");
        }

        // Print spacing between branches
        for (int j = 0; j < branch_spacing; j++) {
          if (i < nodes_in_level - 1)
            printf(" ");
        }

        if (current && (current->left || current->right)) {
          printf("\\");
        } else {
          printf(" ");
        }

        if (i < nodes_in_level - 1) {
          for (int j = 0; j < branch_spacing; j++)
            printf(" ");
        }
      }
      printf("\n");
    }
  }
  free(queue);
}

// Function to display menu
void menu() {
  printf("\n=== Binary Search Tree Operations ===\n");
  printf("1. Insert\n");
  printf("2. Search\n");
  printf("3. Delete\n");
  printf("4. Display (Inorder)\n");
  printf("5. Display (Preorder)\n");
  printf("6. Exit\n");
  printf("Enter your choice: ");
}

// Main function with interactive menu
int main() {
  Node *root = NULL;
  int choice, value;

  printf("Binary Search Tree Implementation in C\n");
  printf("=====================================\n");

  while (1) {
    menu();
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("Enter value to insert: ");
      scanf("%d", &value);
      root = insert(root, value);
      printf("Value %d inserted successfully!\n", value);
      break;

    case 2:
      printf("Enter value to search: ");
      scanf("%d", &value);
      if (search(root, value)) {
        printf("Value %d found in the tree!\n", value);
      } else {
        printf("Value %d not found in the tree.\n", value);
      }
      break;

    case 3:
      printf("Enter value to delete: ");
      scanf("%d", &value);
      if (search(root, value)) {
        root = delete (root, value);
        printf("Value %d deleted successfully!\n", value);
      } else {
        printf("Value %d not found in the tree.\n", value);
      }
      break;

    case 4:
      printf("Inorder traversal (sorted): ");
      if (root == NULL) {
        printf("Tree is empty.\n");
      } else {
        in_order_traversal(root);
        printf("\n");
      }
      break;

    case 5:
      printf("Preorder traversal: ");
      if (root == NULL) {
        printf("Tree is empty.\n");
      } else {
        print_tree(root);
        printf("\n");
      }
      break;

    case 6:
      printf("Freeing memory and exiting...\n");
      free_tree(root);
      exit(0);

    default:
      printf("Invalid choice! Please try again.\n");
    }
  }

  return 0;
}
