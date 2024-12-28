#include <stdio.h>

#include "../include/codebar.h"

void decompoeIdentificador(int identificador, int arr[TAM_VERIFICADOR]) {
    int divisor = 10000000, aux = identificador, digito = 0;

    for (int i = 0; i < TAM_VERIFICADOR; i++) {
        digito = aux / divisor;
        aux -= digito * divisor;

        arr[i] = digito;
        divisor /= 10;
    }
}

int isDigitoVerificadorValido(int identificador) {
    int soma = 0;
    int numerosIdentificador[TAM_VERIFICADOR];

    decompoeIdentificador(identificador, numerosIdentificador);

    for (int i = 0; i < 7; i++) {
        int peso = 3;

        if ((i + 1) % 2 == 0) {
            peso = 1;
        }

        soma += peso * numerosIdentificador[i];
    }

    printf("%d\n", soma);

    int multiploDe10;

    if (soma % 10 == 0) {
        multiploDe10 = soma;
    } else {
        multiploDe10 = (soma / 10 + 1) * 10;
    }

    int digitoVerificadorCorreto = multiploDe10 - soma;
    int ultimoDigito = numerosIdentificador[TAM_VERIFICADOR - 1];

    return digitoVerificadorCorreto == ultimoDigito;
}