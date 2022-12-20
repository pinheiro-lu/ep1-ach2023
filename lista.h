#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __no_fila__ {
	int linhaOcorrencia;
	struct __no_fila__ * proximo;
} NoFila;

typedef struct {
	NoFila * primeiro;
	NoFila * ultimo;
} Fila;

typedef struct {
	char palavra[TAMANHO];
	Fila * ocorrenciasPalavra;
	int numOcorrenciasPalavra;
} PalavraLista;

typedef struct {
	PalavraLista * palavras;
	int numPalavras;
} Lista;

Lista * criaLista(void);
Arquivo * armazenaArquivoLista(FILE * in, Lista * lista);
void buscaImprimeLista(char x[TAMANHO], Lista * lista, Arquivo * inLinhas);
