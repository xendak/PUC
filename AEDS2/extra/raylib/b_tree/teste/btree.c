/*******************************************************************************************
 * 2-3-4 Tree Visualizer
 *
 * This program provides a graphical visualization of a 2-3-4 Tree data
 *structure. 2-3-4 trees are a type of self-balancing tree, a specific order of
 *B-Tree.
 *
 * Properties of a 2-3-4 Tree:
 * 1. Every node is a 2-node, 3-node, or 4-node, holding one, two, or three
 *keys.
 * 2. All leaves are at the same depth.
 * 3. Data is kept in sorted order within nodes and across subtrees.
 *
 * How to Compile:
 * - This code is written in C and uses the raylib and raygui libraries.
 * - You will need to link these libraries during compilation.
 * Example with gcc: gcc main.c -o btree -lraylib -lGL -lm -lpthread -ldl -lrt
 *-lX11
 *
 * How to Use:
 * - Enter a number in the text box.
 * - Click "Insert" to add the number to the tree. If the box is empty, a random
 *number is used.
 * - Click "Delete" to remove the number from the tree. If the box is empty, a
 *random existing number is deleted.
 * - Click "Reset" to clear the tree.
 *
 ********************************************************************************************/

#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h> // For memcpy and memmove

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

// --- Configuration ---
#define MAX_KEYS 3 // A 4-node has 3 keys.
#define MIN_KEYS 1 // A 2-node has 1 key. (t-1 in B-Tree terms)

// --- Data Structures ---

// Tree Node Structure for a 2-3-4 Tree
typedef struct Node {
  int num_keys;                        // Number of data elements (1, 2, or 3)
  int keys[MAX_KEYS];                  // Data elements (keys)
  struct Node *children[MAX_KEYS + 1]; // Pointers to children
  struct Node *parent;                 // Pointer to parent node
} Node;

// --- Global Variables ---
Node *root = NULL; // The root of the 2-3-4 tree

// --- Forward Declarations for Core Functions ---
void insert(int key);
void deleteKey(int key);
void freeTree(Node *node);
bool findKey(int key, Node **node_found, int *key_index);

// --- Forward Declarations for Visualization Functions ---
void drawTree(Node *treeRoot);
void drawTreeRecursive(Node *node, int x, int y, int h_spacing);

// --- Core B-Tree Functions ---

/**
 * @brief Creates and initializes a new tree node.
 * @return A pointer to the newly allocated node.
 */
Node *createNode() {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    // Handle memory allocation failure if necessary
    perror("Failed to allocate memory for new node");
    exit(EXIT_FAILURE);
  }
  newNode->num_keys = 0;
  newNode->parent = NULL;
  for (int i = 0; i < MAX_KEYS; i++) {
    newNode->keys[i] = 0;
  }
  for (int i = 0; i < MAX_KEYS + 1; i++) {
    newNode->children[i] = NULL;
  }
  return newNode;
}

/**
 * @brief Splits a full child node of a given parent node.
 * This is a key operation for insertion that prevents nodes from overflowing.
 * @param parent The parent of the child to be split.
 * @param child_index The index of the full child in the parent's children
 * array.
 */
void splitChild(Node *parent, int child_index) {
  Node *child_to_split = parent->children[child_index];
  Node *new_sibling = createNode();
  new_sibling->parent = parent;

  // The middle key of the child moves up to the parent.
  int middle_key = child_to_split->keys[MIN_KEYS];

  // Keys after the middle key move to the new sibling.
  new_sibling->num_keys = MIN_KEYS;
  new_sibling->keys[0] = child_to_split->keys[MIN_KEYS + 1];

  // If the split child was not a leaf, its children must also be moved.
  if (child_to_split->children[0] != NULL) {
    for (int i = 0; i < MIN_KEYS + 1; i++) {
      new_sibling->children[i] = child_to_split->children[MIN_KEYS + 1 + i];
      if (new_sibling->children[i] != NULL)
        new_sibling->children[i]->parent = new_sibling;
    }
  }

  // The original child's key count is reduced.
  child_to_split->num_keys = MIN_KEYS;

  // Make space in the parent for the new child pointer.
  for (int i = parent->num_keys; i > child_index; i--) {
    parent->children[i + 1] = parent->children[i];
  }
  parent->children[child_index + 1] = new_sibling;

  // Make space in the parent for the key moved up from the child.
  for (int i = parent->num_keys - 1; i >= child_index; i--) {
    parent->keys[i + 1] = parent->keys[i];
  }
  parent->keys[child_index] = middle_key;
  parent->num_keys++;
}

/**
 * @brief Inserts a key into a node that is guaranteed to be non-full.
 * @param node The node to insert into.
 * @param key The key to insert.
 */
void insertNonFull(Node *node, int key) {
  int i = node->num_keys - 1;

  // If the node is a leaf, insert the key directly.
  if (node->children[0] == NULL) {
    while (i >= 0 && key < node->keys[i]) {
      node->keys[i + 1] = node->keys[i];
      i--;
    }
    node->keys[i + 1] = key;
    node->num_keys++;
  } else { // If the node is internal, find the correct child to descend to.
    while (i >= 0 && key < node->keys[i]) {
      i--;
    }
    i++; // The index of the child to descend into.

    // If the child is full, split it before descending.
    if (node->children[i]->num_keys == MAX_KEYS) {
      splitChild(node, i);
      // After splitting, the key from the child moves to the parent.
      // We must check if the new key should go into the newly created sibling.
      if (key > node->keys[i]) {
        i++;
      }
    }
    insertNonFull(node->children[i], key);
  }
}

/**
 * @brief Public function to insert a key into the 2-3-4 tree.
 * @param key The key to be inserted.
 */
void insert(int key) {
  // Cannot insert a key that already exists.
  Node *existing_node;
  int existing_index;
  if (findKey(key, &existing_node, &existing_index)) {
    return;
  }

  // If the tree is empty, create a root.
  if (root == NULL) {
    root = createNode();
    root->keys[0] = key;
    root->num_keys = 1;
    return;
  }

  // If the root is full, the tree must grow in height.
  if (root->num_keys == MAX_KEYS) {
    Node *new_root = createNode();
    new_root->children[0] = root;
    root->parent = new_root;
    splitChild(new_root, 0);
    root = new_root;
  }

  insertNonFull(root, key);
}

/**
 * @brief Merges a child node with its right sibling.
 * This is a helper function for deletion.
 * @param parent The parent of the nodes to be merged.
 * @param child_index The index of the left child to be merged.
 */
void mergeChildren(Node *parent, int child_index) {
  Node *left_child = parent->children[child_index];
  Node *right_sibling = parent->children[child_index + 1];

  // Pull a key down from the parent into the left child.
  left_child->keys[left_child->num_keys] = parent->keys[child_index];

  // Copy keys from the right sibling to the left child.
  for (int i = 0; i < right_sibling->num_keys; i++) {
    left_child->keys[left_child->num_keys + 1 + i] = right_sibling->keys[i];
  }

  // If not a leaf, copy child pointers from the right sibling as well.
  if (right_sibling->children[0] != NULL) {
    for (int i = 0; i <= right_sibling->num_keys; i++) {
      left_child->children[left_child->num_keys + 1 + i] =
          right_sibling->children[i];
      if (left_child->children[left_child->num_keys + 1 + i] != NULL)
        left_child->children[left_child->num_keys + 1 + i]->parent = left_child;
    }
  }

  // Update the key count of the merged node.
  left_child->num_keys += right_sibling->num_keys + 1;

  // Free the now-empty right sibling.
  free(right_sibling);

  // Shift keys and children in the parent to fill the gap.
  for (int i = child_index; i < parent->num_keys - 1; i++) {
    parent->keys[i] = parent->keys[i + 1];
  }
  for (int i = child_index + 1; i < parent->num_keys; i++) {
    parent->children[i] = parent->children[i + 1];
  }

  parent->num_keys--;

  // If the parent becomes empty and it's the root, the merged child becomes the
  // new root.
  if (parent == root && parent->num_keys == 0) {
    root = left_child;
    root->parent = NULL;
    free(parent);
  }
}

/**
 * @brief Internal recursive function to delete a key.
 * Ensures that the function always descends into a node with at least MIN_KEYS
 * + 1 keys.
 * @param node The current node in the traversal.
 * @param key The key to delete.
 */
void deleteInternal(Node *node, int key) {
  if (!node)
    return;

  int i = 0;
  while (i < node->num_keys && key > node->keys[i]) {
    i++;
  }

  // Case 1: The key is found in the current node.
  if (i < node->num_keys && key == node->keys[i]) {
    if (node->children[0] == NULL) { // The node is a leaf.
      // Simply remove the key.
      for (int j = i; j < node->num_keys - 1; j++) {
        node->keys[j] = node->keys[j + 1];
      }
      node->num_keys--;
    } else { // The node is internal.
      Node *pred_node = node->children[i];
      Node *succ_node = node->children[i + 1];

      // Replace key with predecessor.
      if (pred_node->num_keys > MIN_KEYS) {
        Node *current = pred_node;
        while (current->children[0] != NULL) {
          current = current->children[current->num_keys];
        }
        int predecessor = current->keys[current->num_keys - 1];
        node->keys[i] = predecessor;
        deleteInternal(pred_node, predecessor);
      }
      // Replace key with successor.
      else if (succ_node->num_keys > MIN_KEYS) {
        Node *current = succ_node;
        while (current->children[0] != NULL) {
          current = current->children[0];
        }
        int successor = current->keys[0];
        node->keys[i] = successor;
        deleteInternal(succ_node, successor);
      }
      // Merge predecessor and successor nodes.
      else {
        mergeChildren(node, i);
        deleteInternal(node->children[i], key);
      }
    }
  }
  // Case 2: The key is not in the current node, so descend.
  else {
    Node *child_node = node->children[i];
    if (child_node == NULL)
      return; // Key not in tree

    // If the child node has the minimum number of keys, we must ensure it has
    // more before descending.
    if (child_node->num_keys == MIN_KEYS) {
      Node *left_sibling = (i > 0) ? node->children[i - 1] : NULL;
      Node *right_sibling = (i < node->num_keys) ? node->children[i + 1] : NULL;

      // Borrow from right sibling.
      if (right_sibling && right_sibling->num_keys > MIN_KEYS) {
        child_node->keys[child_node->num_keys] = node->keys[i];
        node->keys[i] = right_sibling->keys[0];
        child_node->num_keys++;

        if (right_sibling->children[0] != NULL) {
          child_node->children[child_node->num_keys] =
              right_sibling->children[0];
          if (child_node->children[child_node->num_keys])
            child_node->children[child_node->num_keys]->parent = child_node;
        }

        for (int j = 0; j < right_sibling->num_keys - 1; j++) {
          right_sibling->keys[j] = right_sibling->keys[j + 1];
        }
        if (right_sibling->children[0] != NULL) {
          for (int j = 0; j < right_sibling->num_keys; j++) {
            right_sibling->children[j] = right_sibling->children[j + 1];
          }
        }
        right_sibling->num_keys--;
      }
      // Borrow from left sibling.
      else if (left_sibling && left_sibling->num_keys > MIN_KEYS) {
        for (int j = child_node->num_keys; j > 0; j--) {
          child_node->keys[j] = child_node->keys[j - 1];
        }
        if (child_node->children[0] != NULL) {
          for (int j = child_node->num_keys + 1; j > 0; j--) {
            child_node->children[j] = child_node->children[j - 1];
          }
        }

        child_node->keys[0] = node->keys[i - 1];
        node->keys[i - 1] = left_sibling->keys[left_sibling->num_keys - 1];
        child_node->num_keys++;

        if (left_sibling->children[0] != NULL) {
          child_node->children[0] =
              left_sibling->children[left_sibling->num_keys];
          if (child_node->children[0])
            child_node->children[0]->parent = child_node;
        }
        left_sibling->num_keys--;
      }
      // Merge with a sibling.
      else {
        if (right_sibling) {
          mergeChildren(node, i);
        } else { // Merge with left sibling
          mergeChildren(node, i - 1);
          child_node = node->children[i - 1]; // We descend into the merged node
        }
      }
    }
    deleteInternal(child_node, key);
  }
}

/**
 * @brief Public function to delete a key from the tree.
 * @param key The key to be deleted.
 */
void deleteKey(int key) {
  Node *node_found = NULL;
  int key_index = -1;
  // We can only delete a key if it exists.
  if (!findKey(key, &node_found, &key_index)) {
    return;
  }

  deleteInternal(root, key);

  // If root becomes empty, the tree might shrink.
  if (root && root->num_keys == 0) {
    if (root->children[0] != NULL) {
      Node *old_root = root;
      root = root->children[0];
      root->parent = NULL;
      free(old_root);
    } else {
      free(root);
      root = NULL;
    }
  }
}

/**
 * @brief Finds a key in the tree.
 * @param key The key to search for.
 * @param node_found Output parameter for the node containing the key.
 * @param key_index Output parameter for the index of the key within the node.
 * @return True if the key is found, false otherwise.
 */
bool findKey(int key, Node **node_found, int *key_index) {
  Node *current = root;
  while (current != NULL) {
    int i = 0;
    // Find the first key in the current node that is >= the search key
    while (i < current->num_keys && key > current->keys[i]) {
      i++;
    }

    // Check if we found the key
    if (i < current->num_keys && key == current->keys[i]) {
      *node_found = current;
      *key_index = i;
      return true;
    }

    // If the node is a leaf, we have nowhere else to look.
    if (current->children[0] == NULL) {
      return false;
    }

    // Descend to the appropriate child.
    current = current->children[i];
  }
  return false;
}

/**
 * @brief Frees all nodes in the tree recursively.
 * @param node The root of the tree/subtree to free.
 */
void freeTree(Node *node) {
  if (node == NULL)
    return;

  // Recurse for all children
  if (node->children[0] != NULL) { // Not a leaf
    for (int i = 0; i <= node->num_keys; i++) {
      freeTree(node->children[i]);
    }
  }
  free(node);
}

// --- Visualization Functions ---

/**
 * @brief Recursively draws the tree nodes and connecting lines.
 * @param node The current node to draw.
 * @param x The center x-coordinate for this node's drawing area.
 * @param y The y-coordinate for this node.
 * @param h_spacing The total horizontal space allocated for this node's
 * subtree.
 */
void drawTreeRecursive(Node *node, int x, int y, int h_spacing) {
  if (node == NULL) {
    return;
  }

  // Node visual properties
  const int node_height = 40;
  const int key_width = 35;
  const int key_padding = 5;
  const int node_width =
      (node->num_keys * key_width) + ((node->num_keys - 1) * key_padding);
  const int start_x = x - node_width / 2;

  // Draw lines to children first (so they are behind the nodes)
  if (node->children[0] != NULL) {
    int child_h_spacing = h_spacing / (node->num_keys + 1);
    for (int i = 0; i <= node->num_keys; i++) {
      int child_x =
          (x - h_spacing / 2) + (i * child_h_spacing) + child_h_spacing / 2;
      int child_y = y + 80;
      DrawLine(x, y + node_height / 2, child_x, child_y - node_height / 2,
               GRAY);
      // Recurse for children
      drawTreeRecursive(node->children[i], child_x, child_y, child_h_spacing);
    }
  }

  // Draw the node box(es)
  for (int i = 0; i < node->num_keys; i++) {
    Rectangle rect = {start_x + i * (key_width + key_padding),
                      y - node_height / 2, key_width, node_height};
    DrawRectangleRec(rect, SKYBLUE);
    DrawRectangleLinesEx(rect, 2, DARKGRAY);

    // Draw text
    char text[10];
    sprintf(text, "%d", node->keys[i]);
    int textWidth = MeasureText(text, 20);
    DrawText(text, rect.x + (key_width - textWidth) / 2,
             rect.y + (node_height - 20) / 2, 20, BLACK);
  }
}

/**
 * @brief Main drawing function that sets up the canvas and calls the recursive
 * drawer.
 * @param treeRoot The root of the tree to draw.
 */
void drawTree(Node *treeRoot) {
  int start_x = GetScreenWidth() / 2;
  int start_y = 100;
  int initial_h_spacing = GetScreenWidth() - 50;

  BeginDrawing();
  ClearBackground((Color) {45, 45, 45} );

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
  InitWindow(screenWidth, screenHeight, "2-3-4 Tree Visualizer");
  SetTargetFPS(60);
  srand(time(NULL));

  // --- GUI State ---
  char textBoxText[8] = {0};
  bool textBoxEditMode = false;
  int values[1000]; // To keep track of inserted values for random deletion
  int count = 0;

  // --- Main Loop ---
  while (!WindowShouldClose()) {
    Rectangle textBox = {screenWidth / 2.0 - 190, 20, 120, 30};

    // Handle Insert Button
    if (GuiButton((Rectangle){screenWidth / 2.0 - 60, 20, 80, 30}, "Insert")) {
      int value = atoi(textBoxText);
      if (value != 0 || strcmp(textBoxText, "0") == 0) {
        insert(value);
        values[count++] = value;
        textBoxText[0] = '\0';
      } else { // Insert a random value if textbox is empty
        int r = rand() % 100;
        Node *n;
        int ki;
        while (findKey(r, &n, &ki)) { // Ensure value is unique
          r = rand() % 100;
        }
        insert(r);
        values[count++] = r;
      }
    }

    // Handle Delete Button
    if (GuiButton((Rectangle){screenWidth / 2.0 + 30, 20, 80, 30}, "Delete")) {
      int value = atoi(textBoxText);
      if (value != 0 || strcmp(textBoxText, "0") == 0) {
        deleteKey(value);
        // Simple removal from values array for demo purposes
        // This is not efficient for large N.
        int found_idx = -1;
        for (int i = 0; i < count; i++)
          if (values[i] == value)
            found_idx = i;
        if (found_idx != -1) {
          for (int i = found_idx; i < count - 1; i++)
            values[i] = values[i + 1];
          count--;
        }
        textBoxText[0] = '\0';
      } else { // Delete a random value if textbox is empty
        if (count > 0) {
          int rand_idx = rand() % count;
          int val_to_del = values[rand_idx];
          deleteKey(val_to_del);
          for (int i = rand_idx; i < count - 1; i++)
            values[i] = values[i + 1];
          count--;
        }
      }
    }

    // Handle Reset Button
    if (GuiButton((Rectangle){screenWidth / 2.0 + 120, 20, 80, 30}, "Reset")) {
      freeTree(root);
      root = NULL;
      count = 0;
      textBoxText[0] = '\0';
    }

    // --- Drawing ---
    drawTree(root);

    // Draw GUI controls on top
    if (GuiTextBox(textBox, textBoxText, 8, textBoxEditMode)) {
      textBoxEditMode = !textBoxEditMode;
    }

    DrawText("2-3-4 Tree", 10, 10, 20, DARKGRAY);
    DrawFPS(10, screenHeight - 20);

    EndDrawing();
  }

  // --- De-Initialization ---
  freeTree(root);
  CloseWindow();
  return 0;
}
