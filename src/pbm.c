#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/pbm.h"

int arquivoExiste(char *path) {
    FILE *arquivo;
    arquivo = fopen(path, "r");

    int existe = arquivo != NULL;

    if (existe) {
        fclose(arquivo);
    }
    
    return existe;
}

int pbmValido(char *path){
    FILE *arquivo;
    arquivo = fopen(path, "r");
    char *tipo, *stringLargura, *stringAltura;
    
    fscanf(arquivo, "%s", tipo);
    fscanf(arquivo, "%s %s", stringLargura, stringAltura);

    if (strcmp(tipo,"P1") != 0){
        printf("[ERRO] PBM inválido");
        return 0; //0 falso
    }

    int largura = atoi(stringLargura);
    int altura = atoi(stringAltura);
    
    if (largura == 0 && altura == 0){
        printf("[ERRO] PBM inválido");
        return 0;
    }
    
    return 1;
}


void gerarPBM(CodigoDeBarras *codigo) {
    int larguraCodigo = codigo->pxPorArea * TAM_CODIGO_DE_BARRAS;
    int larguraTotal = larguraCodigo + (2 * codigo->pxMargem);
    int alturaTotal = codigo->pxAltura + (2 * codigo->pxMargem);

    FILE *pbm;
    pbm = fopen(codigo->nome, "w");

    fprintf(pbm, "%s\n%d %d\n", "P1", larguraTotal, alturaTotal);

    for (int i = 0; i < alturaTotal; i++) {
        char *margem;
        margem = calloc(larguraTotal, sizeof(char));

        if (i < codigo->pxMargem || i > codigo->pxAltura + 1) {
            memset(margem, '0', larguraTotal);

            fprintf(pbm, "%s\n", margem);
        } else {
            memset(margem, '0', codigo->pxMargem);

            fprintf(pbm, "%s", margem);
            
            for (int j = 0; j < TAM_CODIGO_DE_BARRAS; j++) {
                char *buffer;
                buffer = calloc(codigo->pxPorArea, sizeof(char));

                memset(buffer, codigo->binario[j], codigo->pxPorArea);
                fprintf(pbm, "%s", buffer);
            }

            fprintf(pbm, "%s\n", margem);
        }
        
    }

    fclose(pbm);
}