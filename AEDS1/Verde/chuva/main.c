#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int row, col;

void print_matrix(char m[][col]);

int check_left(char m[][col], int currRow, int pos) {
    int len = 0;
    int left = pos - 1;
    char cursor = m[currRow + 1][left];

    while (cursor == '#') {
        m[currRow][left - len] = 'o';
        len++;
        cursor = m[currRow + 1][left - len];
    }

    m[currRow][left - len] = 'o';
    if(currRow + 1 < row)
        m[currRow + 1][left - len] = 'o';
    if(currRow + 2 < row)
        m[currRow + 2][left - len] = 'o';
    return len;
}

int check_right(char m[][col], int currRow, int pos) {
    int len = 0;
    int right = pos + 1;
    char cursor = m[currRow + 1][right];

    while (cursor == '#') {
        m[currRow][right + len] = 'o';
        len++;
        cursor = m[currRow + 1][right + len];
    }

    m[currRow][right + len] = 'o';
    if(currRow + 1 < row)
        m[currRow + 1][right + len] = 'o';
    if(currRow + 2 < row)
        m[currRow + 2][right + len] = 'o';
    return len;
}

bool does_fall(char m[][col], int currRow, int pos) {
    return m[currRow + 1][pos] == '.';
}


int* get_all_drops(char m[][col], int currRow) {
    int* c = (int*)malloc(sizeof(int) * col);
    if (c == NULL) {
        exit(1);
    }
    
    for (int i = 0; i < col; i++) {
        c[i] = (m[currRow][i] == 'o') ? 1 : 0;
    }
    return c;
}

void let_it_fall(char m[][col]) {
    for (int i = 0; i < row-2; i += 2) {
        int* drops = get_all_drops(m, i);

        for (int j = 0; j < col; j++) {
            if (drops[j]) {
                if (does_fall(m, i, j)) { 
                    m[i+1][j] = 'o'; 
                    m[i+2][j] = 'o'; 
                } else  {
                    int left = check_left(m, i, j);
                    int right = check_right(m, i, j);
                }
            }
        }
        free(drops);
    }
}

int main() {
    row = col = 0;
    scanf("%d %d\n", &row, &col);

    char board[row][col];
    for(int i = 0; i < row; i++) 
        for (int j = 0; j < col; j++) 
            if(j == col-1)
                scanf("%c\n", &board[i][j]);
            else
                scanf("%c", &board[i][j]);
        

    let_it_fall(board);
    print_matrix(board);
    return 0;
}

void print_matrix(char m[][col]) {
    for(int i = 0; i < row; i++) { 
        for (int j = 0; j < col; j++) 
            printf("%c", m[i][j]);
        printf("\n");
    }
}
