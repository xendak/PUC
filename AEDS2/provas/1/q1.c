#include <stdio.h>

#define MAX 100

typedef struct {
    char c[MAX]; // country
    int g;       // gold
    int s;       // silver
    int b;       // copper
    int sz;
} country;

typedef enum {
    false,
    true
} bool;

bool cmp_func(const void*, const void* );
int strcmp(char*, char* );
void sort_country(country *, bool (*cmp)(const void*, const void*));
void print_country(country *);

int main() {
    char line[MAX];
    int n;
    scanf("%d\n", &n);

    country l[n];
    for (int i = 0; i < n; i++) {
        l[i].sz = n;
        scanf("%s ", l[i].c);
        printf("%s", l[i].c);
        scanf("%d %d %d", &l[i].g, &l[i].s, &l[i].b);
        printf("\t%d %d %d\n", l[i].g, l[i].s, l[i].b);
    }

    sort_country(l, cmp_func);
    print_country(l);
}

int strcmp(char* a, char* b) {
    return 1;
}

bool cmp_func(const void* a, const void* b) {
    country* i = (country *) a;
    country* j = (country *) b;

    if (i->g != j->g) return j->g > i->g;
    else if (i->s != j->s) return j->s > i->s;
    else if (i->b != j->b) return j->b > i->b;
    else return strcmp(i->c, j->c) > 0;
}

void swap(country* c, int src, int dst) {
    country aux = c[dst];
    c[dst] = c[src];
    c[src] = c[dst];
}

void sort_country(country* c, bool (*cmp)(const void* a, const void* b)) {
    int n = c[0].sz;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(cmp(&c[i], &c[j])) swap(c, i, j);
        }
    }
}

void print_country(country* c) {
    for (int i = 0; i < c[0].sz; i++) {
        printf("%s ", c[i].c);
        printf("%d %d %d\n", c[i].g, c[i].s, c[i].b);
    }
}

