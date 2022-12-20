#include <ctype.h>

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

void converteParaMinuscula(char palavra[TAMANHO]) {
	for (int i = 0; i < strlen(palavra); i++)
		palavra[i] = tolower(palavra[i]);
}

int buscaPalavra(Lista * lista, char palavra[TAMANHO]) {
	int ini = 0;
	int fim = lista -> numPalavras - 1;
	int meio;

	while (ini <= fim) {
		meio = (ini + fim) / 2;
		if (strcmp(lista -> palavras[meio].palavra, palavra) > 0) {
			fim = meio - 1;
			continue;
		}
		if (strcmp(lista -> palavras[meio].palavra, palavra) < 0) {
			ini = meio + 1;
			continue;
		}
		return meio;
	}

	return -1;
}

void insereFila(Fila * fila, int x) {
	NoFila * novo = (NoFila *) malloc(sizeof(NoFila));

	novo -> linhaOcorrencia = x;
	novo -> proximo = NULL;

	fila -> ultimo -> proximo = novo;
	fila -> ultimo = novo;
}

PalavraLista criaPalavra(char palavra[TAMANHO], Arquivo * arquivo) {
	PalavraLista p;

	strcpy(p.palavra, palavra);
	p.numOcorrenciasPalavra = 1;

	Fila * f = (Fila *) malloc(sizeof(Fila));

	NoFila * novo = (NoFila *) malloc(sizeof(NoFila));

	novo -> linhaOcorrencia = arquivo -> numLinhas - 1;
	novo -> proximo = NULL;

	f -> ultimo = f -> ultimo = novo;

	return p;
}

void insere (Lista * lista, char palavra[TAMANHO], Arquivo * arquivo) {
	converteParaMinuscula(palavra);

	int i = buscaPalavra(lista, palavra);

	if (i != -1) {
		lista -> palavras[i].numOcorrenciasPalavra++;
		insereFila(lista -> palavras[i].ocorrenciasPalavra, arquivo -> numLinhas-1);
		return;	
	}
		
	lista -> numPalavras++;
	lista -> palavras = (PalavraLista *) realloc(lista -> palavras, lista -> numPalavras * sizeof(PalavraLista));

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
