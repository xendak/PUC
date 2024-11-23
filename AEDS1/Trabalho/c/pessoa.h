#ifndef PESSOA_H
#define PESSOA_H

#include "data.h"

#define MAX 50

typedef struct {
    char* nome;
    char* cpf;
    Data data_nascimento;
} s_Pessoa;

typedef struct {
    s_Pessoa p[MAX];
    int tam;
} Pessoa;


void escreve_pessoas(Pessoa*, char*, char*);
s_Pessoa escreve_s_pessoa(char*, char*);
Pessoa criar_pessoa();
void print_ultima_pessoa(Pessoa);
void print_todas_pessoas(Pessoa);
Pessoa pesquisa_pessoa(Pessoa, char*);
s_Pessoa* pesquisa_pessoa_cpf(Pessoa, char*);

#endif // PESSOA_H
