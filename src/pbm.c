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

int pbmValido(FILE *arquivo, int *ptrLargura) {
    char tipo[3];
    int largura, altura;

    int isValido = 1;

    if (fscanf(arquivo, "%2s", tipo) != 1 || strcmp(tipo, "P1") != 0) {
        isValido = 0;
    }

    if (fscanf(arquivo, "%d %d", &largura, &altura) != 2 || largura == 0 || altura == 0) {
        isValido = 0;
    }

    *ptrLargura = largura;
    
    return isValido;
}


void gerarPBM(CodigoDeBarras *codigo) {
    int larguraCodigo = codigo->pxPorArea * TAM_CODIGO_DE_BARRAS;
    int larguraTotal = larguraCodigo + (2 * codigo->pxMargem);
    int alturaTotal = codigo->pxAltura + (2 * codigo->pxMargem);
    char cadeia[TAM_CODIGO_DE_BARRAS + 1] = "1010000000000000000000000000000010100000000000000000000000000000101\0";

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

                if (i > codigo->pxAltura - (codigo->pxAltura * 0.05)) {
                    memset(buffer, cadeia[j], codigo->pxPorArea);
                } else {
                    memset(buffer, codigo->binario[j], codigo->pxPorArea);
                }

                fprintf(pbm, "%s", buffer);
            }

            fprintf(pbm, "%s\n", margem);
        }
        
    }

    fclose(pbm);
}

void extrairCodigoBinario(char *path, char stringBinario[TAM_CODIGO_DE_BARRAS]) {
    FILE *arquivo;
    arquivo = fopen(path, "r");

    int larguraTotal = 0;

    if (pbmValido(arquivo, &larguraTotal) == 0) {
        printf("[ERRO] %s não é um arquivo PBM válido", path);
    }

    int margem = (larguraTotal % TAM_CODIGO_DE_BARRAS) / 2;
    int larguraReal = larguraTotal - 2 * margem;
    int pxPorArea = (larguraReal) / TAM_CODIGO_DE_BARRAS;
    int offset = 1 + (larguraTotal + 1) * margem;

    char linha[larguraTotal];
    
    fseek(arquivo, offset, SEEK_CUR);
    fseek(arquivo, margem, SEEK_CUR);

    fgets(linha, larguraReal, arquivo);

    fclose(arquivo);

    int tamanhoLinha = (int)strlen(linha);
    linha[tamanhoLinha - 1] = '\0';

    char *binario = malloc(sizeof(char));
    int contador = 0;

    for (int i = 0; i + pxPorArea <= tamanhoLinha; i += pxPorArea) {
        binario[contador] = linha[i];
        contador += 1;
        binario = realloc(binario, sizeof(char) * (contador + 1));
    }

    binario[contador] = '\0';

    strcpy(stringBinario, binario);
} 
    
    
 int temCodigoDeBarras(FILE *arquivo, int *ptrLargura) {    
    char tipo[3];
    int larguraTotal, alturaTotal;

    int isValido = 1;

    if (fscanf(arquivo, "%2s", tipo) != 1 || strcmp(tipo, "P1") != 0) {
        isValido = 0;
    }

    if (fscanf(arquivo, "%d %d", &larguraTotal, &alturaTotal) != 2 || larguraTotal == 0 || alturaTotal == 0) {
        isValido = 0;
    }

    *ptrLargura = larguraTotal;
    
    if (isValido) {
        int margem = (larguraTotal % TAM_CODIGO_DE_BARRAS) / 2;
        int larguraReal = larguraTotal - 2 * margem;
        int alturaReal = alturaTotal - 2 * margem;
        int pxPorArea = (larguraReal) / TAM_CODIGO_DE_BARRAS;
        int offset = 1 + (larguraTotal + 1) * margem;

        char linhaAtual[larguraTotal];
        char linhaOriginal[larguraTotal];
    
        fseek(arquivo, offset, SEEK_CUR);

        for (int i = 0; i < alturaReal; i++) {
            if (i == 0) {
                fgets(linhaOriginal, larguraTotal, arquivo);
            }

            fgets(linhaAtual, larguraTotal, arquivo);

            if (strcmp(linhaAtual, linhaOriginal) != 0) {
                isValido = 0;
                break;
            }
        }

        return isValido;
    }

    
}

    