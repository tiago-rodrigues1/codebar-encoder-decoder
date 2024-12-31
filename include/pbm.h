#include "./codebar.h"

#ifndef OUTPUT_PATH
#define OUTPUT_PATH "/output/"
#endif

int arquivoExiste(char *path);
void gerarPBM(CodigoDeBarras *codigo);