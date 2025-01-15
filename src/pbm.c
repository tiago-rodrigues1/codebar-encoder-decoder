#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/definitions.h"
#include "../include/pbm.h"

int arquivoExiste(char *path) {
    FILE *arquivo;
    arquivo = fopen(path, "r");

    int existe = arquivo != NULL;

    if (existe) {
        fclose(arquivo);
    }
    
    return existe;
}

int pbmValido(FILE *arquivo, int *ptrLargura, int *ptrAltura) {
    char tipo[3];
    int largura, altura;

    int isValido = 1;

    if (fscanf(arquivo, "%2s", tipo) != 1 || strcmp(tipo, "P1") != 0) {
        isValido = 0;
    }

    if (fscanf(arquivo, "%d %d", &largura, &altura) != 2 || largura == 0 || altura == 0) {
        isValido = 0;
    }

    *ptrLargura = largura;
	*ptrAltura = altura;
    
    return isValido;
}


void gerarPBM(CodigoDeBarras *codigo) {
    int larguraCodigo = codigo->pxPorArea * TAM_CODIGO_DE_BARRAS;
    int larguraTotal = larguraCodigo + (2 * codigo->pxMargem);
    int alturaTotal = codigo->pxAltura + (2 * codigo->pxMargem);

    FILE *pbm;
    pbm = fopen(codigo->nome, "w");

    fprintf(pbm, "%s\n%d %d\n", "P1", larguraTotal, alturaTotal);

    for (int i = 0; i < alturaTotal; i++) {
        char *margem;
        margem = calloc(larguraTotal, sizeof(char));

        if (i < codigo->pxMargem || i >= codigo->pxAltura + codigo->pxMargem) {
            memset(margem, '0', larguraTotal);

            fprintf(pbm, "%s\n", margem);
        } else {
            memset(margem, '0', codigo->pxMargem);

            fprintf(pbm, "%s", margem);
            
            for (int j = 0; j < TAM_CODIGO_DE_BARRAS; j++) {
                char *buffer;
                buffer = calloc(codigo->pxPorArea, sizeof(char));

                memset(buffer, codigo->binario[j], codigo->pxPorArea);
               
                fprintf(pbm, "%s", buffer);
            }

            fprintf(pbm, "%s\n", margem);
        }
        
    }

    fclose(pbm);
}

void extrairCodigoBinario(char *path, char stringBinario[TAM_CODIGO_DE_BARRAS]) {
    FILE *arquivo;
    arquivo = fopen(path, "r");

    int larguraTotal = 0, alturaTotal = 0;

    if (pbmValido(arquivo, &larguraTotal, &alturaTotal) == 0) {
        printf("[ERRO] %s não é um arquivo PBM válido", path);
		exit(-1);
    }

    int margem = (larguraTotal % TAM_CODIGO_DE_BARRAS) / 2;
    int larguraReal = larguraTotal - 2 * margem;
	int alturaReal = alturaTotal - 2 * margem;
    int pxPorArea = (larguraReal) / TAM_CODIGO_DE_BARRAS;
    int offset = (larguraTotal + 1) * margem + 1;

    char linha[larguraTotal + 1];
    
    fseek(arquivo, offset, SEEK_CUR);
    fgets(linha, larguraTotal + 1, arquivo);

    char *binario = malloc(sizeof(char));
    int contador = 0;

    for (int i = margem; i + pxPorArea <= larguraTotal - margem; i += pxPorArea) {
        binario[contador] = linha[i];
        contador += 1;
        binario = realloc(binario, sizeof(char) * (contador + 1));
    }

    binario[contador] = '\0';

	if (temCodigoDeBarras(arquivo, linha, binario,larguraTotal, alturaReal) == 0) {
		printf("[ERRO] %s não possui um código de barras em seu conteúdo", path);
		fclose(arquivo);
		exit(-1);
	}

    fclose(arquivo);

    strcpy(stringBinario, binario);

    free(binario);
} 
    
int temCodigoDeBarras(FILE *arquivo, char *linhaBase, char stringBinario[TAM_CODIGO_DE_BARRAS], int larguraTotal, int alturaReal) {  
    char linhaAtual[larguraTotal + 2];

	fgetc(arquivo);
    for (int i = 0; i < alturaReal - 1; i++) {
		fgets(linhaAtual, larguraTotal + 1, arquivo);
		fgetc(arquivo);

		if (strcmp(linhaAtual, linhaBase) != 0) {
			printf("a)%s\nb)%s\n", linhaBase, linhaAtual);
			printf("%d\n", i);
			return 0;
		}
    }

	int temMarcadorInicial = stringBinario[0] == '1' && stringBinario[1] == '0' && stringBinario[2] == '1';
	int temMarcadorFinal = stringBinario[TAM_CODIGO_DE_BARRAS - 1] == '1' && stringBinario[TAM_CODIGO_DE_BARRAS - 2] == '0' && stringBinario[TAM_CODIGO_DE_BARRAS - 3] == '1';

	int posicaoMarcadorCentral = (TAM_CODIGO_DE_BARRAS - 1) / 2;
	int temMarcadorCentral = stringBinario[posicaoMarcadorCentral - 2] == '0' && stringBinario[posicaoMarcadorCentral - 1] == '1' &&
		stringBinario[posicaoMarcadorCentral] == '0' && stringBinario[posicaoMarcadorCentral + 1] == '1' && stringBinario[posicaoMarcadorCentral + 2] == '0';

	if (temMarcadorInicial == 0 || temMarcadorFinal == 0 || temMarcadorCentral == 0) {
		return 0;
	}

	return 1;
}

    