#include <stdio.h>
#include <string.h>

#define MAX 100

typedef enum {
    false,
    true
} bool;

bool is_capital(char c) {
    return c >= 'A' && c <= 'Z';
}

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

bool mercosul(char* line) {
    int len = strlen(line);
    bool p0 = len == 7; // size = 7
    bool p1 = true;     // 0->2 char = CAPITAL

    // p1
    for (int i = 0; i < 2; i++) {
       if (!is_capital(line[i])) p1 = false;
    }

    bool p2 = is_digit(line[3]);   // [3] == DIGIT
    bool p3 = is_capital(line[4]); // [4] == CAPITAL
    
    bool p4 = is_digit(line[len-1]) && is_digit(line[len-2]); // [n-2][n-1] == DIGIT


    return p0 && p1 && p2 && p3 && p4;
}

bool antigo(char* line) {
    int len = strlen(line);
    bool p0 = len == 8; // size = 8
    bool p1 = true;     // [0->3] = CAPITAL
    for (int i = 0; i < 3; i++) {
        if (!is_capital(line[i])) p1 = false;
    }
    bool p2 = line[3] == '-'; // [3] == dash
    bool p3 = true;           // [4->END] == DIGIT
    for (int i = 4; i < len; i++) {
        if (!is_digit(line[i])) p3 = false;
    }

    return p0 && p1 && p2 && p3;
}

int main() {
    char line[MAX];
    scanf("%s", line);
    if (mercosul(line)) printf("2\n");
    else if (antigo(line)) printf("1\n");
    else printf("0\n");
    printf("\n");
}
