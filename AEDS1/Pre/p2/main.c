#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW 5
#define MAX_COL MAX_ROW

int check_dia2(float**, float);

int main(int argc, char** argv) {
    float** mat = (float**) malloc(MAX_ROW * sizeof(float*));
    for (int i = 0; i < MAX_ROW; i++)
        mat[i] = (float *) malloc(MAX_COL * sizeof(float));
    for (int i = 0; i < MAX_ROW; i++){
        for (int j = 0; j < MAX_COL; j++) {
            mat[i][j] = (float) i + j;
            printf("%2.f\t", mat[i][j]);
        }
        printf("\n");
    }

    printf("\nval = %f, qt = %d", 5.0f, check_dia2(mat, 5));
    return 0;
}

int check_dia2(float** mat, float val) {
    int qt = 0;

    for(int i = MAX_ROW - 1; i >= 0; i--) {
        for (int j = MAX_ROW - i; j < MAX_ROW; j++)
            if (mat[i][j] == val) { qt++; }
    }
    return qt;
}
