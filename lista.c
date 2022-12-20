#include "comum.h"
#include "lista.h"

Lista * criaLista(void) {
	Lista * l = (Lista *) malloc(sizeof(Lista));
	l -> numPalavras = 0;
	return l;
}

Arquivo * armazenaArquivoLista(FILE * in, Lista * lista) {
	Arquivo * a = (Arquivo *) malloc(sizeof(Arquivo));

	a -> numLinhas = 0;
	a -> linhasArquivo = NULL;

	char linha[TAMANHO];

	while (fgets(linha, TAMANHO, in)) {
		char * quebra_de_linha;

		if (quebra_de_linha = strrchr(linha, '\n')) *quebra_de_linha = '\0';
		a -> numLinhas++;
		a -> linhasArquivo = (char **) realloc(a -> linhasArquivo, a -> numLinhas * sizeof(char *));
		a -> linhasArquivo[a -> numLinhas-1] = (char *) malloc(TAMANHO);
		strcpy(a -> linhasArquivo[a -> numLinhas-1], linha);

		char * copia_ponteiro_linha = linha;

	}

	return a;
}

void buscaImprimeLista(char x[TAMANHO], Lista * lista, Arquivo * inLinhas) {
}
