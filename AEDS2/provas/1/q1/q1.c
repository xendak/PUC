#include <stdio.h>

#define MAX 100

typedef struct {
    char name[MAX];
    int gold;
    int silver;
    int copper;
    int size; // so we dont use a global var, though takes more space.
} country;

typedef enum {
    false,
    true
} bool;

/* comparison function for the struct 
 * takes 2 countries a and b
 * returns a value boolean
 */
bool cmp_func(const void*, const void*);

/* swap function
 * takes an array/pointer to a country and indexes for both source and destination
 * swap in place.
 */
void swap_func(void*, int, int);

/* self implementation of strcmp
 * returns the difference (a - b), of each character, in int.
 * positive means a > b, 0 means equal, negative means b > a
 */
int strcmp(const char*, const char*);

/* util functions, self implementation */
/* returns length of a string (does not count \0) */
unsigned long strlen(const char*);
/* returns min value between a and b*/
int imin(int, int);

/* bubble sort algorithm for a generic array dataset
 * -- need to implement comparison and swap function to each case.
 * takes a pointer to an object/struct
 * a pointer to comparison function
 * and a pointer to a swap function
 * does sort in place
 */
void bubble_sort_country(void*, 
        bool (*cmp)(const void*, const void*), 
        void (*swp)(void*, int, int));


/* print functions for our struct */
void print_country(country);
void print_countries(country *);
void print_reverse_country(country *);

int main() {
    char line[MAX];
    int n;
    /* 
     * scanf returns the number of successfully scanned variables.
     * treat as error and quit program if read went wrong.
    */

    if (scanf("%d\n", &n) != 1) return -1;

    country l[n];
    for (int i = 0; i < n; i++) {
        l[i].size = n;
        if (scanf("%s ", l[i].name) != 1) return -1;
        if (scanf("%d %d %d", &l[i].gold, &l[i].silver, &l[i].copper) != 3) return -1;
    }

    bubble_sort_country(l, cmp_func, swap_func);
    print_reverse_country(l);
    return 0;
}

unsigned long strlen(const char* str) {
    int len = 0;
    while(str[len++])
        ;;
    return len;
}

int imin(int a, int b) {
    return a > b ? b : a;
}

int strcmp(const char* a, const char* b) {
   int len = imin(strlen(a), strlen(b));
   int res = 0; int i = 0;
   while(res == 0 && i < len) {
       res = (int) ((int)a[i] - (int)b[i]);
       i++;
   }
   return res;
}

bool cmp_func(const void* a, const void* b) {
    const country* i = (const country *) a;
    const country* j = (const country *) b;
    if(i == j) return 0;

    if (i->gold != j->gold) return j->gold > i->gold;
    else if (i->silver != j->silver) return j->silver > i->silver;
    else if (i->copper != j->copper) return j->copper > i->copper;
    else return strcmp(i->name, j->name) > 0;
}

void swap_func(void* obj, int src, int dst) {
    country* c = (country*) obj;
    country tmp = c[dst];
    c[dst] = c[src];
    c[src] = tmp;
}

// TODO: change bubble to something decent.
void bubble_sort_country(void* obj, 
        bool (*cmp)(const void* a, const void* b),
        void (*swp)(void* obj, int src, int dst)) {

    country* c = (country *) obj;
    int n = c[0].size;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(cmp(&c[i], &c[j])) swp(c, i, j);
        }
    }
}

void print_country(country c) {
    printf("%s ", c.name);
    printf("%d %d %d\n", c.gold, c.silver, c.copper);
}

void print_countries(country* c) {
    for (int i = 0; i < c[0].size; i++) {
        print_country(c[i]);
    }
}

void print_reverse_country(country* c) {
    for (int i = 0; i < c[0].size; i++) {
        print_country(c[c[0].size - i - 1]);
    }
}

