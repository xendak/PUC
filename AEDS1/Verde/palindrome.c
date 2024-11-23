#include <stdio.h>

#define MAX 1000

int mystr_cmp(char*, char*);
int mystr_len(char*);
int mychar_cmp(char, char);
char mychar_to_lower(char);


void check_palindrome(char*);


int main() {
    char line[MAX];
    scanf("%[^\n]", line);

    while (mystr_cmp(line, "FIM")) {
        printf("%s\t", line);
        check_palindrome(line);
        scanf(" %[^\n]", line);
    }
}

int mychar_cmp(char a, char b) {
    return (mychar_to_lower(a) - 'A') - (mychar_to_lower(b) - 'A'); 
}

char mychar_to_lower(char c) {
    char r = c;
    if (c >= 'A' && c <= 'Z')
       r ^= 'a' - 'A'; 
    return r;
}

int mystr_cmp(char* a, char* b) {
    int asz = mystr_len(a);
    int bsz = mystr_len(b);
    int min = asz >= bsz ? bsz : asz;
    int val = asz - bsz;

    int i = 0;
    do  {
        val = mychar_cmp(a[i], b[i]);
        i++;
    } while (i < min && a[i] == b[i]);

    return val;
}

int mystr_len(char* s) {
    int sz = 0;
    while(s[sz++])
        ;;
    return sz;
}

int is_even(int n) {
    int c[2] = {0, 1};
    return c[n & 1];
}

void check_palindrome(char* s) {
    int sz = mystr_len(s) - 2;
    sz = is_even(sz) == 0 ? sz : sz + 1;
    int i = 0;
    int pal = 1;
    while (i < (int)(sz/2) && pal) {
        if (s[i] != s[sz-i]) { pal = 0; }
        i++;
    }
    char* palindrome[2] = {"NAO", "SIM"};
    printf("%s\n", palindrome[pal]);
}
