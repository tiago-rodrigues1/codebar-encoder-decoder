#ifndef TAM_VERIFICADOR
#define TAM_VERIFICADOR 8
#endif

#ifndef TAM_CODIGO_DE_BARRAS
#define TAM_CODIGO_DE_BARRAS 67
#endif

#ifndef CODIGO_DE_BARRAS
#define CODIGO_DE_BARRAS
typedef struct codigo {
    int identificador;
    int pxMargem;
    int pxPorArea;
    int pxAltura;
    char *nome;
    char binario[TAM_CODIGO_DE_BARRAS];
} CodigoDeBarras;
#endif

int isDigitoVerificadorValido(int identificador);
void getBinario(int identificador, char stringBinario[TAM_CODIGO_DE_BARRAS]);