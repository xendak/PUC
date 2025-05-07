#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// only because its easier to print.
size_t len = 0;

typedef enum {
  false,
  true,
} bool;

typedef enum {
  WEST,
  SOUTH,
  NORTH,
  EAST,
  ENUM_COUNT,
} Direction;

typedef struct Node {
  struct Node *next;
  char name[6]; // A9999 + \0 max number.
} Node, *Nodeptr;

typedef struct {
  Nodeptr head;
  Nodeptr tail;
  size_t len;
} Queue;

void init_queue(Queue *q);
void enqueue(Queue *q, char *val);
char *dequeue(Queue *q);
void deinit_queue(Queue *q);

Nodeptr create_node(char *val);
char *delete_node(Nodeptr n);

void print_queue(Queue *q);
bool is_direction(char *line);
Direction parse_line(char *val);

int main() {
  char line[10];
  Direction dir = WEST;
  Queue planes[ENUM_COUNT];
  for (int i = 0; i < ENUM_COUNT; i++)
    init_queue(&planes[i]);

  // first read.
  if (scanf("%s", line) != 1)
    return 1;

  while (line[0] != '0') {
    if (is_direction(line)) {
      dir = parse_line(line);
    } else {
      enqueue(&planes[dir], line);
      len++;
    }

    if (scanf("%s", line) != 1)
      return 1;
  }
  print_queue(planes);

  for (int i = 0; i < ENUM_COUNT; i++)
    deinit_queue(&planes[i]);
  return 0;
}

bool is_direction(char *str) { return str[0] == '-'; }

Direction parse_line(char *str) {
  int res = atoi(&str[1]);
  return res - 1;
}

Nodeptr create_node(char *val) {
  Nodeptr res = (Nodeptr)malloc(sizeof(Node));
  if (!res)
    exit(EXIT_FAILURE);

  strcpy(res->name, val);
  res->next = NULL;

  return res;
}

char *delete_node(Nodeptr n) {
  if (!n) {
    return NULL;
  }

  char *res = n->name;
  free(n);
  return res;
}

void init_queue(Queue *q) {
  Nodeptr head = create_node("DUMMY");
  q->head = head;
  q->tail = head;
  q->len = 0;
}

void enqueue(Queue *q, char *val) {
  // head == tail
  Nodeptr tmp = create_node(val);
  q->tail->next = tmp;
  // head->next & tail -> next = tmp;
  q->tail = tmp;
  // now we keep head as is, and move tail.

  q->len++;
}

bool is_empty(Queue *q) {
  // we have a dummy node, so needs to check against head->next and not head.
  return (q->head->next == NULL);
}

char *dequeue(Queue *q) {
  if (is_empty(q)) {
    return NULL;
  }

  Nodeptr remove = q->head->next;
  static char removed[6];
  strcpy(removed, remove->name);

  q->head->next = remove->next;

  // if when we remove, we find that what we are removing is our tail,
  // tail == last "real node", then we're back at our dummy.
  // set head = tail.
  if (q->tail == remove) {
    q->tail = q->head;
  }

  free(remove);
  q->len--;
  return removed;
}

void deinit_queue(Queue *q) {
  while (dequeue(q))
    ;
  ;
  delete_node(q->head);
}

void print_queue(Queue *q) {
  while (len) {
    for (int i = 0; i < ENUM_COUNT; i++) {
      if (q[i].len) {
        printf("%s ", dequeue(&q[i]));
        len--;
      }
    }
  }
  printf("\n");
}
