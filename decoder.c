#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/definitions.h"
#include "include/codebar.h"
#include "include/pbm.h"

void usage() { //deborah
    printf("Modo de uso:\n");
    printf("$ ./decoder <nome_do_arquivo>\n");
}

int main(int argc, char *argv[]) {
    char *path;
    path = argv[1];


    if (argc == 1 || argv[1] == NULL) {
        printf("[ERRO] Você precisa informar o caminho de um arquivo\n");
        usage();
        exit(-1);
    }

    if (strcmp(argv[1], "-h") == 0) {
        usage();
        exit(-1);
    }

    if (arquivoExiste(path) == 0) {
        printf("[ERRO] %s não foi encontrado\n", path);
        exit(-1);
    }

    CodigoDeBarras c;  

    c.path = path;
    extrairCodigoBinario(&c);
    
    int identificador = getDecimal(&c);
    c.identificador = identificador;

    printf("========== EXTRAINDO CÓDIGO DE BARRAS ==========\n");
    printCodigoDeBarras(&c);

    return 0;
}