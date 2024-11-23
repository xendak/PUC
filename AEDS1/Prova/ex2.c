#include <stdio.h>
#include <stdlib.h>


#define MAX 100
int TAM = 0;

struct Func {
    char nome[MAX];
    float salario;
};
typedef struct Func Func;


void print_funcs_sal(Func*, float);
void print_funcs_sal_rec(Func*, float, int);
Func* create_func_vec(char*);


int main() {
    Func* funcs; 
    funcs = create_func_vec("in.txt");
    if (funcs == NULL) { fprintf(stderr, "Erro -1"); return 1; } 
    print_funcs_sal_rec(funcs, 3000, 0);

    return 0;
}

Func* create_func_vec(char* fname) {
    FILE* f = fopen(fname, "r");
    if (f == NULL) return NULL;

    int qtd;

    fscanf(f, "%d\n", &qtd);
    Func* funcs = (Func*) malloc(sizeof(Func) * MAX);
    for (int i = 0; i < qtd; i++) {
        fscanf(f, "%[^\n]", funcs[i].nome);
        fscanf(f, "%f\n", &funcs[i].salario);
        TAM++;
    }

    fclose(f); // 

    return funcs;
}

void print_funcs_sal_rec(Func* f, float sal, int n) {
    if (n < TAM) {
        if (f[n].salario == sal)
            printf("%s\t%.2f\n", f[n].nome, f[n].salario);
        print_funcs_sal_rec(f, sal, n+1);
    }
}

void print_funcs_sal(Func* f, float sal) {
    for (int i = 0; i < TAM; i++)
        if (f[i].salario == sal)
            printf("%s\t%.2f\n", f[i].nome, f[i].salario);
}
