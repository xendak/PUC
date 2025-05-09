#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
  int str;
  char name[50];
} Athlete;

bool compare(Athlete a, Athlete b) {
  if (a.str == b.str) return strcmp(b.name, a.name);
  else return a.str >= b.str;
}

void swap(Athlete *a, int src, int dst) {
  Athlete p = a[dst];
  a[dst] = a[src];
  a[src] = p;
}

void selection_sort(Athlete *a, size_t len) {
  for(int i = len-1; i > 0; i--) {
    int min = i;
    for(int j = 0; j < i; j++) {
      if (compare(a[min], a[j])) {
        min = j;
      }
    }
    swap(a, i, min);
  }
}

int main() {
  int n;
  if (scanf("%d", &n) != 1) exit(EXIT_FAILURE);
  
  Athlete a[n];

  for (int i = 0 ; i < n; i++) {
    if (scanf("%50s %d", a[i].name, &a[i].str) != 2) exit(EXIT_FAILURE);
  }
  selection_sort(a, n);
  for (int i = 0 ; i < n; i++) {
    printf("%s %d\n", a[i].name, a[i].str);
  }
  return 0;
}
