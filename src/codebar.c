#include <stdio.h>
#include <string.h>

#include "../include/codebar.h"

char tabelaRightCode[10][8] = {
    "1110010\0", // 0
    "1100110\0", // 1
    "1101100\0", // 2
    "1000010\0", // 3
    "1011100\0", // 4
    "1001110\0", // 5
    "1010000\0", // 6
    "1000100\0", // 7
    "1001000\0", // 8
    "1001000\0", // 9
};

char tabelaLeftCode[10][8] = {
    "0001101\0", // 0
    "0011001\0", // 1
    "0010011\0", // 2
    "0111101\0", // 3
    "0100011\0", // 4
    "0110001\0", // 5
    "0101111\0", // 6
    "0111011\0", // 7
    "0110111\0", // 8
    "0001011\0", // 9
};

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

void getBinario(int identificador, char stringBinario[TAM_CODIGO_DE_BARRAS]) {
    int numerosIdentificador[TAM_VERIFICADOR];
    decompoeIdentificador(identificador, numerosIdentificador);

    char codigoDeBarras[TAM_CODIGO_DE_BARRAS];
    char marcadorInicioFim[4] = "101\0";
    char marcadorCentral[6] = "01010\0";

    strcat(codigoDeBarras, marcadorInicioFim);

    for (int i = 0; i < TAM_VERIFICADOR; i++) {
        int digito = numerosIdentificador[i];
        char binario[8];

        if (i <= 3) {
            strcpy(binario, tabelaLeftCode[digito]);
        } else {
            strcpy(binario, tabelaRightCode[digito]);
        }

        strcat(codigoDeBarras, binario);

        if (i == 3) {
            strcat(codigoDeBarras, marcadorCentral);
        }
    }
    
    strcat(codigoDeBarras, marcadorInicioFim);

    strcpy(stringBinario, codigoDeBarras);
}