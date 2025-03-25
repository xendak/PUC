#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_ROUNDS 10

void winner(int rodadas_m[], int rodadas_l[], int num_rodadas) {
    int points_m = 0;
    int points_l = 0;
    char winner;

    for(int i = 0; i < num_rodadas; i++) {
        points_m += rodadas_m[i];
        points_l += rodadas_l[i];
    } 

    if (points_m > points_l) {
        winner = 'M';
    } else if (points_l > points_m) {
        winner = 'L';
    } else {
        winner = 'T';
    }

    printf("%c\n", winner);
}

int main() {
    int num_rodadas;
    int rodadas_mark[MAX_ROUNDS];
    int rodadas_leti[MAX_ROUNDS];

    while(true) {
        scanf("%d",&num_rodadas);

        if(num_rodadas == 0) {
            break;
        } 

        for(int i = 0; i < num_rodadas; i++) {
            scanf("%d", &rodadas_mark[i]);
        }
        
        for(int i = 0; i < num_rodadas; i++) {
            scanf("%d", &rodadas_leti[i]);
        }

        winner(rodadas_mark, rodadas_leti, num_rodadas);
    }

    return 0;
}
