#ifndef DATA_H
#define DATA_H

#include <stdbool.h>

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

int dia_por_mes(Data);
char* mes_nome(Data);
bool is_bissexto(Data);
bool is_data_valida(Data);

#endif // DATA_H

