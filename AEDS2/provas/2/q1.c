#include <stdio.h>

typedef enum {
  RABBIT,
  RAT,
  FROG
} species;

typedef struct {
  species specie;
  int count;
} animal;

typedef struct {
  animal rabbit;
  animal rat;
  animal frog;
  int total;
} research;

void init_research(research* r) {
  // not really used here, but is a good idea in general
  r->rabbit.specie = RABBIT;
  r->rat.specie    = RAT;
  r->frog.specie   = FROG;

  r->rabbit.count = 0;
  r->rat.count = 0;
  r->frog.count = 0;
  r->total = 0;
}

float get_percentage(animal a, int total) {
  return a.count * 100 / (float) total;
}

int main () {

  int r_count;
  if (scanf("%d", &r_count) != 1) return -1;

  research re;
  init_research(&re);
  
  for (int i = 0; i < r_count; i++) {
    int num;
    char specie;
    if(scanf("%d %c", &num, &specie) != 2) perror("failed to read line\n");

    switch(specie) {
      case 'C':
        re.rabbit.count += num;
        break;
      case 'R':
        re.rat.count += num;
        break;
      case 'S':
        re.frog.count += num;
        break;
      default:  
        perror("shouldnt be reached.");
        break;
    }

    re.total += num;
  }

  printf("Total: %d cobaias\n", re.total);
  printf("Total de coelhos: %d\n", re.rabbit.count);
  printf("Total de ratos: %d\n", re.rat.count);
  printf("Total de sapos: %d\n", re.frog.count);
  printf("Percentual de coelhos: %.2f %%\n", get_percentage(re.rabbit, re.total));
  printf("Percentual de ratos: %.2f %%\n", get_percentage(re.rat, re.total));
  printf("Percentual de sapos: %.2f %%\n", get_percentage(re.frog, re.total));
  
  return 0;
}
