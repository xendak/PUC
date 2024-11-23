#include <stdio.h>

void inverse_order(char* str);
void inverse_order_rec(char* str, int len);
char to_lower(char c);
int str_len(char* str);

int main(int argc, char** argv) {
    char* str = "nomeFeliz";
    inverse_order(str);
    inverse_order_rec(str, str_len(str));
    return 0;
}

char to_lower(char c) {
    char r = c;
    if (c >= 'A' && c <= 'Z')
       r ^= 'a' - 'A'; 
    return r;
}

int str_len(char* str) {
    int count = 0;
    while(str[count++])
        ;;
    return count - 1;
}

void inverse_order(char* str) {
    for (int i = str_len(str); i >= 0; i--)
        printf("%c", str[i]);
    printf("\n");
}

void inverse_order_rec(char* str, int len) {
    if (len >= 0) {
        printf("%c", str[len]);
        inverse_order_rec(str, len - 1);
    }
    else
        printf("\n");
}
