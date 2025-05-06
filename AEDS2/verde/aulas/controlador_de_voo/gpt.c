#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  WEST = 0,
  SOUTH = 1,
  NORTH = 2,
  EAST = 3,
} Direction;

typedef struct Node {
  struct Node *next;
  char *name;
} Node;

typedef struct {
  Node *head;
  Node *tail;
  size_t size;
} Queue;

typedef enum { false, true } bool;

Node* create_node(char* str);
void init_queue(Queue *q);
void push(Queue *q, char *name);
void free_queue(Queue *q);

bool is_direction(char *str);
Direction get_direction(char *str);
void print(Queue *planes);
void print_queue(Queue *q);

int main() {
  char line[10];

  if (scanf("%s", line) != 1)
    return 1;
  Queue planes[4];
  for (int i = 0; i < 4; i++)
    init_queue(&planes[i]);

  Direction direction = WEST;

  do {
    if (!is_direction(line)) {
      push(&planes[direction], line);
    } else {
      direction = get_direction(line);
    }
    if (scanf("%s", line) != 1)
      return 1;
  } while (line[0] != '0');

  printf("Printing planes in order\n");
  print(planes);

  for (int i = 0; i < 4; i++) {
    free_queue(&planes[i]);
  }

  return 0;
}

bool is_direction(char *str) { return str[0] == '-'; }

Direction get_direction(char *str) {
  int res = atoi(&str[1]);
  return res - 1;
}

void init_queue(Queue *q) {
  q->head = NULL;
  q->tail = NULL;
  q->size = 0;
}

Node* create_node(char* str) {
  Node* new_node = (Node*) malloc(sizeof(Node));
  new_node->name = strdup(str);
  new_node->next = NULL;
  return new_node;
}

void push(Queue *q, char *str) {
  Node *new_node = create_node(str);
  if (q->head == NULL) {
    q->head = q->tail = new_node;
  } else {
    q->tail->next = new_node;
    q->tail = new_node;
  }
  q->size++;
}

void print(Queue *planes) {
  // Print WEST planes
  Node *west = planes[WEST].head;
  while (west != NULL) {
    printf("%s ", west->name);
    west = west->next;
  }

  // Interleave NORTH and SOUTH, starting with NORTH
  Node *north = planes[NORTH].head;
  Node *south = planes[SOUTH].head;
  bool take_north = true;
  while (north != NULL || south != NULL) {
    if (take_north) {
      if (north != NULL) {
        printf("%s ", north->name);
        north = north->next;
      }
      take_north = false;
    } else {
      if (south != NULL) {
        printf("%s ", south->name);
        south = south->next;
      }
      take_north = true;
    }
  }

  // Print EAST planes
  Node *east = planes[EAST].head;
  while (east != NULL) {
    printf("%s ", east->name);
    east = east->next;
  }
  printf("\n");
}

void free_queue(Queue *q) {
  Node *current = q->head;
  while (current != NULL) {
    Node *temp = current;
    current = current->next;
    free(temp->name);
    free(temp);
  }
  q->head = q->tail = NULL;
  q->size = 0;
}
