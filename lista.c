//#include "comum.h"
#include "auxiliarEstruturas.h"
#include "lista.h"
#include "arvore.h"

Lista * criaLista(void) {
	Lista * l = (Lista *) malloc(sizeof(Lista));
	l -> numPalavras = 0;
	l -> palavras = NULL;
	return l;
}

int buscaPalavraLista(Lista * lista, char palavra[TAMANHO]) {
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

PalavraLista criaPalavraLista(char palavra[TAMANHO], Arquivo * arquivo) {
	PalavraLista p;

	strcpy(p.palavra, palavra);
	p.numOcorrenciasPalavra = 1;

	Fila * f = (Fila *) malloc(sizeof(Fila));

	NoFila * novo = (NoFila *) malloc(sizeof(NoFila));

	novo -> linhaOcorrencia = arquivo -> numLinhas - 1;
	novo -> proximo = NULL;

	f -> ultimo = f -> primeiro = novo;
	p.ocorrenciasPalavra = f;
	return p;
}

void insereLista (Lista * lista, char palavra[TAMANHO], Arquivo * arquivo) {
	converteParaMinuscula(palavra);

	int i = buscaPalavraLista(lista, palavra);

	if (i != -1) {
		lista -> palavras[i].numOcorrenciasPalavra++;
		insereFila(lista -> palavras[i].ocorrenciasPalavra, arquivo -> numLinhas-1);
		return;	
	}
		
	lista -> numPalavras++;
	lista -> palavras = (PalavraLista *) realloc(lista -> palavras, lista -> numPalavras * sizeof(PalavraLista));

	for (i = lista -> numPalavras-1; i && strcmp(lista -> palavras[i-1].palavra, palavra) > 0; i--) {
		lista -> palavras[i] = lista -> palavras[i-1];
	}

	lista -> palavras[i] = criaPalavraLista(palavra, arquivo);
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
			if (palavra[0] != '\0')
				insereLista(lista, palavra, a);
		}	
	}

	return a;
}

void buscaImprimeLista(char x[TAMANHO], Lista * lista, Arquivo * inLinhas) {
	clock_t inicio = clock();
	
	converteParaMinuscula(x);
	int indice = buscaPalavraLista(lista, x);

	clock_t fim = clock();

	if (indice == -1) {
		printf("Palavra '%s' nao encontrada.\n", x);
	} else {
		printf("Existem %d ocorr??ncias da palavra '%s' na(s) seguinte(s) linha(s):\n", lista -> palavras[indice].numOcorrenciasPalavra, x);
		imprimeFila(lista->palavras[indice].ocorrenciasPalavra, inLinhas);
	}

	printf("Tempo de busca: %.f ms\n> ", 1000.0 * (fim - inicio) / CLOCKS_PER_SEC); 
}
