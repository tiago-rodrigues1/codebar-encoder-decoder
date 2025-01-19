#include "./definitions.h"

int arquivoExiste(char *path); 
int pbmValido(FILE *arquivo, int *ptrLargura, int *ptrAltura); //verifica se tem o P1, a largura e a altura
int temCodigoDeBarras(FILE *arquivo, char *linhaBase, char stringBinario[TAM_CODIGO_DE_BARRAS], int larguraTotal, int alturaReal); //verifica se algo tem algo que quebra
void gerarPBM(CodigoDeBarras *codigo);
void extraiBinarioDoPBM(CodigoDeBarras *c); //le o arquivo praa pegar a cadeia binario que futuramente vai ser convertida parta decimal