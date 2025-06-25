/*******************************************************************************************
 * Trie (Prefix Tree) Visualizer
 *
 * This program provides a graphical visualization of a Trie data structure,
 * commonly used for storing a set of strings.
 *
 * Properties of a Trie:
 * 1. The root node represents an empty string.
 * 2. Each node has up to 26 children (for 'a' through 'z').
 * 3. Each edge from a parent to a child represents a character.
 * 4. A path from the root to a specific node represents a prefix.
 * 5. A node can be marked as the end of a complete word.
 *
 * How to Compile:
 * - This code is written in C and uses the raylib and raygui libraries.
 * - You will need to link these libraries during compilation.
 * Example with gcc: gcc main.c -o trie -lraylib -lGL -lm -lpthread -ldl -lrt
 *-lX11
 *
 * How to Use:
 * - Enter a lowercase word in the text box.
 * - Click "Insert" to add the word to the trie.
 * - Click "Search" to check if the word exists in the trie.
 * - Click "Delete" to remove the word from the trie.
 * - Click "Reset" to clear the trie.
 *
 ********************************************************************************************/
#include "raylib.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

// --- Configuration ---
#define ALPHABET_SIZE 26

// --- Data Structures ---

// Trie node structure
typedef struct TrieNode {
  struct TrieNode *children[ALPHABET_SIZE];
  bool isEndOfWord;
} TrieNode;

// --- Global Variables ---
TrieNode *root = NULL;

// --- Forward Declarations for Core Functions ---
TrieNode *createNode(void);
void insertWord(const char *word);
bool searchWord(const char *word);
bool deleteWord(const char *word);
void freeTrie(TrieNode *node);

// --- Forward Declarations for Visualization Functions ---
void drawTrie(TrieNode *trieRoot);
void drawTrieRecursive(TrieNode *node, int x, int y);
int calculateSubtreeWidth(TrieNode *node);

// --- Core Trie Functions ---

/**
 * @brief Creates and initializes a new, empty Trie node.
 * @return A pointer to the newly allocated node.
 */
TrieNode *createNode(void) {
  TrieNode *pNode = (TrieNode *)malloc(sizeof(TrieNode));
  if (pNode) {
    pNode->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
      pNode->children[i] = NULL;
    }
  }
  return pNode;
}

/**
 * @brief Inserts a word into the trie.
 * @param word The word to insert (should be lowercase).
 */
void insertWord(const char *word) {
  if (root == NULL) {
    root = createNode();
  }
  TrieNode *pCrawl = root;
  int length = strlen(word);
  for (int i = 0; i < length; i++) {
    int index = word[i] - 'a';
    if (index < 0 || index >= ALPHABET_SIZE)
      continue; // Ignore non-lowercase chars

    if (!pCrawl->children[index]) {
      pCrawl->children[index] = createNode();
    }
    pCrawl = pCrawl->children[index];
  }
  pCrawl->isEndOfWord = true;
}

/**
 * @brief Searches for a word in the trie.
 * @param word The word to search for (should be lowercase).
 * @return True if the word is found, false otherwise.
 */
bool searchWord(const char *word) {
  if (root == NULL)
    return false;
  TrieNode *pCrawl = root;
  int length = strlen(word);
  for (int i = 0; i < length; i++) {
    int index = word[i] - 'a';
    if (index < 0 || index >= ALPHABET_SIZE)
      return false;

    if (!pCrawl->children[index]) {
      return false;
    }
    pCrawl = pCrawl->children[index];
  }
  return (pCrawl != NULL && pCrawl->isEndOfWord);
}

/**
 * @brief Helper function to check if a node has any children.
 * @return True if the node has no children, false otherwise.
 */
bool isEmpty(TrieNode *node) {
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (node->children[i]) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Recursive helper function to delete a word from the trie.
 * @param node The current node in the recursion.
 * @param word The word to delete.
 * @param depth The current depth in the trie.
 * @return The node passed in, possibly modified or freed.
 */
TrieNode *deleteRecursive(TrieNode *node, const char *word, int depth) {
  if (!node)
    return NULL;

  // If we are at the end of the word
  if (depth == strlen(word)) {
    if (node->isEndOfWord) {
      node->isEndOfWord = false;
    }
    // If the node is not a prefix for another word, it can be deleted.
    if (isEmpty(node)) {
      free(node);
      node = NULL;
    }
    return node;
  }

  // Recur for the child corresponding to the next character
  int index = word[depth] - 'a';
  if (index >= 0 && index < ALPHABET_SIZE) {
    node->children[index] =
        deleteRecursive(node->children[index], word, depth + 1);
  }

  // If node does not have any children (its only child got deleted)
  // and it is not the end of another word.
  if (isEmpty(node) && !node->isEndOfWord) {
    free(node);
    node = NULL;
  }

  return node;
}

/**
 * @brief Public function to delete a word from the trie.
 * @param word The word to delete.
 */
bool deleteWord(const char *word) {
  if (!searchWord(word))
    return false; // Can't delete if it doesn't exist
  root = deleteRecursive(root, word, 0);
  return true;
}

/**
 * @brief Frees all nodes in the trie recursively.
 * @param node The root of the trie/subtree to free.
 */
void freeTrie(TrieNode *node) {
  if (node == NULL)
    return;
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (node->children[i]) {
      freeTrie(node->children[i]);
    }
  }
  free(node);
}

// --- Visualization Functions ---

/**
 * @brief Recursively calculates the horizontal space required by a subtree.
 * This is a pure calculation function and does not draw anything.
 * @param node The root of the subtree to measure.
 * @return The total horizontal width in pixels.
 */
int calculateSubtreeWidth(TrieNode *node) {
  if (!node)
    return 0;

  const int horizontal_spacing = 35;
  int total_width = 0;
  int child_count = 0;

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (node->children[i]) {
      total_width += calculateSubtreeWidth(node->children[i]);
      child_count++;
    }
  }

  if (child_count == 0) {
    return horizontal_spacing; // Base width for a leaf's placeholder
  }

  // Add spacing between the children's subtrees
  total_width += (child_count - 1) * (horizontal_spacing / 2);

  return total_width;
}

/**
 * @brief Recursively draws the trie nodes and connecting lines.
 * It uses calculateSubtreeWidth to determine layout.
 * @param node The current node to draw.
 * @param x The center x-coordinate for this node.
 * @param y The y-coordinate for this node.
 */
void drawTrieRecursive(TrieNode *node, int x, int y) {
  if (node == NULL)
    return;

  // Node visual properties
  const int node_radius = 15;
  const int vertical_spacing = 80;
  const int horizontal_spacing = 35;

  // Draw the node itself
  Color node_color = node->isEndOfWord ? GOLD : SKYBLUE;
  DrawCircle(x, y, node_radius, node_color);
  DrawCircleLines(x, y, node_radius, DARKGRAY);

  // Calculate total width of all children to center them under this node
  int total_children_width = calculateSubtreeWidth(node);
  int start_x = x - total_children_width / 2;
  int current_child_x_offset = 0;

  // Iterate through children to draw them at correct positions
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (node->children[i]) {
      int child_subtree_width = calculateSubtreeWidth(node->children[i]);

      int child_x = start_x + current_child_x_offset + child_subtree_width / 2;
      int child_y = y + vertical_spacing;

      // Draw line connecting parent to child
      DrawLine(x, y + node_radius, child_x, child_y - node_radius, GRAY);
      // Draw the character on the line
      char char_text[2] = {(char)('a' + i), '\0'};
      DrawText(char_text, (x + child_x) / 2 - 5, (y + child_y) / 2 - 8, 20,
               MAROON);

      // Recurse to draw the child's subtree
      drawTrieRecursive(node->children[i], child_x, child_y);

      current_child_x_offset += child_subtree_width + (horizontal_spacing / 2);
    }
  }
}

/**
 * @brief Main drawing function that sets up the canvas and calls the recursive
 * drawer.
 * @param trieRoot The root of the trie to draw.
 */
void drawTrie(TrieNode *trieRoot) {
  int start_x = GetScreenWidth() / 2;
  int start_y = 80;

  BeginDrawing();
  ClearBackground((Color) {45, 45, 45});

  if (trieRoot == NULL) {
    DrawText("Trie is empty. Insert a word to begin.",
             GetScreenWidth() / 2 -
                 MeasureText("Trie is empty. Insert a word to begin.", 20) / 2,
             GetScreenHeight() / 2 - 10, 20, DARKGRAY);
  } else {
    // We call the recursive function to draw the trie
    drawTrieRecursive(trieRoot, start_x, start_y);
  }
}

// --- Main Application ---

int main(void) {
  const int screenWidth = 1280;
  const int screenHeight = 720;
  InitWindow(screenWidth, screenHeight, "Trie Visualizer");
  SetTargetFPS(60);

  // --- GUI State ---
  char textBoxText[32] = {0};
  bool textBoxEditMode = false;
  char statusText[64] = "Enter a lowercase word.";
  Color statusColor = DARKGRAY;

  // --- Main Loop ---
  while (!WindowShouldClose()) {

    // --- Input Handling ---
    // Convert textbox input to lowercase automatically
    for (int i = 0; textBoxText[i]; i++) {
      textBoxText[i] = tolower(textBoxText[i]);
    }

    Rectangle textBox = {screenWidth / 2.0f - 260, 20, 200, 30};

    // Handle Insert Button
    if (GuiButton((Rectangle){screenWidth / 2.0f - 50, 20, 80, 30}, "Insert")) {
      if (strlen(textBoxText) > 0) {
        insertWord(textBoxText);
        sprintf(statusText, "Inserted: '%s'", textBoxText);
        statusColor = DARKGREEN;
        textBoxText[0] = '\0';
      } else {
        sprintf(statusText, "Cannot insert an empty word.");
        statusColor = RED;
      }
    }

    // Handle Search Button
    if (GuiButton((Rectangle){screenWidth / 2.0f + 40, 20, 80, 30}, "Search")) {
      if (strlen(textBoxText) > 0) {
        if (searchWord(textBoxText)) {
          sprintf(statusText, "Found: '%s'", textBoxText);
          statusColor = BLUE;
        } else {
          sprintf(statusText, "Not Found: '%s'", textBoxText);
          statusColor = MAROON;
        }
      } else {
        sprintf(statusText, "Enter a word to search.");
        statusColor = RED;
      }
    }

    // Handle Delete Button
    if (GuiButton((Rectangle){screenWidth / 2.0f + 130, 20, 80, 30},
                  "Delete")) {
      if (strlen(textBoxText) > 0) {
        if (deleteWord(textBoxText)) {
          sprintf(statusText, "Deleted: '%s'", textBoxText);
          statusColor = DARKPURPLE;
        } else {
          sprintf(statusText, "'%s' was not in the trie to delete.",
                  textBoxText);
          statusColor = RED;
        }
        textBoxText[0] = '\0';
      } else {
        sprintf(statusText, "Cannot delete an empty word.");
        statusColor = RED;
      }
    }

    // Handle Reset Button
    if (GuiButton((Rectangle){screenWidth / 2.0f + 220, 20, 80, 30}, "Reset")) {
      freeTrie(root);
      root = NULL;
      sprintf(statusText, "Trie has been reset.");
      statusColor = DARKGRAY;
      textBoxText[0] = '\0';
    }

    // --- Drawing ---
    drawTrie(root);

    // Draw GUI controls and text on top
    if (GuiTextBox(textBox, textBoxText, 32, textBoxEditMode)) {
      textBoxEditMode = !textBoxEditMode;
    }

    DrawText("Trie (Prefix Tree)", 10, 10, 20, DARKGRAY);
    DrawText(statusText, 10, 40, 20, statusColor);
    DrawFPS(10, screenHeight - 20);

    EndDrawing();
  }

  // --- De-Initialization ---
  freeTrie(root);
  CloseWindow();
  return 0;
}
