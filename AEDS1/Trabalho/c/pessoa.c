#include "pessoa.h"
#include <string.h>
#include <stdio.h>

void escreve_pessoas(Pessoa* p, char* nome, char* cpf) {
    p->p[p->tam] = escreve_s_pessoa(nome, cpf);
    p->tam++;
}

s_Pessoa escreve_s_pessoa(char* nome, char* cpf) {
    s_Pessoa n;
    n.nome = nome;
    n.cpf = cpf;
    return n;
}

Pessoa criar_pessoa() {
    Pessoa p;
    p.tam = 0;
    return p;
}

void print_ultima_pessoa(Pessoa p) {
    int sz = p.tam - 1;
    s_Pessoa last = p.p[sz];
    printf("%d = %s", sz + 1, last.nome);
}

void print_todas_pessoas(Pessoa p) {
    int sz = p.tam - 1;
    s_Pessoa last = p.p[sz];
    for (int i = 0; i  < sz + 1; i++)
        printf("%d. %s\n", i + 1, p.p[i].nome);
}

Pessoa pesquisa_pessoa(Pessoa p, char* str) {
    Pessoa result = criar_pessoa();

    for (int i = 0; i < p.tam; i++) {
        if (strstr(p.p[i].nome, str) != NULL)
            escreve_pessoas(&result, str, NULL);
    }

    return result;
}

s_Pessoa* pesquisa_pessoa_cpf(Pessoa p, char* cpf) {
    s_Pessoa* res = NULL;
    int sz = p.tam;

    while(!strcmp(p.p[sz].cpf, cpf) && sz) {
        if(strcmp(p.p[sz].cpf, cpf)) res = &p.p[sz];
        sz--;
    }

    return res;
}

bool delete_pessoa_por_cpf(Pessoa* p, char* cpf) {
    return false;
}
