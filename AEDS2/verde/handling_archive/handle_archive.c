#include <stdio.h>

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
        float num;
        scanf("%f\n", &num);
        fprintf(file, "%.3f\n", num);
    }

    fclose(file);

    file = fopen("numbers.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long pos = ftell(file);
    char c;

    while (pos > 0) {
        fseek(file, --pos, SEEK_SET);
        c = fgetc(file);
        if (c == '\n' || pos == 0) {
            long start = pos + (c != '\n' ? 0 : 1);
            fseek(file, start, SEEK_SET);
            char line[100];
            fgets(line, sizeof(line), file);
            printf("%s", line);
        }
    }

    fclose(file);
    return 0;
}

