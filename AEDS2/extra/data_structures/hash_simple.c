#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the size of our simple hash table array.
// A prime number is generally a good choice.
#define TABLE_SIZE 23

// The structure to hold a username and password pair.
typedef struct {
  char *username;
  char *password;
} User;

// The hash table is a simple array of pointers to UserEntry.
User *hash_table[TABLE_SIZE];

/**
 * @brief Initializes the hash table by setting all entries to NULL.
 */
void init_hash_table() {
  for (int i = 0; i < TABLE_SIZE; i++) {
    hash_table[i] = NULL;
  }
}

/**
 * @brief Simple hash function to convert a string (username) into an array
 * index.
 * @param username The string key to hash.
 * @return An integer representing the index in the hash table array.
 */
int hash_function(const char *username) {
  unsigned long hash = 0;
  int c;
  while ((c = *username++)) {
    // A simple hash calculation
    hash = hash * 31 + c;
  }
  return hash % TABLE_SIZE;
}

/**
 * @brief Inserts a new user into the hash table.
 * Uses linear probing to handle collisions.
 * @param username The username to insert.
 * @param password The associated password.
 */
void insert_user(const char *username, const char *password) {
  // Create the new entry
  User *new_entry = (User *)malloc(sizeof(User));
  new_entry->username = strdup(username);
  new_entry->password = strdup(password);

  // Calculate the initial hash index
  int index = hash_function(username);

  // --- Linear Probing for Collision ---
  // Find the next available empty slot
  while (hash_table[index] != NULL) {
    // Simple check to prevent inserting the same user twice
    if (strcmp(hash_table[index]->username, username) == 0) {
      printf("Warning: User '%s' already exists. Cannot insert.\n", username);
      free(new_entry->username);
      free(new_entry->password);
      free(new_entry);
      return;
    }
    index = (index + 1) %
            TABLE_SIZE; // Move to the next slot (and wrap around if needed)
  }

  // Place the new entry in the found empty slot
  hash_table[index] = new_entry;
  printf("Inserted user '%s' at index %d.\n", username, index);
}

/**
 * @brief Looks up a user and verifies their password.
 * @param username The username to look for.
 * @param password The password to verify.
 * @return `true` if username is found and password matches, `false` otherwise.
 */
bool login(const char *username, const char *password) {
  // Calculate the starting index
  int index = hash_function(username);

  // --- Linear Probing for Lookup ---
  // Search for the username starting from its hash index
  int attempts = 0;
  while (hash_table[index] != NULL && attempts < TABLE_SIZE) {
    // Check if we found the correct username
    if (strcmp(hash_table[index]->username, username) == 0) {
      // Username found, now check the password
      if (strcmp(hash_table[index]->password, password) == 0) {
        return true; // Password matches!
      } else {
        return false; // Password does not match
      }
    }
    // If not the right user, move to the next slot
    index = (index + 1) % TABLE_SIZE;
    attempts++;
  }

  // If we hit a NULL slot or searched the whole table, the user does not exist
  return false;
}

/**
 * @brief Frees all memory allocated for the hash table entries.
 */
void free_table() {
  for (int i = 0; i < TABLE_SIZE; i++) {
    if (hash_table[i] != NULL) {
      free(hash_table[i]->username);
      free(hash_table[i]->password);
      free(hash_table[i]);
    }
  }
}

// Main function to demonstrate the login system
int main() {
  // Initialize the hash table
  init_hash_table();

  // Add some users to our system
  printf("--- Registering Users ---\n");
  insert_user("alice", "pass123");
  insert_user("bob", "bobcat99");
  insert_user("charlie", "securepwd");
  // 'ecilA' might collide with 'alice' depending on the hash function
  // This helps demonstrate linear probing.
  insert_user("ecila", "different_user");
  printf("\n");

  // --- Login Attempts ---
  printf("--- Login System ---\n");
  // Successful login
  printf("Attempting login for 'alice' with password 'pass123'... %s\n",
         login("alice", "pass123") ? "SUCCESS" : "FAILED");

  // Failed login (wrong password)
  printf("Attempting login for 'bob' with password 'wrongpass'... %s\n",
         login("bob", "wrongpass") ? "SUCCESS" : "FAILED");

  // Successful login for a user that likely had a collision
  printf("Attempting login for 'ecila' with password 'different_user'... %s\n",
         login("ecila", "different_user") ? "SUCCESS" : "FAILED");

  // Failed login (user does not exist)
  printf("Attempting login for 'david' with password 'anything'... %s\n",
         login("david", "anything") ? "SUCCESS" : "FAILED");
  printf("\n");

  // Free all allocated memory before exiting
  free_table();

  return 0;
}
