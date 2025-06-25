/*******************************************************************************************
 * AVL Tree Visualizer
 *
 * This program provides a graphical visualization of an AVL Tree, a
 *self-balancing binary search tree.
 *
 * Properties of an AVL Tree:
 * 1. It is a standard Binary Search Tree.
 * 2. For every node, the height difference between its left and right subtrees
 * (the "balance factor") is at most 1.
 *
 * How to Compile:
 * - This code is written in C and uses the raylib and raygui libraries.
 * - You will need to link these libraries during compilation.
 * Example with gcc: gcc main.c -o avl_tree -lraylib -lGL -lm -lpthread -ldl
 *-lrt -lX11
 *
 * How to Use:
 * - Enter a number in the text box.
 * - If no number is entered, a random number is used.
 * - Click "Insert" to add the number to the tree.
 * - Click "Delete" to remove the number from the tree.
 * - Click "Reset" to clear the tree.
 *
 ********************************************************************************************/

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

// --- Data Structures ---

// AVL Tree Node Structure
typedef struct Node {
  int key;
  struct Node *left;
  struct Node *right;
  int height; // Height of the node
} Node;

// --- Global Variables ---
Node *root = NULL;

// --- Forward Declarations for Core Functions ---
Node *insertNode(Node *node, int key);
Node *deleteNode(Node *root, int key);
void freeTree(Node *node);

// --- Forward Declarations for Visualization Functions ---
void drawTree(Node *treeRoot);
void drawTreeRecursive(Node *node, int x, int y, int h_spacing);

// --- Core AVL Functions ---

/**
 * @brief Utility function to get the height of a node.
 * Returns 0 for a NULL node.
 * @param N The node to check.
 * @return The height of the node.
 */
int height(Node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

/**
 * @brief Utility function to get the maximum of two integers.
 * @param a First integer.
 * @param b Second integer.
 * @return The greater of the two integers.
 */
int max(int a, int b) { return (a > b) ? a : b; }

/**
 * @brief Creates a new AVL tree node with a given key.
 * @param key The key value for the new node.
 * @return A pointer to the newly created node.
 */
Node *createNode(int key) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1; // New node is initially added at a leaf
  return node;
}

/**
 * @brief Performs a right rotation on the subtree rooted with y.
 * This is used to fix a left-heavy imbalance.
 * @param y The root of the subtree to rotate.
 * @return The new root of the rotated subtree.
 */
Node *rightRotate(Node *y) {
  Node *x = y->left;
  Node *T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  // Return new root
  return x;
}

/**
 * @brief Performs a left rotation on the subtree rooted with x.
 * This is used to fix a right-heavy imbalance.
 * @param x The root of the subtree to rotate.
 * @return The new root of the rotated subtree.
 */
Node *leftRotate(Node *x) {
  Node *y = x->right;
  Node *T2 = y->left;

  // Perform rotation
  y->left = x;
  x->right = T2;

  // Update heights
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  // Return new root
  return y;
}

/**
 * @brief Gets the balance factor of a node.
 * Balance Factor = height(left subtree) - height(right subtree)
 * @param N The node to check.
 * @return The balance factor.
 */
int getBalance(Node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

/**
 * @brief Recursively inserts a key into the AVL tree.
 * After insertion, it balances the tree.
 * @param node The root of the subtree to insert into.
 * @param key The key to insert.
 * @return The new root of the subtree.
 */
Node *insertNode(Node *node, int key) {
  // 1. Perform standard BST insertion
  if (node == NULL)
    return (createNode(key));

  if (key < node->key)
    node->left = insertNode(node->left, key);
  else if (key > node->key)
    node->right = insertNode(node->right, key);
  else // Equal keys are not allowed in this AVL tree implementation
    return node;

  // 2. Update height of this ancestor node
  node->height = 1 + max(height(node->left), height(node->right));

  // 3. Get the balance factor of this ancestor node to check for imbalance
  int balance = getBalance(node);

  // 4. If the node becomes unbalanced, there are 4 cases

  // Left Left Case (Node is left-heavy, and new key was inserted in left
  // child's left subtree)
  if (balance > 1 && key < node->left->key)
    return rightRotate(node);

  // Right Right Case (Node is right-heavy, and new key was inserted in right
  // child's right subtree)
  if (balance < -1 && key > node->right->key)
    return leftRotate(node);

  // Left Right Case (Node is left-heavy, but new key was inserted in left
  // child's right subtree)
  if (balance > 1 && key > node->left->key) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  // Right Left Case (Node is right-heavy, but new key was inserted in right
  // child's left subtree)
  if (balance < -1 && key < node->right->key) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  // Return the (possibly unchanged) node pointer
  return node;
}

/**
 * @brief Finds the node with the minimum key value in a given tree.
 * @param node The root of the tree to search.
 * @return The node with the minimum key.
 */
Node *minValueNode(Node *node) {
  Node *current = node;
  // Loop down to find the leftmost leaf
  while (current->left != NULL)
    current = current->left;
  return current;
}

/**
 * @brief Recursively deletes a key from the AVL tree.
 * After deletion, it balances the tree.
 * @param root The root of the subtree to delete from.
 * @param key The key to delete.
 * @return The new root of the subtree.
 */
Node *deleteNode(Node *root, int key) {
  // 1. Perform standard BST delete
  if (root == NULL)
    return root;

  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else { // Node with the key to be deleted is found
    // Node with only one child or no child
    if ((root->left == NULL) || (root->right == NULL)) {
      Node *temp = root->left ? root->left : root->right;

      // No child case
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else           // One child case
        *root = *temp; // Copy the contents of the non-empty child
      free(temp);
    } else {
      // Node with two children: Get the inorder successor (smallest in the
      // right subtree)
      Node *temp = minValueNode(root->right);
      // Copy the inorder successor's data to this node
      root->key = temp->key;
      // Delete the inorder successor
      root->right = deleteNode(root->right, temp->key);
    }
  }

  // If the tree had only one node then return
  if (root == NULL)
    return root;

  // 2. Update height of the current node
  root->height = 1 + max(height(root->left), height(root->right));

  // 3. Get the balance factor of this node
  int balance = getBalance(root);

  // 4. If the node becomes unbalanced, there are 4 cases

  // Left Left Case
  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  // Left Right Case
  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  // Right Right Case
  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  // Right Left Case
  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

/**
 * @brief Frees all nodes in the tree recursively.
 * @param node The root of the tree/subtree to free.
 */
void freeTree(Node *node) {
  if (node == NULL)
    return;
  freeTree(node->left);
  freeTree(node->right);
  free(node);
}

// --- Visualization Functions ---

/**
 * @brief Recursively draws the tree nodes, lines, and info.
 * @param node The current node to draw.
 * @param x The center x-coordinate for this node.
 * @param y The y-coordinate for this node.
 * @param h_spacing The horizontal space allocated for this node's subtree.
 */
void drawTreeRecursive(Node *node, int x, int y, int h_spacing) {
  if (node == NULL) {
    return;
  }

  // Draw lines to children first (so they are behind the nodes)
  if (node->left != NULL) {
    DrawLine(x, y, x - h_spacing, y + 80, GRAY);
  }
  if (node->right != NULL) {
    DrawLine(x, y, x + h_spacing, y + 80, GRAY);
  }

  // Draw the node circle
  DrawCircle(x, y, 20, SKYBLUE);
  DrawCircleLines(x, y, 20, DARKBLUE);

  // Draw key value inside the circle
  char text[10];
  sprintf(text, "%d", node->key);
  int textWidth = MeasureText(text, 20);
  DrawText(text, x - textWidth / 2, y - 10, 20, BLACK);

  // Draw height and balance factor below the node
  char infoText[20];
  sprintf(infoText, "h:%d bf:%d", node->height, getBalance(node));
  int infoWidth = MeasureText(infoText, 10);
  DrawText(infoText, x - infoWidth / 2, y + 25, 10, DARKGRAY);

  // Recurse for children
  drawTreeRecursive(node->left, x - h_spacing, y + 80, h_spacing / 2);
  drawTreeRecursive(node->right, x + h_spacing, y + 80, h_spacing / 2);
}

/**
 * @brief Main drawing function that sets up the canvas.
 * @param treeRoot The root of the tree to draw.
 */
void drawTree(Node *treeRoot) {
  int start_x = GetScreenWidth() / 2;
  int start_y = 100;
  int initial_h_spacing = GetScreenWidth() / 4;

  BeginDrawing();
  ClearBackground((Color) { 45, 45, 45 });

  if (treeRoot == NULL) {
    DrawText("Tree is empty. Insert a node to begin.",
             GetScreenWidth() / 2 -
                 MeasureText("Tree is empty. Insert a node to begin.", 20) / 2,
             GetScreenHeight() / 2 - 10, 20, DARKGRAY);
  } else {
    drawTreeRecursive(treeRoot, start_x, start_y, initial_h_spacing);
  }
}

// --- Main Application ---
int main(void) {
  const int screenWidth = 1280;
  const int screenHeight = 720;
  InitWindow(screenWidth, screenHeight, "AVL Tree Visualizer");
  SetTargetFPS(60);
  srand(time(NULL));

  // GUI state
  char textBoxText[8] = {0};
  bool textBoxEditMode = false;

  // We need a way to find a value to delete randomly. A simple array is
  // sufficient.
  int values[1000];
  int count = 0;

  // Main game loop
  while (!WindowShouldClose()) {
    Rectangle textBox = {screenWidth / 2.0f - 190, 20, 120, 30};

    if (GuiButton((Rectangle){screenWidth / 2.0f - 60, 20, 80, 30}, "Insert")) {
      int value = atoi(textBoxText);
      if (value != 0 || strcmp(textBoxText, "0") == 0) {
        root = insertNode(root, value);
        values[count++] = value; // Store for random delete
        textBoxText[0] = '\0';
      } else {
        // Randomly add a value
        int r = rand() % 100;
        root = insertNode(root, r);
        values[count++] = r;
      }
    }

    if (GuiButton((Rectangle){screenWidth / 2.0f + 30, 20, 80, 30}, "Delete")) {
      int value = atoi(textBoxText);
      if (value != 0 || strcmp(textBoxText, "0") == 0) {
        root = deleteNode(root, value);
        textBoxText[0] = '\0';
      } else {
        // Randomly delete a value
        if (count > 0) {
          int rand_idx = rand() % count;
          int val_to_del = values[rand_idx];
          root = deleteNode(root, val_to_del);

          // Remove from our values array
          values[rand_idx] = values[count - 1];
          count--;
        }
      }
    }

    if (GuiButton((Rectangle){screenWidth / 2.0f + 120, 20, 80, 30}, "Reset")) {
      freeTree(root);
      root = NULL;
      count = 0;
      textBoxText[0] = '\0';
    }

    // --- Drawing ---
    drawTree(root);

    // Draw the GUI on top
    if (GuiTextBox(textBox, textBoxText, 8, textBoxEditMode)) {
      textBoxEditMode = !textBoxEditMode;
    }

    DrawText("AVL Tree Visualizer", 10, 10, 20, BLACK);
    DrawFPS(10, screenHeight - 20);

    EndDrawing();
  }

  // De-Initialization
  freeTree(root);
  CloseWindow();

  return 0;
}
