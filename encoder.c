#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/codebar.h"
#include "include/pbm.h"

void usage() {
    printf("\nModo de uso:\n");
    printf("\n$ ./encoder <identificador> -m <margem_lateral> -p <pixel_por_area> -a <altura_do_codigo> -n <nome_do_arquivo> \n\n");
    printf("-m............Margem lateral, em px (opcional)\n");
    printf("-p............Pixel por área do código (opcional)\n");
    printf("-a............Altura do códgido em pixels (opcional)\n");
    printf("-f............Caminho do arquivo do código de barras (opcional)\n");
    printf("-h............Ver modo de uso (opcional)\n");
}


int main(int argc, char* argv[]) {
    CodigoDeBarras c;

    // Valores padrão
    c.pxMargem = 8;
    c.pxPorArea = 3;
    c.pxAltura = 180;
    c.path = "codigo.pbm";

    if (strcmp(argv[1], "-h") == 0) {
        usage();
        exit(-1);
    } else {
        int resultado = isIdentificadorValido(argv[1]);

        if (resultado == 0) {
            usage();
            exit(-1);
        } else {
            c.identificador = resultado;
        }
    }

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
            c.pxMargem = atoi(argv[i + 1]);
            i++;
        }

        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            c.pxPorArea = atoi(argv[i + 1]);
            i++;
        }

        if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) {
            c.pxAltura = atoi(argv[i + 1]);
            i++;
        }

        if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            c.path = argv[i + 1];
            i++;
        }

        if (strcmp(argv[i], "-h") == 0) {
            usage();
            exit(-1);
        }
    }

    printf("========== GERANDO CÓDIGO DE BARRAS ==========\n");
    printf("> Identificador: %d\n", c.identificador);
    printf("> Margem: %d\n", c.pxMargem);
    printf("> Px por área: %d\n", c.pxPorArea);
    printf("> Altura: %d\n", c.pxAltura);
    printf("> Arquivo: %s\n", c.path);
    
    getBinario(&c);
    gerarPBM(&c);
    
    return 0;
}