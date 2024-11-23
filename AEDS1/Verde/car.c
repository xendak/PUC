#include <stdio.h>

#define MAX 100
int TAM = 0;

typedef struct {
    char marca[MAX];
    int ano;
    float valor;
} Carro;

void ler_carro(Carro *);
void print_output(Carro *, float);

int main() {
    float max_val = 0;
    Carro carros[MAX];

    scanf("%d", &TAM);
    for (int i = 0; i < TAM; i++)
        ler_carro(&carros[i]);

    scanf("%f", &max_val);
    print_output(carros, max_val);

    return 0;
}

void ler_carro(Carro* c) {
    scanf("%s", c->marca);
    scanf("%d", &c->ano);
    scanf("%f", &c->valor);
}

void print_output(Carro* c, float val) {
    printf("Carros com preco menor que %.2f:\n", val);
    for (int i = 0; i < TAM; i++) {
        if (val > c[i].valor) { printf("Marca: %s, Ano: %d, Preco: %.2f\n", c[i].marca, c[i].ano, c[i].valor); }
    }
}
