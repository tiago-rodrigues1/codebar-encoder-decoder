#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "include/codebar.h"
#define TAM 8

int main(){
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

//verificar se tem a quantidade certa de caracteres (8)




//verificar se está lendo ok
    //printf("O código é esse: %s", codigo);

return 0;
}