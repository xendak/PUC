#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the initial size of the hash table array.
// A prime number is often a good choice to help with key distribution.
#define TABLE_SIZE 101

// Structure for a key-value pair node in the hash table.
// These will be the elements in the linked lists (chains).
typedef struct HashItem {
  char *key;
  char *value;
  struct HashItem *next; // Pointer to the next item in the chain
} HashItem;

// Structure for the Hash Table itself.
typedef struct HashTable {
  HashItem **items; // Array of pointers to Ht_item (the buckets)
  int size;        // The current size of the array
  int count;       // The number of items currently in the table
} HashTable;

/**
 * @brief Creates a new key-value pair item.
 * @param key The key for the item.
 * @param value The value associated with the key.
 * @return A pointer to the newly created Ht_item.
 */
HashItem *create_item(const char *key, const char *value) {
  // Allocate memory for the item
  HashItem *item = (HashItem *)malloc(sizeof(HashItem));
  if (!item) {
    perror("Failed to allocate memory for Ht_item");
    return NULL;
  }
  // Duplicate the key and value strings to store them
  item->key = strdup(key);
  item->value = strdup(value);
  item->next = NULL;
  return item;
}

/**
 * @brief The hash function (djb2 algorithm).
 * @param key The string key to hash.
 * @param table_size The size of the hash table's array.
 * @return An unsigned long integer representing the hash index.
 */
unsigned long hash_function(const char *key, int table_size) {
  unsigned long hash = 5381;
  int c;
  while ((c = *key++)) {
    // hash = hash * 33 + c
    hash = ((hash << 5) + hash) + c;
  }
  return hash % table_size;
}

/**
 * @brief Creates a new Hash Table.
 * @param size The desired size of the hash table's internal array.
 * @return A pointer to the newly created HashTable.
 */
HashTable *create_table(int size) {
  HashTable *table = (HashTable *)malloc(sizeof(HashTable));
  if (!table) {
    perror("Failed to allocate memory for HashTable");
    return NULL;
  }
  table->size = size;
  table->count = 0;
  // Allocate memory for the array of item pointers (the buckets)
  table->items = (HashItem **)calloc(table->size, sizeof(HashItem *));
  if (!table->items) {
    perror("Failed to allocate memory for HashTable items");
    free(table);
    return NULL;
  }
  return table;
}

/**
 * @brief Frees a single Ht_item (node).
 */
void free_item(HashItem *item) {
  free(item->key);
  free(item->value);
  free(item);
}

/**
 * @brief Frees the entire Hash Table and all its contents.
 */
void free_table(HashTable *table) {
  // Iterate through each bucket in the table
  for (int i = 0; i < table->size; i++) {
    HashItem *item = table->items[i];
    // If the bucket is not empty, free the entire chain
    while (item) {
      HashItem *next = item->next;
      free_item(item);
      item = next;
    }
  }
  // Free the array of buckets and the table structure itself
  free(table->items);
  free(table);
}

/**
 * @brief Inserts a key-value pair into the hash table.
 * Handles collisions by chaining. If key already exists, updates the value.
 * @param table The hash table.
 * @param key The key to insert.
 * @param value The value associated with the key.
 */
void ht_insert(HashTable *table, const char *key, const char *value) {
  // Create the item to insert
  HashItem *item = create_item(key, value);
  // Calculate the hash index for the key
  unsigned long index = hash_function(key, table->size);

  // Get the head of the chain at this index
  HashItem *current_item = table->items[index];

  // --- Collision Handling ---
  // If the bucket is empty, this item becomes the head of the new chain
  if (current_item == NULL) {
    table->items[index] = item;
    table->count++;
    return;
  }

  // If bucket is not empty, traverse the chain
  HashItem *prev = NULL;
  while (current_item != NULL) {
    // If the key already exists, update the value and free the new item
    if (strcmp(current_item->key, key) == 0) {
      free(current_item->value); // Free the old value
      current_item->value = strdup(value);
      free_item(item); // Free the newly created, now unused item
      return;
    }
    prev = current_item;
    current_item = current_item->next;
  }

  // If we reached the end of the chain, append the new item
  prev->next = item;
  table->count++;
}

/**
 * @brief Searches for a key in the hash table.
 * @param table The hash table.
 * @param key The key to search for.
 * @return The value as a string if found, otherwise NULL.
 */
char *ht_search(HashTable *table, const char *key) {
  // Calculate the hash index for the key
  unsigned long index = hash_function(key, table->size);
  // Get the head of the chain at this index
  HashItem *item = table->items[index];

  // Traverse the chain at the given index
  while (item != NULL) {
    if (strcmp(item->key, key) == 0) {
      // Key found, return the associated value
      return item->value;
    }
    item = item->next;
  }
  // If the loop finishes, the key was not found
  return NULL;
}

/**
 * @brief Deletes a key-value pair from the hash table.
 * @param table The hash table.
 * @param key The key of the item to delete.
 */
void ht_delete(HashTable *table, const char *key) {
  unsigned long index = hash_function(key, table->size);
  HashItem *item = table->items[index];
  HashItem *prev = NULL;

  // Traverse the chain to find the item to delete
  while (item != NULL) {
    if (strcmp(item->key, key) == 0) {
      // Found the item. Now we need to remove it from the list.
      if (prev == NULL) {
        // It's the head of the list
        table->items[index] = item->next;
      } else {
        // It's in the middle or at the end of the list
        prev->next = item->next;
      }
      free_item(item);
      table->count--;
      return;
    }
    prev = item;
    item = item->next;
  }
  // If we reach here, the item was not found.
}

/**
 * @brief Prints the contents of the hash table for debugging.
 */
void print_table(HashTable *table) {
  printf("\n--- Hash Table Contents ---\n");
  for (int i = 0; i < table->size; i++) {
    if (table->items[i]) {
      printf("Index %d: ", i);
      HashItem *item = table->items[i];
      while (item) {
        printf("(\"%s\", \"%s\") -> ", item->key, item->value);
        item = item->next;
      }
      printf("NULL\n");
    }
  }
  printf("---------------------------\n\n");
}

// Main function to demonstrate usage
int main() {
  // Create a new hash table
  HashTable *ht = create_table(TABLE_SIZE);

  // Insert some key-value pairs
  printf("Inserting items...\n");
  ht_insert(ht, "name", "John Doe");
  ht_insert(ht, "age", "30");
  ht_insert(ht, "city", "New York");
  ht_insert(ht, "occupation", "Software Engineer");
  // This will cause a collision with "age" if TABLE_SIZE is small,
  // demonstrating chaining.
  ht_insert(ht, "gea", "A different value");

  print_table(ht);

  // Search for items
  printf("Searching for key 'city': %s\n", ht_search(ht, "city"));
  printf("Searching for key 'country': %s\n",
         ht_search(ht, "country") ? ht_search(ht, "country") : "Not Found");
  printf("Searching for key 'gea': %s\n", ht_search(ht, "gea"));
  printf("\n");

  // Update an existing item
  printf("Updating key 'age' to '31'...\n");
  ht_insert(ht, "age", "31");
  printf("Searching for key 'age' after update: %s\n", ht_search(ht, "age"));
  print_table(ht);

  // Delete an item
  printf("Deleting key 'name'...\n");
  ht_delete(ht, "name");
  printf("Searching for key 'name' after deletion: %s\n",
         ht_search(ht, "name") ? ht_search(ht, "name") : "Not Found");
  print_table(ht);

  // Clean up
  free_table(ht);

  return 0;
}
