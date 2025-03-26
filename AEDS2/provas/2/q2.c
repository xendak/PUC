#include <stdio.h>

#define POINT_SIZE 10

typedef struct {
  char *name;
  int points[POINT_SIZE];
  int score;
  int same_monster_bonus;
} player;

typedef struct {
  player p1;
  player p2;
  int rounds;
  char result;
} game;

game new_game(int rounds, char *name1, char *name2) {
  game res;
  player p1;
  player p2;
  res.rounds = rounds;

  p1.name = name1;
  p1.score = 0;
  p1.same_monster_bonus = -1;

  p2.name = name2;
  p2.score = 0;
  p2.same_monster_bonus = -1;

  for (int i = 0; i < POINT_SIZE; i++) {
    p1.points[i] = 0;
    p2.points[i] = 0;
  }

  res.p1 = p1;
  res.p2 = p2;

  res.result = 'T';

  return res;
}

void compute_game(game *g) {
  player *p1 = &g->p1;
  player *p2 = &g->p2;

  if (p1->same_monster_bonus < p2->same_monster_bonus)
    p1->score += 30;
  else if (p2->same_monster_bonus < p1->same_monster_bonus)
    p2->score += 30;

  if (p1->score > p2->score)
    g->result = p1->name[0];
  else if (p1->score < p2->score)
    g->result = p2->name[0];
}

void compute_player(player *p, int rounds) {
  int pt;
  for (int i = 0; i < rounds; i++) {
    if(scanf("%d", &pt) != 1) perror("Failed to scan a number in a line.\n");

    p->points[pt % 10]++;
    p->score += pt;

    if (p->points[pt % 10] > 2 && p->same_monster_bonus == -1)
      p->same_monster_bonus = i;
  }
}

int main() {
  int rounds;
  do {
    if (scanf("%d", &rounds) != 1)
      return -1; // failed to read value so force exit

    game match = new_game(rounds, "Mark", "Leti");
    int pt;

    compute_player(&match.p1, rounds);
    compute_player(&match.p2, rounds);

    compute_game(&match);
    if (match.rounds > 0)
      printf("%c\n", match.result);
      // printf("%c\t p1: %d\tp2: %d", match.result, match.p1.score, match.p2.score);

    // we dont need to free anything since everything is static allocated.
  } while (rounds != 0);
  return 0;
}
