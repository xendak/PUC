#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 1. 2 num naturais (beach_length, Sorveteiros)
// S.. (U, V) onde U < V e ambos dentro de 0..beach_length
// 0 0 = fim.

// Saida: Teste N
// print node \n

typedef struct {
  int start;
  int end;
} Path;

typedef struct Node {
  Path p;
  struct Node *next;
  struct Node *prev;
} Node, *pNode;

typedef struct {
  pNode head;
  pNode tail;
} List;

void init_list(List *l) {
  pNode tmp = (pNode)malloc(sizeof(Node));
  if (!tmp)
    exit(EXIT_FAILURE);

  tmp->prev = NULL;
  tmp->next = NULL;
  Path dummy = { .start = -1, .end = -1 };
  tmp->p = dummy;

  l->head = tmp;
  l->tail = l->head;
}

inline bool is_empty(List *l) { return l->head->next == NULL; }

inline bool compare_path(Path a, Path b) {
  return (b.start > a.start);
}

void swap_path(pNode src, pNode dst) {
  Path tmp = src->p;
  src->p = dst->p;
  dst->p = tmp;
}

void list_add(List *l, Path data) {
  pNode tmp = (pNode)malloc(sizeof(Node));
  if (!tmp)
    exit(EXIT_FAILURE);

  pNode curr = l->head->next;

  tmp->p = data;
  tmp->next = NULL;
  tmp->prev = l->tail;
  
  l->tail->next = tmp;
  l->tail = tmp;
  
  curr = l->head->next->next;
  pNode prev = l->head->next;
  while (curr) {
    if (compare_path(curr->p, prev->p)) {
      swap_path(curr, prev);
    }
    prev = curr;
    curr = curr->next;
  }

}

bool list_remove(List *l) {
  if (is_empty(l))
    return false;

  pNode to_remove = l->head;
  l->head = l->head->next;
  free(to_remove);

  if (l->head->next == NULL) {
    l->head = l->tail;
  }

  return true;
}

void deinit_list(List *l) {
  while (list_remove(l))
    ;
  ;

  free(l->head);
}

void print_queue(List *l) {
  pNode curr = l->head->next;
  while (curr != NULL) {
    // printf("[%d, %d]\t", curr->p.start, curr->p.end);
    printf("%d %d\n", curr->p.start, curr->p.end);
    curr = curr->next;
  }
}

inline bool is_connected(Path a, Path b) {
  return b.start >= a.start && b.start <= a.end;
}

Path unify_path(Path a, Path b) {
  Path res = {a.start, a.end};
  if (a.end < b.end)
    res.end = b.end;

  return res;
}


void in_place_coalesce_paths(List *l) {
  if (is_empty(l) || l->head->next->next == NULL) {
    return;
  }
  
  // using the "previous" as the path comparison
  // and merge option.
  pNode prev = l->head->next;
  pNode current = l->head->next->next;
  
  while (current != NULL) {
    pNode next = current->next;
    
    // if they are connected, we should merge.
    if (is_connected(prev->p, current->p)) {

      prev->p = unify_path(prev->p, current->p);
      
      // Remove the current node as it's now merged
      if (current == l->tail) {
        l->tail = prev;
      }
      
      // if we have a valid "foward", then we must set the prev pointer. (because tihs is a doubly linked list)
      // otherwise this for is useless.
      if (current->next) {
        current->next->prev = prev;
      }
      
      // actually move forward
      prev->next = current->next;
      
      // since it was connected and we merged, means we dont need the node anymore
      free(current);
    } else {
      // if they arent connected, it means we can just advance foward since
      // non merged paths dont need to be deleted.
      prev = current;
    }
    
    current = next;
  }
}

// i did like this first, but was a bit annoying since we created a new list
// but also modified the old one.. so i tried making a "in_place".
List coalesce_paths(List *l) {
  List result;
  init_list(&result);
  
  if (is_empty(l)) {
    return result;
  }
  
  pNode curr = l->head->next;
  // our path is always our previous node.
  Path prev = curr->p;
  
  curr = curr->next;
  
  while (curr != NULL) {
    if (is_connected(prev, curr->p)) {
      // Merge the paths
      prev = unify_path(prev, curr->p);
    } else {
      // not connected, means the "last" stopped and needs to be added now.
      list_add(&result, prev);
      prev = curr->p;
    } 

    curr = curr->next;
  }
  
  // we need to make sure we add the last one.
  list_add(&result, prev);
  
  return result;
}

int main() {
  int beach_length, salesman_count;
  int count = 1;
  List *l = (List *)malloc(sizeof(List));

  if (scanf("%d %d", &beach_length, &salesman_count) != 2)
    exit(EXIT_FAILURE);

  while (beach_length != 0 && salesman_count != 0) {
    init_list(l);
    for (int i = 0; i < salesman_count; i++) {
      Path tmp = {0, 0};
      if (scanf("%d %d", &tmp.start, &tmp.end) != 2)
        exit(EXIT_FAILURE);

      // printf("Adding: [%d, %d]\n", tmp.start, tmp.end);
      list_add(l, tmp);
    }
    in_place_coalesce_paths(l);
    printf("Teste %d\n", count);
    print_queue(l);
    deinit_list(l);
    count++;
    if (scanf("%d %d", &beach_length, &salesman_count) != 2)
      exit(EXIT_FAILURE);
  }

  free(l);
  return 0;
}
