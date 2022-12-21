#include "comum.h"
#include "arvore.h"
#include "auxiliarEstruturas.h"

Arvore * criaArvore(void) {
	Arvore * a = (Arvore *) malloc(sizeof(Arvore));
	
	return a;
}

Arquivo * armazenaArquivoArvore(FILE * in, Arvore * arvore) {
	Arquivo * a = (Arquivo *) malloc(sizeof(Arquivo));

	a -> numLinhas = 0;
	a -> linhasArquivo = NULL;

	char linha[TAMANHO];

	while(fgets(linha, TAMANHO, in)) {
		char * quebra_de_linha;

		if (quebra_de_linha = strrchr(linha, '\n')) *quebra_de_linha = '\0';
		a -> numLinhas++;
		a -> linhasArquivo = (char **) realloc(a->linhasArquivo, a->numLinhas * sizeof(char *));
		a -> linhasArquivo[a -> numLinhas-1] = (char *) malloc(TAMANHO);

		char * copia_ponteiro_linha = linha;

		trocaHifenPorEspaco(copia_ponteiro_linha);

		char * palavra;

		while (palavra = strsep(&copia_ponteiro_linha, " ")) {
			tiraPontuacao(palavra);
			if (palavra[0])
				insere(arvore, palavra, a);
		}
	}

	return a;
}
