#ifndef TAM_IDENTIFICADOR
#define TAM_IDENTIFICADOR 8
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