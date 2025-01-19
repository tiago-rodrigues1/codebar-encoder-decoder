#include "./definitions.h"

void decompoeIdentificador(int identificador, int arr[TAM_IDENTIFICADOR]);
int compoeIdentificador(int arr[TAM_IDENTIFICADOR]);
int isDigitoVerificadorValido(int identificador);
int isIdentificadorValido(char *identificador); //verifica o identificador(codigo) que o usuaario passa, ve se tem alguem caractere nao numero e chama a função acima pra ver se o ultimo digito é valido
void getBinario(CodigoDeBarras *c); //converte decimal pra binario
int getDecimal(CodigoDeBarras *c);
void printCodigoDeBarras(CodigoDeBarras *c);