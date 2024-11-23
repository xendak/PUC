#include <stdio.h>

char is_even(int);

int main() {
    int num;

    scanf("%d", &num);
    while (num != 0) {
        printf("%c\n", is_even(num));
        scanf("%d", &num);
    } 
    return 0;
}

char is_even(int n) {
   char res[2] = {'P', 'I'};
   return res[n & 1];
}
