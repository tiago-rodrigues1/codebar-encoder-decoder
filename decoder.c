#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/definitions.h"
#include "include/codebar.h"
#include "include/pbm.h"

void usage() { //deborah
    printf("Modo de uso:\n");
    printf(ANSI_COLOR_BLUE "$ ./decoder <nome_do_arquivo>" ANSI_COLOR_RESET "\n");
}

int main(int argc, char *argv[]) {
    char *path;
    path = argv[1];


    if (argc == 1 || argv[1] == NULL) {
        printf(ANSI_COLOR_RED "[ERRO] Você precisa informar o caminho de um arquivo" ANSI_COLOR_RESET "\n");
        usage();
        exit(-1);
    }

    if (strcmp(argv[1], "-h") == 0) {
        usage();
        exit(-1);
    }

    if (arquivoExiste(path) == 0) {
        printf(ANSI_COLOR_RED "[ERRO] %s não foi encontrado" ANSI_COLOR_RESET "\n", path);
        exit(-1);
    }

    CodigoDeBarras c;  

    c.path = path;
    
    extraiBinarioDoPBM(&c);
    converteBinarioParaDecimal(&c);

    printf(ANSI_COLOR_GREEN "========== EXTRAINDO CÓDIGO DE BARRAS ==========" ANSI_COLOR_RESET "\n");
    printCodigoDeBarras(&c);

    return 0;
}