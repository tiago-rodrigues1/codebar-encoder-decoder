#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TAM 8

#include "include/codebar.h"
#include "include/pbm.h"


int main(void) {
    char codigo[TAM];
    int i;
//pedir codigo
    printf("Digite o código: \n ");
    scanf("%s", codigo);

//verificar se tem algo q n é numero

    for (i = 0; codigo[i] != '\0'; i++) {
        if (!isdigit(codigo[i])) { 
            printf("Há caractere inválido");          
            break;                 
        }
    }
//verificar se está lendo ok
    //printf("O código é esse: %s", codigo);
    
//verificar se tem a quantidade certa de caracteres (8)
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