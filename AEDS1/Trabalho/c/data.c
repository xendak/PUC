#include "data.h"

int dia_por_mes(Data d) {
    int dias_m[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return dias_m[d.mes-1];
}

char* mes_nome(Data d) {
    char* mes[] = {
        "janeiro", 
        "fevereiro", 
        "março",
        "abril",
        "maio",
        "junho",
        "julho",
        "agosto",
        "setembro",
        "outubro",
        "novembro",
        "dezembro"
    };

    return mes[d.mes-1];
}

bool is_bissexto(Data d) {
    return d.ano % 4 == 0;
}

bool is_data_valida(Data d) {
    bool res = true;
    if (d.dia > dia_por_mes(d)) res = false;
    else if (d.mes > 12 || d.mes <= 0) res = false;
    else if(d.ano <= 0) res = false;

    return res;
}
