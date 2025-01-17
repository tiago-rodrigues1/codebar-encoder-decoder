#include "./definitions.h"

void decompoeIdentificador(int identificador, int arr[TAM_IDENTIFICADOR]);
int compoeIdentificador(int arr[TAM_IDENTIFICADOR]);
int isDigitoVerificadorValido(int identificador);
int isIdentificadorValido(char *identificador);
void getBinario(CodigoDeBarras *c);
int getDecimal(CodigoDeBarras *c);
void printCodigoDeBarras(CodigoDeBarras *c);