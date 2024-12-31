#include <stdio.h>
#include <string.h>
#include "include/codebar.h"
#include "include/pbm.h"


int main(void) {
    CodigoDeBarras c;

    c.identificador = 40170725;
    c.pxPorArea = 3;
    c.pxMargem = 8;
    c.pxAltura = 180;

    c.nome = "teste.pbm";
    
    char binario[TAM_CODIGO_DE_BARRAS];
    getBinario(c.identificador, binario);

    printf("%s\n", binario);

    strcpy(c.binario, binario);

    gerarPBM(&c);
    
    return 0;
}