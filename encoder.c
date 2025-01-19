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
        int resultado = isIdentificadorValido(argv[1]); //quando é válido retorna o próprio identificador

        if (resultado == 0) {
            usage();
            exit(-1);
        } else {
            c.identificador = resultado;
        }
    }
    //primeiro parametro é o nome do arquivo por isso o 2
    for (int i = 2; i < argc; i++) { //argc: quantos parametros o usuario digitou v: quais foram
        if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
            int valor = atoi(argv[i + 1]);
            if (valor != 0) {

                c.pxMargem = valor;
            }

            i++;
        }

        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            int valor = atoi(argv[i + 1]);
            if (valor != 0) {

                c.pxPorArea = valor;
            }

            i++;
        }

        if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) {
            int valor = atoi(argv[i + 1]);
            if (valor != 0) {
                c.pxAltura = valor;
            }

            i++;
        }

        if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            char *valor;

            if (strlen(valor) > 0) {
                c.path = argv[i + 1];
            }

            i++;
        }

        if (strcmp(argv[i], "-h") == 0) {
            usage();
            exit(-1);
        }
    }

    if (arquivoExiste(c.path)) {
        printf("[ATENÇÃO] %s já existe\n\n", c.path);

        char podeSobrescrever;
        printf("> Gostaria de sobrescrever ? [Y/N]: ");
        scanf("%c", &podeSobrescrever);

        if (podeSobrescrever == 'n' || podeSobrescrever == 'N') {
            printf("[ERRO] arquivo resultante já existe\n");
            exit(-1);
        }

    }

    printf("\n========== GERANDO CÓDIGO DE BARRAS ==========\n");
    printCodigoDeBarras(&c);  //printa os párametros la de cima
    converteDecimalParaBinario(&c); //transforma de decimal para binario
    gerarPBM(&c); //gera o arquivo 
    
    return 0;
}