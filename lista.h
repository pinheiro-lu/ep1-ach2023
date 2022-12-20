#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char palavra[TAMANHO];
	int * ocorrenciasPalavra;
	int numOcorrenciasPalavra;
} PalavraLista;

typedef struct {
	PalavraLista * palavras;
	int numPalavras;
} Lista;

Lista * criaLista(void);
Arquivo * armazenaArquivoLista(FILE * in, Lista * lista);
void buscaImprimeLista(char x[TAMANHO], Lista * lista, Arquivo * inLinhas);
