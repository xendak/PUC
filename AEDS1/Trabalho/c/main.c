#include <stdio.h>
#include "pessoa.h"

#define MAX 50

int main(int argc, char** argv) {

    Pessoa Pessoas = criar_pessoa();
    escreve_pessoas(&Pessoas, "anna", NULL);
    escreve_pessoas(&Pessoas, "david", NULL);
    escreve_pessoas(&Pessoas, "john 2", NULL);
    escreve_pessoas(&Pessoas, "john 1", NULL);


    Pessoa t = pesquisa_pessoa(Pessoas, "john");

    // print_todas_pessoas(Pessoas);
    print_todas_pessoas(t);

    return 0;
}
