#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// West priority.
// North/South alternates between 1 and 1
// East always last

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
  size_t size;

} Stack;

typedef enum { false, true } bool;

Node* create_node(char* str);
void init_stack(Stack *s);
void push(Stack *s, char *name);

bool is_direction(char *str);
Direction get_direction(char *str);
void print(Stack *s);
void print_stack(Stack *s);

int main() {
  char line[10];

  if (scanf("%s", line) != 1)
    return 1;
  Stack planes[4];
  for (int i = 0; i < 4; i++)
    init_stack(&planes[i]);

  Direction direction = WEST;
  printf("Starting, Dir = %d\n", direction);

  do {
    if (!is_direction(line)) {
      printf("adding a plane = %s\n", line);
      push(&planes[direction], line);
    } else {
      printf("changing direction = ");
      direction = get_direction(line);
    }
    if (scanf("%s", line) != 1)
      return 1;
  } while (line[0] != '0');

  printf("Printing planes in order\n");
  print(planes);
  return 0;
}

bool is_direction(char *str) { return str[0] == '-'; }

Direction get_direction(char *str) {
  int res = atoi(&str[1]);
  printf("%d\n", res - 1);
  return res - 1;
}

void init_stack(Stack *s) {
  s->size = 0;
  s->head = NULL;
}

Node* create_node(char* str) {
  Node* new_node = (Node*) malloc(sizeof(Node));
  new_node->name = strdup(str);
  new_node->next = NULL;
  printf("added: %s", new_node->name);
  return new_node;
}

void push(Stack *s, char *str) {
  s->size++;
  Node *tmp = create_node(str);
  tmp->next = s->head;
  s->head = tmp;
  print_stack(s);
}

void print_stack(Stack *s) {
  Node* h = s->head;
    printf("[");
  while(s) {
    printf("%s", h->name);
    h = h->next;
  }
    printf("]");
}


void print(Stack *s) {
  printf("sizes = %zu", s[WEST].size);
  Node *west = s[WEST].head;
  Node *south = s[SOUTH].head;
  Node *north = s[NORTH].head;
  Node *east = s[EAST].head;

  // WEST
  while (west) {
    printf("%s ", west->name);
    west = west->next;
  }

  size_t ns = s[NORTH].size > s[SOUTH].size ? s[NORTH].size : s[SOUTH].size;
  bool n_s = true;
  Node *curr = NULL;

  while (ns) {
    if (n_s) {
      curr = north;
      north = north->next;
    } else {
      curr = south;
      south = south->next;
    }
    printf("%s ", curr->name);
    n_s = !n_s;
  }

  if (s[SOUTH].size <= s[NORTH].size) {
    while (north) {
      printf("%s ", north->name);
      north = north->next;
    }
  } else {
    while (south) {
      printf("%s ", south->name);
      south = south->next;
    }
  }

  while (east) {
    printf("%s ", east->name);
    east = east->next;
  }
  printf("\n");
}
