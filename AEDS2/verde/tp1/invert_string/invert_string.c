#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>

void reverse_string(const char* str, int i, int sz) {
    if (i <= sz) {
        printf("%c", str[sz-i]);
        reverse_string(str, i+1, sz);
    }
}

void recursive_reverse_string(const char* str) { 

    reverse_string(str, 0, strlen(str) - 1);
    printf("\n");
}

int main() {
    // locale was getting f. up
    setlocale(LC_ALL, "");
    
    char line[1000];
    
    while (fgets(line, sizeof(line), stdin)) {
        
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[--len] = '\0';
        }

        if (strcmp(line, "FIM") != 0) 
            recursive_reverse_string(line);
    }
    
    return 0;
}
