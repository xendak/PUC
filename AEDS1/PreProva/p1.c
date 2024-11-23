#include <stdio.h>

int abs(int n) {
    return n > 0 ? n : -n;
}

void recursive(int linhas, int current, int los) {
    if (current > linhas) return; // Base

    int spaces;
    if (linhas % 2 == 0) {
        spaces = (linhas / 2) - (current + 1) / 2;
    } else {
        spaces = abs((linhas / 2) - current);
    }

    for (int i = 0; i < spaces; i++) {
        printf("  ");
    }

    for (int i = 0; i < los; i++) {
        printf("* ");
    }
    printf("\n");

    if (current < linhas / 2) {
        recursive(linhas, current + 1, los + 2);
    } else if (current >= linhas / 2) {
        recursive(linhas, current + 1, los - 2);
    }
}

int main() {
    int n;

    printf("Digite o valor de N: ");
    scanf("%d", &n);
    recursive(n, 0, 1);

    return 0;
}

