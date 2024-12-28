#ifndef TAM_VERIFICADOR
#define TAM_VERIFICADOR 8
#endif

#ifndef TAM_CODIGO_DE_BARRAS
#define TAM_CODIGO_DE_BARRAS 67
#endif

int isDigitoVerificadorValido(int identificador);
void getBinario(int identificador, char stringBinario[TAM_CODIGO_DE_BARRAS]);