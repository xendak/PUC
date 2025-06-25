#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Red-Black Tree Node Colors
typedef enum { RB_RED = 0, RB_BLACK = 1 } RBColor;

// Red-Black Tree Node Structure
typedef struct RBNode {
  int data;
  RBColor color;
  struct RBNode *left;
  struct RBNode *right;
  struct RBNode *parent;
} RBNode;

// Red-Black Tree Structure
typedef struct {
  RBNode *root;
  RBNode *nil; // Sentinel node representing NULL
} RBTree;

// Function prototypes
RBTree *createRBTree();
RBNode *createNode(RBTree *tree, int data);
void leftRotate(RBTree *tree, RBNode *x);
void rightRotate(RBTree *tree, RBNode *x);
void insertFixup(RBTree *tree, RBNode *z);
void insert(RBTree *tree, int data);
void transplant(RBTree *tree, RBNode *u, RBNode *v);
RBNode *minimum(RBTree *tree, RBNode *x);
void deleteFixup(RBTree *tree, RBNode *x);
void deleteNode(RBTree *tree, int data);
RBNode *search(RBTree *tree, int data);
void inorderTraversal(RBTree *tree, RBNode *node);
void drawTree(RBTree *tree, RBNode *node, int x, int y, int level, int spacing);
void getAllValues(RBTree *tree, RBNode *node, int *values, int *count);
void visualizeTree(RBTree *tree);

/*
 * RED-BLACK TREE PROPERTIES:
 * 1. Every node is either red or black
 * 2. The root is black
 * 3. All leaves (NIL nodes) are black
 * 4. If a node is red, both its children are black (no two red nodes adjacent)
 * 5. For each node, all simple paths from the node to descendant leaves
 *    contain the same number of black nodes (black-height property)
 */

// Create a new Red-Black Tree
RBTree *createRBTree() {
  RBTree *tree = (RBTree *)malloc(sizeof(RBTree));

  // Create sentinel NIL node (always black)
  tree->nil = (RBNode *)malloc(sizeof(RBNode));
  tree->nil->color = RB_BLACK;
  tree->nil->left = tree->nil->right = tree->nil->parent = tree->nil;

  tree->root = tree->nil;
  return tree;
}

// Create a new node
RBNode *createNode(RBTree *tree, int data) {
  RBNode *node = (RBNode *)malloc(sizeof(RBNode));
  node->data = data;
  node->color = RB_RED; // New nodes are always red initially
  node->left = node->right = node->parent = tree->nil;
  return node;
}

/*
 * LEFT ROTATION:
 * Rotates the subtree rooted at x to the left
 * Used to maintain Red-Black tree properties during insertion/deletion
 *
 *     x               y
 *    / \             / \
 *   α   y    =>     x   γ
 *      / \         / \
 *     β   γ       α   β
 */
void leftRotate(RBTree *tree, RBNode *x) {
  RBNode *y = x->right; // Set y
  x->right = y->left;   // Turn y's left subtree into x's right subtree

  if (y->left != tree->nil) {
    y->left->parent = x;
  }

  y->parent = x->parent; // Link x's parent to y

  if (x->parent == tree->nil) {
    tree->root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }

  y->left = x; // Put x on y's left
  x->parent = y;
}

/*
 * RIGHT ROTATION:
 * Rotates the subtree rooted at x to the right
 * Mirror operation of left rotation
 *
 *       x           y
 *      / \         / \
 *     y   γ   =>  α   x
 *    / \             / \
 *   α   β           β   γ
 */
void rightRotate(RBTree *tree, RBNode *x) {
  RBNode *y = x->left; // Set y
  x->left = y->right;  // Turn y's right subtree into x's left subtree

  if (y->right != tree->nil) {
    y->right->parent = x;
  }

  y->parent = x->parent; // Link x's parent to y

  if (x->parent == tree->nil) {
    tree->root = y;
  } else if (x == x->parent->right) {
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }

  y->right = x; // Put x on y's right
  x->parent = y;
}

/*
 * INSERT FIXUP:
 * Restores Red-Black tree properties after insertion
 * Handles the cases where red-red violations occur
 */
void insertFixup(RBTree *tree, RBNode *z) {
  while (z->parent->color == RB_RED) {
    if (z->parent == z->parent->parent->left) {
      RBNode *y = z->parent->parent->right; // Uncle

      // Case 1: Uncle is red
      if (y->color == RB_RED) {
        z->parent->color = RB_BLACK;
        y->color = RB_BLACK;
        z->parent->parent->color = RB_RED;
        z = z->parent->parent;
      } else {
        // Case 2: Uncle is black, z is right child
        if (z == z->parent->right) {
          z = z->parent;
          leftRotate(tree, z);
        }
        // Case 3: Uncle is black, z is left child
        z->parent->color = RB_BLACK;
        z->parent->parent->color = RB_RED;
        rightRotate(tree, z->parent->parent);
      }
    } else {
      // Mirror cases when z->parent is right child
      RBNode *y = z->parent->parent->left; // Uncle

      if (y->color == RB_RED) {
        z->parent->color = RB_BLACK;
        y->color = RB_BLACK;
        z->parent->parent->color = RB_RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          rightRotate(tree, z);
        }
        z->parent->color = RB_BLACK;
        z->parent->parent->color = RB_RED;
        leftRotate(tree, z->parent->parent);
      }
    }
  }
  tree->root->color = RB_BLACK; // Root is always black
}

/*
 * INSERT:
 * Inserts a new node with given data into the Red-Black tree
 * Uses standard BST insertion followed by fixup to maintain RB properties
 */
void insert(RBTree *tree, int data) {
  RBNode *z = createNode(tree, data);
  RBNode *y = tree->nil;
  RBNode *x = tree->root;

  // Standard BST insertion
  while (x != tree->nil) {
    y = x;
    if (z->data < x->data) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  z->parent = y;
  if (y == tree->nil) {
    tree->root = z;
  } else if (z->data < y->data) {
    y->left = z;
  } else {
    y->right = z;
  }

  // Fix Red-Black tree properties
  insertFixup(tree, z);
}

// Transplant: Replace subtree rooted at u with subtree rooted at v
void transplant(RBTree *tree, RBNode *u, RBNode *v) {
  if (u->parent == tree->nil) {
    tree->root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

// Find minimum node in subtree
RBNode *minimum(RBTree *tree, RBNode *x) {
  while (x->left != tree->nil) {
    x = x->left;
  }
  return x;
}

/*
 * DELETE FIXUP:
 * Restores Red-Black tree properties after deletion
 * Handles cases where black-height property is violated
 */
void deleteFixup(RBTree *tree, RBNode *x) {
  while (x != tree->root && x->color == RB_BLACK) {
    if (x == x->parent->left) {
      RBNode *w = x->parent->right; // Sibling

      // Case 1: Sibling is red
      if (w->color == RB_RED) {
        w->color = RB_BLACK;
        x->parent->color = RB_RED;
        leftRotate(tree, x->parent);
        w = x->parent->right;
      }

      // Case 2: Sibling is black, both children are black
      if (w->left->color == RB_BLACK && w->right->color == RB_BLACK) {
        w->color = RB_RED;
        x = x->parent;
      } else {
        // Case 3: Sibling is black, left child is red, right child is black
        if (w->right->color == RB_BLACK) {
          w->left->color = RB_BLACK;
          w->color = RB_RED;
          rightRotate(tree, w);
          w = x->parent->right;
        }
        // Case 4: Sibling is black, right child is red
        w->color = x->parent->color;
        x->parent->color = RB_BLACK;
        w->right->color = RB_BLACK;
        leftRotate(tree, x->parent);
        x = tree->root;
      }
    } else {
      // Mirror cases when x is right child
      RBNode *w = x->parent->left;

      if (w->color == RB_RED) {
        w->color = RB_BLACK;
        x->parent->color = RB_RED;
        rightRotate(tree, x->parent);
        w = x->parent->left;
      }

      if (w->right->color == RB_BLACK && w->left->color == RB_BLACK) {
        w->color = RB_RED;
        x = x->parent;
      } else {
        if (w->left->color == RB_BLACK) {
          w->right->color = RB_BLACK;
          w->color = RB_RED;
          leftRotate(tree, w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = RB_BLACK;
        w->left->color = RB_BLACK;
        rightRotate(tree, x->parent);
        x = tree->root;
      }
    }
  }
  x->color = RB_BLACK;
}

/*
 * DELETE:
 * Deletes a node with given data from the Red-Black tree
 * Uses standard BST deletion followed by fixup to maintain RB properties
 */
void deleteNode(RBTree *tree, int data) {
  RBNode *z = search(tree, data);
  if (z == tree->nil) {
    printf("Node %d not found!\n", data);
    return;
  }

  RBNode *y = z;
  RBNode *x;
  RBColor yOriginalColor = y->color;

  if (z->left == tree->nil) {
    x = z->right;
    transplant(tree, z, z->right);
  } else if (z->right == tree->nil) {
    x = z->left;
    transplant(tree, z, z->left);
  } else {
    y = minimum(tree, z->right);
    yOriginalColor = y->color;
    x = y->right;

    if (y->parent == z) {
      x->parent = y;
    } else {
      transplant(tree, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }

    transplant(tree, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }

  if (yOriginalColor == RB_BLACK) {
    deleteFixup(tree, x);
  }

  free(z);
}

// Search for a node with given data
RBNode *search(RBTree *tree, int data) {
  RBNode *current = tree->root;
  while (current != tree->nil && current->data != data) {
    if (data < current->data) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return current;
}

// Inorder traversal for debugging
void inorderTraversal(RBTree *tree, RBNode *node) {
  if (node != tree->nil) {
    inorderTraversal(tree, node->left);
    printf("%d(%s) ", node->data, node->color == RB_RED ? "R" : "B");
    inorderTraversal(tree, node->right);
  }
}

/*
 * TREE VISUALIZATION:
 * Recursively draws the Red-Black tree using raylib
 * Red nodes are drawn in red, black nodes in dark gray
 */
void drawTree(RBTree *tree, RBNode *node, int x, int y, int level,
              int spacing) {
  if (node == tree->nil)
    return;

  // Draw current node
  Color nodeColor = node->color == RB_RED ? RED : DARKGRAY;
  DrawCircle(x, y, 20, nodeColor);
  DrawText(TextFormat("%d", node->data), x - 8, y - 8, 16, WHITE);

  // Calculate positions for children
  int childSpacing = spacing / 2;
  int childY = y + 80;

  // Draw left child
  if (node->left != tree->nil) {
    int leftX = x - childSpacing;
    DrawLine(x, y + 20, leftX, childY - 20, BLACK);
    drawTree(tree, node->left, leftX, childY, level + 1, childSpacing);
  }

  // Draw right child
  if (node->right != tree->nil) {
    int rightX = x + childSpacing;
    DrawLine(x, y + 20, rightX, childY - 20, BLACK);
    drawTree(tree, node->right, rightX, childY, level + 1, childSpacing);
  }
}

// Get all values in the tree for deletion purposes
void getAllValues(RBTree *tree, RBNode *node, int *values, int *count) {
  if (node != tree->nil) {
    getAllValues(tree, node->left, values, count);
    values[(*count)++] = node->data;
    getAllValues(tree, node->right, values, count);
  }
}

// Interactive visualization function
void visualizeTree(RBTree *tree) {
  InitWindow(1200, 800, "Interactive Red-Black Tree Visualization");
  SetTargetFPS(60);

  int lastInserted = -1;
  int lastDeleted = -1;
  char statusMessage[256] =
      "Ready - Press 'A' to insert, 'D' to delete, 'C' to clear";

  while (!WindowShouldClose()) {
    // Handle input
    if (IsKeyPressed(KEY_A)) {
      // Insert random value between 1-99
      int randomValue = GetRandomValue(1, 99);

      // Check if value already exists
      if (search(tree, randomValue) == tree->nil) {
        insert(tree, randomValue);
        lastInserted = randomValue;
        snprintf(statusMessage, sizeof(statusMessage), "Inserted: %d",
                 randomValue);
      } else {
        snprintf(statusMessage, sizeof(statusMessage),
                 "Value %d already exists! Try again.", randomValue);
      }
    }

    if (IsKeyPressed(KEY_D)) {
      if (tree->root != tree->nil) {
        // Get all values in the tree
        int values[1000];
        int count = 0;
        getAllValues(tree, tree->root, values, &count);

        if (count > 0) {
          // Pick a random value to delete
          int randomIndex = GetRandomValue(0, count - 1);
          int valueToDelete = values[randomIndex];
          deleteNode(tree, valueToDelete);
          lastDeleted = valueToDelete;
          snprintf(statusMessage, sizeof(statusMessage), "Deleted: %d",
                   valueToDelete);
        }
      } else {
        snprintf(statusMessage, sizeof(statusMessage),
                 "Tree is empty! Nothing to delete.");
      }
    }

    if (IsKeyPressed(KEY_C)) {
      // Clear the entire tree
      while (tree->root != tree->nil) {
        int values[1000];
        int count = 0;
        getAllValues(tree, tree->root, values, &count);
        if (count > 0) {
          deleteNode(tree, values[0]);
        }
      }
      snprintf(statusMessage, sizeof(statusMessage), "Tree cleared!");
      lastInserted = lastDeleted = -1;
    }

    // Count nodes for display
    int nodeCount = 0;
    if (tree->root != tree->nil) {
      int values[1000];
      getAllValues(tree, tree->root, values, &nodeCount);
    }

    BeginDrawing();
    ClearBackground(SKYBLUE);

    // Draw title and instructions
    DrawText("Interactive Red-Black Tree Visualization", 10, 10, 24, BLACK);
    DrawText("Controls:", 10, 45, 18, DARKBLUE);
    DrawText("  A - Insert random value (1-99)", 10, 70, 16, DARKGRAY);
    DrawText("  D - Delete random existing value", 10, 90, 16, DARKGRAY);
    DrawText("  C - Clear entire tree", 10, 110, 16, DARKGRAY);
    DrawText("  ESC - Exit", 10, 130, 16, DARKGRAY);

    // Draw status
    DrawText("Status:", 10, 160, 18, DARKBLUE);
    DrawText(statusMessage, 10, 185, 16, DARKGREEN);

    // Draw tree info
    DrawText(TextFormat("Nodes in tree: %d", nodeCount), 10, 215, 16, BLACK);
    if (lastInserted != -1) {
      DrawText(TextFormat("Last inserted: %d", lastInserted), 10, 235, 16,
               GREEN);
    }
    if (lastDeleted != -1) {
      DrawText(TextFormat("Last deleted: %d", lastDeleted), 10, 255, 16, RED);
    }

    // Draw legend
    DrawText("Legend:", 10, 285, 18, DARKBLUE);
    DrawCircle(30, 315, 12, RED);
    DrawText("Red Node", 50, 308, 16, BLACK);
    DrawCircle(30, 335, 12, DARKGRAY);
    DrawText("Black Node", 50, 328, 16, BLACK);

    // Draw tree if not empty
    if (tree->root != tree->nil) {
      drawTree(tree, tree->root, 600, 120, 0, 280);
    } else {
      DrawText("Tree is empty", 550, 400, 24, GRAY);
      DrawText("Press 'A' to insert your first node!", 500, 430, 18, DARKGRAY);
    }

    // Draw current tree values (inorder)
    if (tree->root != tree->nil) {
      DrawText("Inorder traversal:", 10, 750, 16, DARKBLUE);
      char treeString[1000] = "";
      int values[1000];
      int count = 0;
      getAllValues(tree, tree->root, values, &count);

      for (int i = 0; i < count && i < 50; i++) { // Limit display
        char temp[20];
        snprintf(temp, sizeof(temp), "%d ", values[i]);
        strcat(treeString, temp);
      }

      if (count > 50) {
        strcat(treeString, "...");
      }

      DrawText(treeString, 150, 750, 14, BLACK);
    }

    EndDrawing();
  }

  CloseWindow();
}

// Example usage with step-by-step demonstration
int main() {
  printf("=== RED-BLACK TREE DEMONSTRATION ===\n\n");

  RBTree *tree = createRBTree();

  // Step-by-step insertions
  int insertValues[] = {10, 20, 30, 15, 25, 12, 18};
  int numInserts = sizeof(insertValues) / sizeof(insertValues[0]);

  printf("INSERTION SEQUENCE:\n");
  printf("Values to insert: ");
  for (int i = 0; i < numInserts; i++) {
    printf("%d ", insertValues[i]);
  }
  printf("\n\n");

  for (int i = 0; i < numInserts; i++) {
    printf("Step %d: Inserting %d\n", i + 1, insertValues[i]);
    insert(tree, insertValues[i]);
    printf("Tree after insertion (inorder): ");
    inorderTraversal(tree, tree->root);
    printf("\n");
    printf("Root: %d(%s)\n", tree->root->data,
           tree->root->color == RB_RED ? "RED" : "BLACK");
    printf("----------------------------------------\n");
  }

  printf("\nFinal tree structure (inorder traversal):\n");
  inorderTraversal(tree, tree->root);
  printf("\n\n");

  // Step-by-step deletions
  int deleteValues[] = {15, 10, 25};
  int numDeletes = sizeof(deleteValues) / sizeof(deleteValues[0]);

  printf("DELETION SEQUENCE:\n");
  for (int i = 0; i < numDeletes; i++) {
    printf("Step %d: Deleting %d\n", i + 1, deleteValues[i]);
    deleteNode(tree, deleteValues[i]);
    printf("Tree after deletion (inorder): ");
    inorderTraversal(tree, tree->root);
    printf("\n");
    if (tree->root != tree->nil) {
      printf("Root: %d(%s)\n", tree->root->data,
             tree->root->color == RB_RED ? "RED" : "BLACK");
    } else {
      printf("Tree is empty\n");
    }
    printf("----------------------------------------\n");
  }

  printf("\nStarting visualization...\n");
  printf("Close the window to exit.\n");

  // Start visualization
  visualizeTree(tree);

  return 0;
}
