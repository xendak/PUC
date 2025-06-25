/*******************************************************************************************
 * Red-Black Tree
 *
 * How to Compile:
 * - use zig build :)
 * - or import raylib and raygui and math to cc
 *
 * How to Use:
 * - Enter a number in the text box.
 * - If no number is added, random % 100 is used.
 * - Click "Insert" to add the number to the tree.
 * - Click "Delete" to remove the number from the tree.
 * - Click "Reset" to clear the tree.
 *
 ********************************************************************************************/

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

// Enum for Node Colors
// Probably better to be a boolean though...
typedef enum { RB_RED, RB_BLACK } RB_Color;

// Tree Node Structure
typedef struct Node {
  int data;
  RB_Color color;
  struct Node *parent;
  struct Node *left;
  struct Node *right;
} Node;

// --- Global Variables ---
Node *root;
// NIL => black
Node *NIL;

// --- Forward Declarations for Core Functions ---
void leftRotate(Node *x);
void rightRotate(Node *y);
void insertFixup(Node *z);
void insert(int data);
void deleteFixup(Node *x);
void deleteNode(Node *z);
Node *findNode(int data);

// --- Forward Declarations for Visualization Functions ---
void drawTree(Node *treeRoot);
void drawTreeRecursive(Node *node, int x, int y, int h_spacing);

// Function to create a new node
Node *createNode(int data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->parent = NIL;
  newNode->left = NIL;
  newNode->right = NIL;
  newNode->data = data;

  // New nodes are always red
  newNode->color = RB_RED;
  return newNode;
}

// Left Rotate operation
void leftRotate(Node *x) {
  Node *y = x->right;
  x->right = y->left;

  if (y->left != NIL) {
    y->left->parent = x;
  }

  y->parent = x->parent;

  if (x->parent == NIL) {
    root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }

  y->left = x;
  x->parent = y;
}

// Right Rotate operation
void rightRotate(Node *y) {
  Node *x = y->left;
  y->left = x->right;

  if (x->right != NIL) {
    x->right->parent = y;
  }

  x->parent = y->parent;

  if (y->parent == NIL) {
    root = x;
  } else if (y == y->parent->right) {
    y->parent->right = x;
  } else {
    y->parent->left = x;
  }

  x->right = y;
  y->parent = x;
}

// Fixes the tree to maintain Red-Black properties after insertion
void insertFixup(Node *z) {
  // Loop as long as the parent of z is RED (violating Rule 4)
  while (z->parent->color == RB_RED) {
    // Case: Parent is a left child
    if (z->parent == z->parent->parent->left) {
      Node *y = z->parent->parent->right; // The uncle of z
      // Case 1: Uncle is RED
      if (y->color == RB_RED) {
        z->parent->color = RB_BLACK;
        y->color = RB_BLACK;
        z->parent->parent->color = RB_RED;
        z = z->parent->parent; // Move z up to the grandparent
      } else {
        // Case 2: Uncle is BLACK and z is a right child
        if (z == z->parent->right) {
          z = z->parent;
          leftRotate(z);
        }
        // Case 3: Uncle is BLACK and z is a left child
        z->parent->color = RB_BLACK;
        z->parent->parent->color = RB_RED;
        rightRotate(z->parent->parent);
      }
    }
    // Case: Parent is a right child (symmetric to the above)
    else {
      Node *y = z->parent->parent->left; // The uncle of z
      // Case 1: Uncle is RED
      if (y->color == RB_RED) {
        z->parent->color = RB_BLACK;
        y->color = RB_BLACK;
        z->parent->parent->color = RB_RED;
        z = z->parent->parent;
      } else {
        // Case 2: Uncle is BLACK and z is a left child
        if (z == z->parent->left) {
          z = z->parent;
          rightRotate(z);
        }
        // Case 3: Uncle is BLACK and z is a right child
        z->parent->color = RB_BLACK;
        z->parent->parent->color = RB_RED;
        leftRotate(z->parent->parent);
      }
    }
  }
  // Ensure the root is always BLACK (Rule 2)
  root->color = RB_BLACK;
}

// Insert a node if and only if data is unique
void insert(int data) {
  Node *y = NIL;
  Node *x = root;

  // insert in binary tree
  while (x != NIL) {
    y = x;
    if (data < x->data) {
      x = x->left;
    } else if (data > x->data) {
      x = x->right;
    } else {
      return;
    }
  }

  Node *z = createNode(data);

  z->parent = y;
  if (y == NIL) {
    root = z;
  } else if (z->data < y->data) {
    y->left = z;
  } else {
    y->right = z;
  }

  // Fix the tree so that the RB tree properties are still mainted.
  insertFixup(z);
}

// Helper function to replace one subtree with another
void transplant(Node *u, Node *v) {
  if (u->parent == NIL) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

// Find the node with min value
Node *minimum(Node *node) {
  while (node->left != NIL) {
    node = node->left;
  }
  return node;
}

// Fixes the tree to maintain Red-Black properties after deletion
void deleteFixup(Node *x) {
  while (x != root && x->color == RB_BLACK) {
    if (x == x->parent->left) {
      Node *w = x->parent->right; // Sibling of x
      // Case 1: Sibling w is RED
      if (w->color == RB_RED) {
        w->color = RB_BLACK;
        x->parent->color = RB_RED;
        leftRotate(x->parent);
        w = x->parent->right;
      }
      // Case 2: Sibling w is BLACK, and both of w's children are BLACK
      if (w->left->color == RB_BLACK && w->right->color == RB_BLACK) {
        w->color = RB_RED;
        x = x->parent;
      } else {
        // Case 3: Sibling w is BLACK, w's left child is RED, right child is
        // BLACK
        if (w->right->color == RB_BLACK) {
          w->left->color = RB_BLACK;
          w->color = RB_RED;
          rightRotate(w);
          w = x->parent->right;
        }
        // Case 4: Sibling w is BLACK, and w's right child is RED
        w->color = x->parent->color;
        x->parent->color = RB_BLACK;
        w->right->color = RB_BLACK;
        leftRotate(x->parent);
        x = root; // End loop
      }
    } else {                     // x->parent->right
      Node *w = x->parent->left; // Sibling of x
      // Case 1: Sibling w is RED
      if (w->color == RB_RED) {
        w->color = RB_BLACK;
        x->parent->color = RB_RED;
        rightRotate(x->parent);
        w = x->parent->left;
      }
      // Case 2: Sibling w is BLACK, and both children are BLACK
      if (w->right->color == RB_BLACK && w->left->color == RB_BLACK) {
        w->color = RB_RED;
        x = x->parent;
      } else {
        // Case 3: Sibling w is BLACK, w's right is RED, left is BLACK
        if (w->left->color == RB_BLACK) {
          w->right->color = RB_BLACK;
          w->color = RB_RED;
          leftRotate(w);
          w = x->parent->left;
        }
        // Case 4: Sibling w is BLACK, and w's left child is RED
        w->color = x->parent->color;
        x->parent->color = RB_BLACK;
        w->left->color = RB_BLACK;
        rightRotate(x->parent);

        // Force exit
        x = root;
      }
    }
  }
  x->color = RB_BLACK;
}

// Delete a node
void deleteNode(Node *z) {
  if (z == NIL)
    return;

  Node *y = z;
  Node *x;
  RB_Color y_original_color = y->color;

  if (z->left == NIL) {
    x = z->right;
    transplant(z, z->right);
  } else if (z->right == NIL) {
    x = z->left;
    transplant(z, z->left);
  } else {
    y = minimum(z->right);
    y_original_color = y->color;
    x = y->right;
    if (y->parent == z) {
      x->parent = y;
    } else {
      transplant(y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    transplant(z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }

  free(z);

  if (y_original_color == RB_BLACK) {
    deleteFixup(x);
  }
}

// Find a node with a given value
Node *findNode(int data) {
  Node *current = root;
  while (current != NIL) {
    if (data == current->data) {
      return current;
    } else if (data < current->data) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return NIL;
}

// Free all nodes in the tree
void freeTree(Node *node) {
  if (node == NIL)
    return;
  freeTree(node->left);
  freeTree(node->right);
  free(node);
}

// Recursively draws the tree
void drawTreeRecursive(Node *node, int x, int y, int h_spacing) {
  if (node == NULL || node == NIL) {
    return;
  }

  // Draw lines to children first (so they are behind the nodes)
  if (node->left != NIL) {
    DrawLine(x, y, x - h_spacing, y + 80, GRAY);
  }
  if (node->right != NIL) {
    DrawLine(x, y, x + h_spacing, y + 80, GRAY);
  }

  Color nodeColor = (node->color == RB_RED) ? RED : BLACK;
  DrawCircle(x, y, 20, nodeColor);

  // Draw text
  char text[10];
  sprintf(text, "%d", node->data);
  int textWidth = MeasureText(text, 20);
  DrawText(text, x - textWidth / 2, y - 10, 20, RAYWHITE);

  // Recurse for children
  drawTreeRecursive(node->left, x - h_spacing, y + 80, h_spacing / 2);
  drawTreeRecursive(node->right, x + h_spacing, y + 80, h_spacing / 2);
}

// Main drawing function
void drawTree(Node *treeRoot) {
  int start_x = GetScreenWidth() / 2;
  int start_y = 100;
  int initial_h_spacing = GetScreenWidth() / 4;

  BeginDrawing();
  ClearBackground(SKYBLUE);

  if (treeRoot == NIL) {
    DrawText("Tree is empty. Insert a node to begin.",
             GetScreenWidth() / 2 -
                 MeasureText("Tree is empty. Insert a node to begin.", 20) / 2,
             GetScreenHeight() / 2 - 10, 20, DARKGRAY);
  } else {
    drawTreeRecursive(treeRoot, start_x, start_y, initial_h_spacing);
  }
}

int main(void) {
  const int screenWidth = 1280;
  const int screenHeight = 720;
  InitWindow(screenWidth, screenHeight, "Red-Black Tree Visualizer");
  SetTargetFPS(60);
  srand(30);

  // Initialize the NIL sentinel node
  NIL = (Node *)malloc(sizeof(Node));
  NIL->color = RB_BLACK;
  NIL->left = NULL;
  NIL->right = NULL;
  NIL->parent = NULL;
  NIL->data = 0;
  root = NIL;

  // GUI state
  char textBoxText[8] = {0};
  bool textBoxEditMode = false;
  int values[1000];
  int count = 0;

  // Main game loop
  while (!WindowShouldClose()) {
    Rectangle textBox = {screenWidth / 2.0 - 190, 20, 120, 30};

    if (GuiButton((Rectangle){screenWidth / 2.0 - 60, 20, 80, 30}, "Insert")) {
      int value = atoi(textBoxText);
      if (value != 0 || textBoxText[0] == '0') {
        insert(value);
        textBoxText[0] = '\0';
        values[count++] = value;
      } else {
        // Randomly add a value
        int r = rand() % 100;
        Node *toAdd = findNode(r);
        while (toAdd != NIL) {
          r = rand() % 100;
          toAdd = findNode(r);
        }
        insert(r);
        values[count++] = r;
      }
    }

    if (GuiButton((Rectangle){screenWidth / 2.0 + 30, 20, 80, 30}, "Delete")) {
      int value = atoi(textBoxText);
      if (value != 0 || textBoxText[0] == '0') {
        Node *nodeToDelete = findNode(value);
        if (nodeToDelete != NIL) {
          deleteNode(nodeToDelete);
          int toDeleteIndex = 0;
          while (values[toDeleteIndex++] != value)
            ;
          ;
          for (int i = toDeleteIndex; i < count; i++) {
            values[i] = values[i + 1];
          }
          count = count > 0 ? count - 1 : 0;
        }
        textBoxText[0] = '\0';
      } else {
        // Randomly delete a value
        if (root != NIL) {
          int randomIndex = count == 1 ? 0 : rand() % (count - 1);
          int valueToDelete = values[randomIndex];
          Node *nodeToDelete = findNode(valueToDelete);
          if (nodeToDelete != NIL) {

            deleteNode(nodeToDelete);
            for (int i = randomIndex; i < count; i++) {
              values[i] = values[i + 1];
            }
            count = count > 0 ? count - 1 : 0;
          }
        }
      }
    }

    if (GuiButton((Rectangle){screenWidth / 2.0 + 120, 20, 80, 30}, "Reset")) {
      freeTree(root);
      root = NIL;
      count = 0;
      textBoxText[0] = '\0';
    }

    drawTree(root);
    // Draw the GUI on top
    if (GuiTextBox(textBox, textBoxText, 8, textBoxEditMode)) {
      textBoxEditMode = !textBoxEditMode;
    }

    DrawText("Red-Black Tree", 10, 10, 20, BLACK);
    DrawFPS(10, screenHeight - 20);

    EndDrawing();
  }

  // De-Initialization
  freeTree(root);
  free(NIL);
  CloseWindow();

  return 0;
}
