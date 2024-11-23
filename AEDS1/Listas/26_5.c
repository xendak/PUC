#include <stdio.h>
#include <stdlib.h>

#define MAX_COL 2
#define MAX_ROW 2

void print_matrix(float m[MAX_ROW][MAX_COL]);
void copy_matrix(float src[MAX_ROW][MAX_COL], float dst[MAX_ROW][MAX_COL]);



int main(int argc, char** argv) {
    float (*m1)[MAX_COL] = malloc(sizeof(*m1) * MAX_ROW);
    float (*m2)[MAX_COL] = malloc(sizeof(*m2) * MAX_ROW);
    /*float m2[MAX_COL][MAX_ROW];*/

    if (m1 == NULL) return -1;
    if (m2 == NULL) return -1;

    for (int i = 0; i < MAX_COL * MAX_ROW; i++)
        for (int j = 0; j < MAX_ROW * MAX_ROW; j++)
            scanf("%f", &m1[i][j]);



    print_matrix(m1);
    print_matrix(m2);
    copy_matrix(m1, m2);
    print_matrix(m2);
    
    return 0;
}

void copy_matrix(float src[MAX_ROW][MAX_COL], float dst[MAX_ROW][MAX_COL]) {
    for(int i = 0; i < MAX_ROW * MAX_COL; i++)
        dst[i] = &src[i];
}

void print_matrix(float m[MAX_ROW][MAX_COL]) {
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; i < MAX_COL; j++)
            printf("%.2f\t", m[i][j]);
        printf("\n");
    }
}
