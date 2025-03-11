#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t digit_sum(size_t num) {
    return num > 0 ? num % 10 + digit_sum(num/10) : 0;
}

int main() {
    char line[1000];
    
    while (fgets(line, sizeof(line), stdin)) {
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n')
            line[--len] = '\0';

        size_t number = (size_t) atoi(line);
        if (number > 0)
            printf("%zu\n", digit_sum(number));
    }
    
    return 0;
}

