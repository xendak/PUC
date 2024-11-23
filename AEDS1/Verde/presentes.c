#include <stdio.h>
#include <string.h>

#define MAX 100
int TAM = 0;

typedef struct {
    char nome[MAX];
    float preco;
    int pref;
} Presente;

typedef struct {
    char nome[MAX];
    int qtd;
    Presente p[MAX];
} Pessoa;

/**
 * As duas funções a baixo foram feitas com intuito de melhorar meu entendimento para ponteiros de funções, entretanto, poderia ter side feito normalmente com if's 
 * pois ja conhece-se todos os tipos utilizados, logo não precisa-se de uma abordagem genérica.
**/
int cmp_type(const void*, const void*);
void sort_presentes(Presente*, int, int (*cmp)(const void*, const void*));

void print_output(Pessoa*);

int main() {
    Pessoa pessoas[MAX];
    /**
     * Assumo que tudo seria lido "perfeitamente", não foi descrito no problema para tratar de entradas erradas ou fora dos limites
     * portanto aceito o valor como o indicado, mesmo que esteja fora dos parametros mencionados no problema.
    **/
    while (scanf("%s %d\n", pessoas[TAM].nome, &pessoas[TAM].qtd) != EOF) {
        int num_presentes = pessoas[TAM].qtd;
        /*printf("\nPessoa: %s\tNum_Lista: %d\n\n", pessoas[TAM].nome, num_presentes);*/
        for (int i = 0; i < num_presentes; i++) {
            Presente* presente = &pessoas[TAM].p[i];

            /** 
             * poderia utilizar a função fgets, como exemplo abaixo, porem adiciona um new line
             * fgets(presente->nome, sizeof(presente), stdin);
             * e utilizando o a funcao a baixo seria possivel mudar o \n por \0 para termino de string,
             * porém eu não conhecia isso e tive de procurar, achei não convencional para o caso de um exercicio
             * presente->nome[strcspn(presente->nome, "\n")] = '\0'; 
             * portanto preferi usar scanf até o \n, msm que apresente problema de OVERFLOW caso o buffer da linha seja maior que o 
             * limite do nome[MAX], porém assim eu conseguiria fazer sem pesquisa de google, vide situação de prova
            **/

            scanf("%[^\n]", presente->nome);
            scanf("%f %d\n", &presente->preco, &presente->pref);

            /*printf("%d.I: %s\tP: %d\tP:%.2f\n", i, presente->nome, presente->pref, presente->preco);*/
        }
        TAM++;
    }

    for (int i = 0; i < TAM; i++)
        sort_presentes(pessoas[i].p, pessoas[i].qtd, cmp_type);
    print_output(pessoas);
    return 0;
}

int cmp_type(const void* a, const void* b) {
    Presente *p1 = (Presente *) a;
    Presente *p2 = (Presente *) b;
    int ret;
    if (p1->pref != p2->pref)
        ret =  (p2->pref - p1->pref);
    else if (p1->preco != p2->preco)
        ret = (p1->preco > p2->preco) - (p1->preco < p2->preco);
    else
        ret = strcmp(p1->nome, p2->nome);

    return ret;
}

void sort_presentes(Presente* lista, int qtd, int (*cmp)(const void*, const void*)) {
    /**
     * utilizando um método "burro" de organização,
     * e utilizando ponteiros para funções para definir o tipo certo de comparação a ser feito
     * com intuinto de aprendizado para func*
    **/
    Presente temp;
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
            if (cmp(&lista[j], &lista[j + 1]) > 0) {
                temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
}


void print_output(Pessoa* pessoas) {
    for (int i = 0; i < TAM; i++) {
        printf("Lista de %s\n", pessoas[i].nome);
        for (int j = 0; j < pessoas[i].qtd; j++) {
            Presente* p = &pessoas[i].p[j];
            printf("%s - R$%.2f\n", p->nome, p->preco);
        }
        printf("\n");
    }
}
