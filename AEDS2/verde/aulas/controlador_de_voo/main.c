#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  char *name;
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
  if(scanf("%s", line) == 1) return 1;

  while (line[0] != '0') {
    if(is_direction(line)) {
      dir = parse_line(line);     
    } else {
      enqueue(&planes[dir], line);
    }
    
    if(scanf("%s", line) == 1) return 1;
  }
  print_queue(planes);

  return 0;
}
Nodeptr create_node(char *val) {
  Nodeptr res = (Nodeptr)malloc(sizeof(Node));
  res->name = val;
  res->next = NULL;
  return res;
}
char *delete_node(Nodeptr n);

void init_queue(Queue *q) {
  Nodeptr head = create_node(NULL);
  q->head = head;
  q->tail = head;
  q->len = 0;
}
void enqueue(Queue *q, char *val) {
  Nodeptr tmp = create_node(val);  
  Nodeptr head = q->head;
  Nodeptr tail = q->tail;
  tmp->next =;

  head->next = tmp;
  
  
}

char *dequeue(Queue *q);
void deinit_queue(Queue *q);


void print_queue(Queue *q);
bool is_direction(char *line);
Direction parse_line(char *val);

