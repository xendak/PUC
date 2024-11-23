
#include <stdio.h>
#include <stdlib.h>

#define VALOR 5

void iterative(int n);
void recursive(int n, int spaces, int row, int stars);

int main(int argc, char** argv) {
    iterative(strtol(argv[1], NULL, 10));
    int input = argc > 1 ? strtol(argv[1], NULL, 10) : VALOR; 
    recursive(input, input / 2, 0, 1);
    return 0;
}

void recursive(int n, int spaces, int row, int stars) {
    if (n <= 0 || row >= n) { return; }
    
    for (int s = 0; s < spaces; s++)
        printf("  ");
    for (int s = 0; s < stars; s++)
        printf("* ");

    printf("\n");

    if (row < n / 2) {
        if ((n % 2 == 0) && (row == (n / 2) - 1))  // if n is even and we're 1 row before the "middle", skip adding stars
            recursive(n, spaces, row + 1, stars);
        else
            recursive(n, spaces - 1, row + 1, stars + 2); // add 2 stars as normal
    }
    else
        recursive(n, spaces + 1, row + 1, stars - 2);
}

void iterative(int n) {
    int spaces = n / 2; 
    int row = 0;
    int stars = 1;

    printf("\n");
    for (int i = 0; i < n / 2; i++) {
        for (int s = 0; s < spaces; s++)
            printf("  ");
        for (int s = 0; s < stars; s++)
            printf("* ");
        printf("\n");
        row++;
        stars += 2; 
        spaces--;
    }

    if (n % 2 > 0) {
        for (int i = 0; i < stars; i++)
            printf("* ");
        printf("\n");
    }

    spaces++;
    stars = 1 + (2 * (row - 1));
    for (int i = 0; i < n / 2 ; i++) {
        for (int s = 0; s < spaces; s++)
            printf("  ");
        for (int s = 0; s < stars; s++)
            printf("* ");
        printf("\n");
        row--;
        stars -= 2;
        spaces++;
    }
    printf("\n");

}
