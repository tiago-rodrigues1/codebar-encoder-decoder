#ifndef TAM_IDENTIFICADOR
#define TAM_IDENTIFICADOR 8
#endif

#ifndef TAM_CODIGO_DE_BARRAS
#define TAM_CODIGO_DE_BARRAS 67
#endif

#ifndef ANSI_COLOR_GREEN
#define ANSI_COLOR_GREEN "\x1b[32m"
#endif

#ifndef ANSI_COLOR_RED
#define ANSI_COLOR_RED "\x1b[31m"
#endif

#ifndef ANSI_COLOR_YELLOW
#define ANSI_COLOR_YELLOW "\x1b[33m"
#endif

#ifndef ANSI_COLOR_BLUE
#define ANSI_COLOR_BLUE "\x1b[34m"
#endif

#ifndef ANSI_COLOR_RESET
#define ANSI_COLOR_RESET "\x1b[0m"
#endif

#ifndef CODIGO_DE_BARRAS
#define CODIGO_DE_BARRAS
typedef struct codigo {
    int identificador;
    int pxMargem;
    int pxPorArea;
    int pxAltura;
    char *path;
    char binario[TAM_CODIGO_DE_BARRAS];
} CodigoDeBarras;
#endif