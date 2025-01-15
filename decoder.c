#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/codebar.h"
#include "include/pbm.h"

void usage() {
    printf("Modo de uso:\n");
    printf("$ ./decoder <nome_do_arquivo>\n");
}

int main() {
    // char *path;
    // path = argv[1];

    // if (strcmp(argv[1], "-h") == 0 || argv[1] == NULL) {
    //     usage();
    //     exit(-1);
    // }

    // int x = getDecimal("1010011001001001101111010100011010101001110101000010001001110010101");

    // int existe = pbmValido("codigo.pbm");
    // pbmValido("codigo.pbm");
    // printf("---> %d\n", existe);

    char stringBinario[TAM_CODIGO_DE_BARRAS];

    extrairCodigoBinario("tiago.pbm", stringBinario);

    printf("%s\n", stringBinario);

    return 0;
}