typedef struct __palavra_arvore__ {
	char palavra[TAMANHO];
	int * ocorrenciasPalavra;
	int numOcorrenciasPalavra;
	struct __palavra_arvore__ * esquerda;
	struct __palavra_arvore__ * direita;
} PalavraArvore;

typedef struct {
	PalavraArvore * raiz;
} Arvore;

Arvore * criaArvore(void);
Arquivo * armazenaArquivoArvore(FILE * in, Arvore * arvore);
void buscaImprimeArvore(char x[TAMANHO], Arvore * arvore, Arquivo * inLinhas);
