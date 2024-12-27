#include <stdio.h>

#include "../include/codebar.h"

int isDigitoVerificadorValido(int identificador) {
    int soma = 0, divisor = 10000000, aux = identificador, digito = 4;

    for (int i = 1; i <= 7; i++) {
        int peso = 3;

        if (i % 2 == 0) {
            peso = 1;
        }

        digito = aux / divisor;
        aux -= digito * divisor;
        divisor /= 10;

        soma += peso * digito;
    }

    int multiploDe10;

    if (soma % 10 == 0) {
        multiploDe10 = soma;
    } else {
        multiploDe10 = (soma / 10 + 1) * 10;
    }

    int digitoVerificadorCorreto = multiploDe10 - soma;

    // aux agora representa o último digito
    return digitoVerificadorCorreto == aux;
}