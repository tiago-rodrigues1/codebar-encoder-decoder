#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/pbm.h"

void gerarPBM(CodigoDeBarras *codigo) {
    int larguraCodigo = codigo->pxPorArea * TAM_CODIGO_DE_BARRAS;
    int larguraTotal = larguraCodigo + (2 * codigo->pxMargem);
    int alturaTotal = codigo->pxAltura + (2 * codigo->pxMargem);

    FILE *pbm;
    pbm = fopen("codigo.pbm", "w");

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