#include <stdio.h>
#include <limits.h>
#include <time.h>

#define MAX 100000000
static char str[MAX];

int count_vowel(char* s);
int count_vowel_rec(char* s, int c);
int count_vowel2(char* s);
int count_vowel_rec2(char* s, int c);
char to_lower(char c);
int is_vowel(char c);
int is_vowel2(char c);


int main(int argc, char** argv) {
    for (long i = 0; i < MAX; i++)
        str[i] = "abcdefghijklmnopqrstuvwxyz"[random() % 26];

    printf("str = %s\n\n\n", str);
    clock_t t_elapsed;
    double time_taken;
    int interative;
    int recursive;

    t_elapsed = clock();
    interative = count_vowel(str);
    t_elapsed = clock() - t_elapsed;
    time_taken = ((double) t_elapsed) / CLOCKS_PER_SEC;
    printf("iter lookup1 count = %d\ttime = %f\n", interative, time_taken);

    t_elapsed = clock();
    recursive = count_vowel_rec(str, 0);
    t_elapsed = clock() - t_elapsed;
    time_taken = ((double) t_elapsed) / CLOCKS_PER_SEC;
    printf("rec lookup1 count = %d\t\ttime = %f\n", recursive, time_taken);

    t_elapsed = clock();
    interative = count_vowel2(str);
    t_elapsed = clock() - t_elapsed;
    time_taken = ((double) t_elapsed) / CLOCKS_PER_SEC;
    printf("iter lookup2 count = %d\ttime = %f\n", interative, time_taken);

    t_elapsed = clock();
    recursive = count_vowel_rec2(str, 0);
    t_elapsed = clock() - t_elapsed;
    time_taken = ((double) t_elapsed) / CLOCKS_PER_SEC;
    printf("rec lookup2 count = %d\t\ttime = %f\n", recursive, time_taken);

    return 0;
}

char to_lower(char c) {
    char r = c;
    if (c >= 'A' && c <= 'Z')
       r ^= 'a' - 'A'; 
    return r;
}

int is_vowel(char c) {
    if (c < 'a' || c > 'z') return 0;
    int v_lookup[1 << CHAR_BIT] = {0};
    v_lookup['a'] = v_lookup['e'] = v_lookup['i'] = v_lookup['o'] = v_lookup['u'] = 1;
    return v_lookup[c] ? 1: 0;
}

int count_vowel(char* s) {
    int i = 0;
    int count = 0;
    while (s[i++]) {
        char c = to_lower(s[i]);
        if (is_vowel(c)) count++;
    }
    return count;
}

int count_vowel_rec(char* s, int c) {
    int count = 0;
    if (s[c] != '\0') 
        count = is_vowel(to_lower(s[c])) ? 1 + count_vowel_rec(s, c + 1) : 0 + count_vowel_rec(s, c + 1);
    return count;
}

int is_vowel2(char c) {
    if (c < 'a' || c > 'z') return 0;
    int v_lookup2[('z' - 'A') - 31] = {0}; //starts at 0
    v_lookup2['a' - 'A' - 32] = v_lookup2['e' - 'A' - 32] = v_lookup2['i' - 'A' - 32] = v_lookup2['o' - 'A' - 32] = v_lookup2['u' - 'A' - 32] = 1;
    return v_lookup2[c - 'a'] ? 1: 0;
}

int count_vowel2(char* s) {
    int i = 0;
    int count = 0;
    while (s[i] != '\0') {
        char c = to_lower(s[i]);
        if (is_vowel2(c)) count++;
        i++;
    }
    return count;
}

int count_vowel_rec2(char* s, int c) {
    int count = 0;
    if (s[c] != '\0') 
        count = is_vowel2(to_lower(s[c])) ? 1 + count_vowel_rec2(s, c + 1) : 0 + count_vowel_rec2(s, c + 1);
    return count;
}
