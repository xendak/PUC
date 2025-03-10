#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>

int is_palindrome(const wchar_t *str) {
    int sz = wcslen(str) - 1;
    int pal = 1;
    int i = 0;
    while (i < (int)(wcslen(str)/2) && pal) {
        if (str[i] != str[sz - i]) { pal = 0; }
        i++;
    }

    return pal;
}

int main() {
    // locale was getting f. up
    setlocale(LC_ALL, "");
    
    char line[1000];
    
    do {
        if (!fgets(line, sizeof(line), stdin)) {
            return 0;
        }
        // was having issues with new lines on the c code .. but not java one..
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[--len] = '\0';
        }

        // handle edge
        size_t wlen = mbstowcs(NULL, line, 0);
        if (wlen == (size_t)-1) {
            printf("NAO\n");
            continue;
        }        
        wchar_t *utf_line = (wchar_t *)malloc((wlen + 1) * sizeof(wchar_t));
        if (!utf_line) {
            printf("NAO\n");
            continue;
        }
        
        mbstowcs(utf_line, line, wlen + 1);
        
        printf("%s\n", is_palindrome(utf_line) ? "SIM" : "NAO");
        
        free(utf_line);
    } while (strcmp(line, "FIM") != 0);
    
    return 0;
}
