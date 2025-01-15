#include "./definitions.h"

int isDigitoVerificadorValido(int identificador);
int isIdentificadorValido(char *identificador);
void getBinario(int identificador, char stringBinario[TAM_CODIGO_DE_BARRAS]);
int getDecimal (char stringBinario[TAM_CODIGO_DE_BARRAS]);