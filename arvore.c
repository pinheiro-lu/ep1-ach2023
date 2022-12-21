//#include "comum.h"
#include "auxiliarEstruturas.h"
#include "arvore.h"

Arvore * criaArvore(void) {
	Arvore * a = (Arvore *) malloc(sizeof(Arvore));
	a->raiz = NULL;
	return a;
}

PalavraArvore * criaPalavraArvore(char palavra[TAMANHO], Arquivo * arquivo) {
	PalavraArvore * p = (PalavraArvore *) malloc(sizeof(PalavraArvore));
	strcpy(p->palavra, palavra);
	p->numOcorrenciasPalavra = 1;

	Fila * f = (Fila *) malloc(sizeof(Fila));

	NoFila * novo = (NoFila *) malloc(sizeof(NoFila));

	novo -> linhaOcorrencia = arquivo -> numLinhas - 1;
	novo -> proximo = NULL;

	f -> ultimo = f -> primeiro = novo;
	p -> ocorrenciasPalavra = f;

	p -> esquerda = NULL;
	p -> direita = NULL;

	return p;
}

void insereRec(PalavraArvore * raiz, char palavra[TAMANHO], Arquivo * arquivo) {
	if(!strcmp(palavra, raiz->palavra)) {
		raiz->numOcorrenciasPalavra++;
		insereFila(raiz -> ocorrenciasPalavra, arquivo -> numLinhas-1);
		return;
	}
	if(strcmp(palavra, raiz->palavra) < 0)
		if (raiz->esquerda) insereRec(raiz->esquerda, palavra, arquivo);
		else raiz->esquerda = criaPalavraArvore(palavra, arquivo);
	else
		if(raiz->direita) insereRec(raiz->direita, palavra, arquivo);
		else raiz->direita = criaPalavraArvore(palavra, arquivo);
}

void insereArvore (Arvore * arvore, char palavra[TAMANHO], Arquivo * arquivo) {
	converteParaMinuscula(palavra);

	if (arvore -> raiz) insereRec(arvore->raiz, palavra, arquivo);
	else {
		PalavraArvore * p = criaPalavraArvore(palavra, arquivo);
		arvore -> raiz = p;
	}
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
		strcpy(a->linhasArquivo[a->numLinhas-1], linha);

		char * copia_ponteiro_linha = linha;

		trocaHifenPorEspaco(copia_ponteiro_linha);

		char * palavra;

		while (palavra = strsep(&copia_ponteiro_linha, " ")) {
			tiraPontuacao(palavra);
			if (palavra[0])
				insereArvore(arvore, palavra, a);
		}
	}

	return a;
}

PalavraArvore * buscaPalavraArvoreRec(PalavraArvore * raiz, char palavra[TAMANHO]) {
	if (!raiz) return NULL;
	if (!strcmp(raiz->palavra, palavra)) return raiz;
	if (strcmp(raiz->palavra, palavra) > 0) return buscaPalavraArvoreRec(raiz->esquerda, palavra);
	return buscaPalavraArvoreRec(raiz->direita, palavra);
}

PalavraArvore * buscaPalavraArvore(Arvore * arvore, char palavra[TAMANHO]) {
	return buscaPalavraArvoreRec(arvore->raiz, palavra);
}

void buscaImprimeArvore(char x[TAMANHO], Arvore * arvore, Arquivo * inLinhas) {
	clock_t inicio = clock();

	converteParaMinuscula(x);
	PalavraArvore * palavraBuscada = buscaPalavraArvore(arvore, x);

	clock_t fim = clock();

	if (!palavraBuscada)
		printf("Palavra '%s' nao encontrada.\n", x);
	else {
		printf("Existem %d ocorrências da palavra '%s' na(s) seguinte(s) linha(s):\n", palavraBuscada -> numOcorrenciasPalavra, x);
	       imprimeFila(palavraBuscada->ocorrenciasPalavra, inLinhas);
	}
	
	printf("Tempo de busca: %.f ms\n> ", 1000.0 * (fim - inicio) / CLOCKS_PER_SEC);	
}
