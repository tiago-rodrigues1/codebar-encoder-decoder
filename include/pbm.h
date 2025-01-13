#include "./codebar.h"

int arquivoExiste(char *path);
void gerarPBM(CodigoDeBarras *codigo);
void extrairCodigoBinario(char *path, char stringBinario[TAM_CODIGO_DE_BARRAS]);