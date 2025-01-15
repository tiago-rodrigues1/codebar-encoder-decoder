#include "./definitions.h"

int arquivoExiste(char *path);
int temCodigoDeBarras(FILE *arquivo, char *linhaBase, char stringBinario[TAM_CODIGO_DE_BARRAS], int larguraTotal, int alturaReal);
void gerarPBM(CodigoDeBarras *codigo);
void extrairCodigoBinario(char *path, char stringBinario[TAM_CODIGO_DE_BARRAS]);