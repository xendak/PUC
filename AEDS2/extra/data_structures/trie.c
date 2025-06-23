#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the size of the alphabet (e.g., 26 for 'a'-'z')
#define ALPHABET_SIZE 26

// Structure for a Trie node
typedef struct TrieNode {
  struct TrieNode *children[ALPHABET_SIZE]; // Pointers to child nodes
  bool word_end; // True if the node represents the end of a word
} TrieNode;

/**
 * @brief Creates a new Trie node and initializes it.
 * @return A pointer to the newly created TrieNode.
 */
TrieNode *create_node() {
  // Allocate memory for a new Trie node
  TrieNode *pNode = (TrieNode *)malloc(sizeof(TrieNode));

  if (pNode) {
    // Mark this node as not being the end of any word initially
    pNode->word_end = false;

    // Initialize all children pointers to NULL
    for (int i = 0; i < ALPHABET_SIZE; i++) {
      pNode->children[i] = NULL;
    }
  }
  return pNode;
}

/**
 * @brief Inserts a key (word) into the Trie.
 * @param root The root node of the Trie.
 * @param key The word to be inserted.
 */
void insert(TrieNode *root, const char *key) {
  TrieNode *pCrawl = root;
  int length = strlen(key);

  // Traverse the Trie for each character in the key
  for (int level = 0; level < length; level++) {
    // Calculate the index for the character (assuming lowercase 'a'-'z')
    // We subtract 'a' to map 'a'->0, 'b'->1, etc.
    int index = key[level] - 'a';

    // If the path for this character doesn't exist, create it
    if (!pCrawl->children[index]) {
      pCrawl->children[index] = create_node();
    }

    // Move to the next node in the path
    pCrawl = pCrawl->children[index];
  }

  // After the last character, mark this node as the end of a word
  pCrawl->word_end = true;
}

/**
 * @brief Searches for a key (word) in the Trie.
 * @param root The root node of the Trie.
 * @param key The word to search for.
 * @return `true` if the key is present in the Trie, `false` otherwise.
 */
bool search(TrieNode *root, const char *key) {
  TrieNode *pCrawl = root;
  int length = strlen(key);

  // Traverse the Trie for each character in the key
  for (int level = 0; level < length; level++) {
    int index = key[level] - 'a';

    // If at any point the path breaks (a child is NULL), the key doesn't exist
    if (!pCrawl->children[index]) {
      return false;
    }

    // Move to the next node
    pCrawl = pCrawl->children[index];
  }

  // The key is found if we reached the end of the key's path (pCrawl is not
  // NULL) AND the final node is marked as the end of a word.
  return (pCrawl != NULL && pCrawl->word_end);
}

/**
 * @brief Checks if any word in the Trie starts with the given prefix.
 * @param root The root of the Trie.
 * @param prefix The prefix to check for.
 * @return `true` if there is a word with the given prefix, `false` otherwise.
 */
bool starts_with(TrieNode *root, const char *prefix) {
  TrieNode *pCrawl = root;
  int length = strlen(prefix);

  // Traverse the Trie for each character in the prefix
  for (int level = 0; level < length; level++) {
    int index = prefix[level] - 'a';

    // If the path for this prefix does not exist, return false
    if (!pCrawl->children[index]) {
      return false;
    }

    // Move to the next node
    pCrawl = pCrawl->children[index];
  }

  // If we have successfully traversed the entire prefix, it means
  // there is at least one word that starts with it.
  return (pCrawl != NULL);
}

// Function to deallocate memory used by the Trie
void free_trie(TrieNode *root) {
  if (!root) {
    return;
  }
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    free_trie(root->children[i]);
  }
  free(root);
}

// Main function to demonstrate Trie operations
int main() {
  // A set of words to be inserted into the Trie
  char keys[][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
  int n = sizeof(keys) / sizeof(keys[0]);

  // Create the root of the Trie
  TrieNode *root = create_node();

  // Insert all keys into the Trie
  printf("Inserting the following words:\n");
  for (int i = 0; i < n; i++) {
    printf("- %s\n", keys[i]);
    insert(root, keys[i]);
  }
  printf("\n");

  // --- Search for some words ---
  printf("--- Search Results ---\n");
  printf("Search for 'the': %s\n", search(root, "the") ? "Found" : "Not Found");
  printf("Search for 'these': %s\n",
         search(root, "these") ? "Found" : "Not Found");
  printf("Search for 'their': %s\n",
         search(root, "their") ? "Found" : "Not Found");
  printf("Search for 'thaw': %s\n",
         search(root, "thaw") ? "Found" : "Not Found");
  printf("\n");

  // --- Check for prefixes ---
  printf("--- Prefix Checking ---\n");
  printf("Prefix 'th': %s\n",
         starts_with(root, "th") ? "Exists" : "Does Not Exist");
  printf("Prefix 'an': %s\n",
         starts_with(root, "an") ? "Exists" : "Does Not Exist");
  printf("Prefix 'cat': %s\n",
         starts_with(root, "cat") ? "Exists" : "Does Not Exist");
  printf("\n");

  // --- Edge case: Searching for a prefix that is not a full word ---
  // "the" is a word, but "the" is also a prefix for "there" and "their".
  // "an" is a prefix for "answer" and "any", but it's not a word itself in our
  // set.
  printf("--- Edge Case: Prefix vs. Word ---\n");
  printf("Search for 'an': %s\n", search(root, "an") ? "Found" : "Not Found");
  printf("\n");

  // Free the memory allocated for the Trie
  free_trie(root);

  return 0;
}
