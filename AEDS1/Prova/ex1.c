#include <stdio.h>
#include <stdlib.h>

#define MAX 10

float get_minmax_matrix(float**);

int main() {
    float** m = (float**) malloc(sizeof(float*) * MAX);
    for (int i = 0; i < MAX; i++)
        m[i] = (float*) malloc(sizeof(float) * MAX);

    // generate matrix
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            m[i][j] = (random() % 15);
            printf("%.2f\t", m[i][j]);
        }
        printf("\n");
    }

    printf("\nmax = %.2f\n", get_minmax_matrix(m));
    return 0;
}

float get_minmax_matrix(float** m) {
    float* linha = (float*) malloc(sizeof(float) * MAX);
    int min = 0;
    float minVal = m[0][0];
    float max = m[0][0];

    for (int i = 0; i < MAX; i++) {
        max = m[i][0];
        for (int j = 0; j < MAX; j++) {
            // save max value on linha[]
            if (max < m[i][j]) { max = m[i][j]; linha[i] = max;}
            // save min value(index) on min.
            if (minVal > m[i][j]) { minVal = m[i][j]; min = i; }
        }
    }

    printf("\nmin = %.2f\tlinha[0] = %.2f\n", minVal, linha[min]);
    return linha[min];
}
