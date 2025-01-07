#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage() {
    printf("Modo de uso:\n");
    printf("$ ./decoder <nome_do_arquivo>\n");
}

int main(int argc, char* argv[]) {
    char *path;
    path = argv[1];

    if (strcmp(argv[1], "-h") == 0 || argv[1] == NULL) {
        usage();
        exit(-1);
    }

    return 0;
}