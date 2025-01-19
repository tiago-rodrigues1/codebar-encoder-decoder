#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/definitions.h"
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

void decompoeIdentificador(int identificador, int arr[TAM_IDENTIFICADOR]) {
    int divisor = 10000000, aux = identificador, digito = 0;

    for (int i = 0; i < TAM_IDENTIFICADOR; i++) {
        digito = aux / divisor;
        aux -= digito * divisor;

        arr[i] = digito;
        divisor /= 10;
    }
}

int compoeIdentificador(int arr[TAM_IDENTIFICADOR]) {
    int multiplicador = 10000000, identificador = 0;

    for (int i = 0; i < TAM_IDENTIFICADOR; i++) {
        identificador += arr[i] * multiplicador;
        
        multiplicador /= 10;
    }

    return identificador;
}

int isDigitoVerificadorValido(int identificador) {
    int soma = 0;
    int numerosIdentificador[TAM_IDENTIFICADOR];

    decompoeIdentificador(identificador, numerosIdentificador);

    for (int i = 0; i < 7; i++) {
        int peso = 3;

        if ((i + 1) % 2 == 0) {
            peso = 1;
        }

        soma += peso * numerosIdentificador[i];
    }

    int multiploDe10;

    if (soma % 10 == 0) {
        multiploDe10 = soma;
    } else {
        multiploDe10 = (soma / 10 + 1) * 10;
    }

    int digitoVerificadorCorreto = multiploDe10 - soma;
    int ultimoDigito = numerosIdentificador[TAM_IDENTIFICADOR - 1];

    return digitoVerificadorCorreto == ultimoDigito;
}

int isIdentificadorValido(char *identificador) {
    int i = 0;

    for (i = 0; identificador[i] != '\0'; i++) {
        if (!isdigit(identificador[i])) { 
            printf(ANSI_COLOR_RED "[ERRO] Todos os carecteres do identificador devem ser numéricos" ANSI_COLOR_RESET "\n");
            return 0;
        }
    }

    if (i != TAM_IDENTIFICADOR) {
        printf(ANSI_COLOR_RED "[ERRO] O identificador deve ter exatamente 8 dígitos" ANSI_COLOR_RESET "\n");
        return 0;
    }

    int numIdentificador = atoi(identificador);

    if (!isDigitoVerificadorValido(numIdentificador)) {
        printf(ANSI_COLOR_RED "[ERRO] O dígito verificador não é válido" ANSI_COLOR_RESET "\n");
        return 0;
    }
    
    return numIdentificador;
}

void converteDecimalParaBinario(CodigoDeBarras *c) {
    int numerosIdentificador[TAM_IDENTIFICADOR];
    decompoeIdentificador(c->identificador, numerosIdentificador);

    char codigoDeBarras[TAM_CODIGO_DE_BARRAS] = "";
    char marcadorInicioFim[4] = "101\0";
    char marcadorCentral[6] = "01010\0";

    strcat(codigoDeBarras, marcadorInicioFim);

    for (int i = 0; i < TAM_IDENTIFICADOR; i++) {
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

    strcpy(c->binario, codigoDeBarras);
}

int converteBinarioParaDecimal(CodigoDeBarras *c) {
    int tamanhoBinario = 7, contador = 0;
    int posicaoMarcadorCentral = (TAM_CODIGO_DE_BARRAS - 1) / 2;
    int arrIdentificador[TAM_IDENTIFICADOR];

    for (int i = 3; i < posicaoMarcadorCentral - 2; i += tamanhoBinario) {
        char binario[TAM_IDENTIFICADOR];
        strncpy(binario, &c->binario[i], tamanhoBinario);
        
        binario[TAM_IDENTIFICADOR - 1] = '\0';

        for (int j = 0; j < 10; j++) {
            if (strcmp(tabelaLeftCode[j], binario) == 0) {
                arrIdentificador[contador] = j;
                contador += 1;
                break;
            }
        }
    }

    for (int i = posicaoMarcadorCentral + 3; i < TAM_CODIGO_DE_BARRAS - 3; i += tamanhoBinario) {
        char binario[TAM_IDENTIFICADOR];
        strncpy(binario, &c->binario[i], tamanhoBinario);
        
        binario[TAM_IDENTIFICADOR - 1] = '\0';

        for (int j = 0; j < 10; j++) {
            if (strcmp(tabelaRightCode[j], binario) == 0) {
                arrIdentificador[contador] = j;
                contador += 1;
                break;
            }
        }
    }

    c->identificador = compoeIdentificador(arrIdentificador);

    return 1;
}

void printCodigoDeBarras(CodigoDeBarras *c) {
    printf("> Identificador: %d\n", c->identificador);
    printf("> Margem: %d\n", c->pxMargem);
    printf("> Px por área: %d\n", c->pxPorArea);
    printf("> Altura: %d\n", c->pxAltura);
    printf("> Arquivo: %s\n", c->path);
}