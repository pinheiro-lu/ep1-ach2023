#include "comum.h"
#include "lista.h"

Lista * criaLista(void) {
	Lista * l = (Lista *) malloc(sizeof(Lista));
	l -> numPalavras = 0;
	l -> palavras = NULL;
	return l;
}

void trocaHifenPorEspaco (char * frase) {
	for (int i = 0; i < strlen(frase); i++) 
		if (frase[i] == '-')
			frase[i] = ' ';
}

void tiraPontuacao (char * palavra) {
	for (int i = 0; i < strlen(palavra); i++)
		if ((palavra[i] >= '!' && palavra[i] <= '/') || (palavra[i] >= ':' && palavra[i] <= '@') || (palavra[i] >= '[' && palavra[i] <= '`') || (palavra[i] >= '{' && palavra[i] <= '~')) {
			palavra[i] = '\0';
			return;
		}
}

void insere (Lista * lista, char palavra[TAMANHO], Arquivo * arquivo) {
	lista -> numPalavras++;

	lista -> palavras = (PalavraLista *) realloc(lista -> palavras, lista -> numPalavras * sizeof(PalavraLista));
	
	int i = buscaPalavra(lista, palavra);

	if (i != -1) {
		lista -> palavras[i].numOcorrenciasPalavra++;
		insereFila(lista -> palavras[i].ocorrenciasPalavra, arquivo -> numLinhas-1);
		return;	
	}


	for (i = lista -> numPalavras-1; i && strcmp(lista -> palavras[i].palavra, palavra) > 0; i--) {
		lista -> palavras[i] = lista -> palavras[i-1];
	}

	lista -> palavras[i] = criaPalavra(palavra, arquivo);
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
		
		trocaHifenPorEspaco(copia_ponteiro_linha);

		char * palavra;

		while (palavra = strsep(&copia_ponteiro_linha, " ")) {
			tiraPontuacao(palavra);
			if (palavra)
				insere(lista, palavra, a);
		}	
	}

	return a;
}

void buscaImprimeLista(char x[TAMANHO], Lista * lista, Arquivo * inLinhas) {
}
