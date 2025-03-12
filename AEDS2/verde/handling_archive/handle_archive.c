#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_print(char* str);

int main() {
    int n;
    FILE *file;

    scanf("%d\n", &n);

    file = fopen("numbers.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        char line[100];
        scanf("%s", line);
        fprintf(file, "%s\n", line);
    }

    fclose(file);

    file = fopen("numbers.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading\n");
        return 1;
    }

    fseek(file, 0, SEEK_END); // starts at EOF
    long pos = ftell(file);
    char c;

    while (pos >= 0) { 
        // adjust pointer to curr
        fseek(file, pos, SEEK_SET);
        // reads current character.
        c = fgetc(file);
        if (c == '\n' || pos == 0) {
            // if new line or start of file then we can adjust position again
            // and read from start till the last \n we passed before.
            // fgets always reads start->end line
            // so we just adjust the file pointer accordingly.
            long start = pos + (c != '\n' ? 0 : 1);
            fseek(file, start, SEEK_SET);
            char line[100];
            if (fgets(line, sizeof(line), file) != NULL) {
                handle_print(line);
            }
        }
        // keep moving backward
        pos--;
    }

    fclose(file);
    return 0;
}


char* mystrchr(char* str, char to_find) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == to_find)
            return &str[i]; // return the pointer
        i++;
    }
    return NULL;
}

void handle_print(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
    // ignores the first \n since we read in reverse.
    if (strlen(str) > 1) { 
        // Check if the string contains a decimal point
        // and gets its pointer.
        char* decimalPoint = mystrchr(str, '.');
        if (decimalPoint != NULL) {
            // pointer to last character. -1 from \0
            char* end = str + strlen(str) - 1; 
            while (end > decimalPoint && *end == '0') {
                *end = '\0'; // dereference and change to remove all zeros
                end--; // keep moving the pointer.
            }
            
            // if we found nothing besides the . or if we culled everything up to
            // the dot, then remove the dot as well.
            if (end == decimalPoint && *end == '.') {
                *end = '\0'; 
            }
            if (str[0] == '.') {
                printf("0");
            }
        }
        printf("%s\n", str);
    }
}
