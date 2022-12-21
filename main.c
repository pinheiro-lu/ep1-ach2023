/*
 * Este arquivo contém a funcionalidade principal do programa.
 */
#include <stdbool.h>

//#include "comum.h"
#include "auxiliarEstruturas.h"
#include "lista.h"
#include "arvore.h"

#define LISTA 0
#define ARVORE 1

Arquivo * armazenaArquivo(FILE * in, Lista * lista, Arvore * arvore, int tipo) {
	if (tipo == LISTA) {
		return armazenaArquivoLista(in, lista);
	} 
	return armazenaArquivoArvore(in, arvore);
}

void imprimeInicio(char ** argv, Arquivo * inLinhas, int tipo, double tempo) {
	printf("Tipo de indice: '%s'\n", argv[2]);
	printf("Arquivo texto: '%s'\n", argv[1]);
	printf("Numero de linhas no arquivo: %d\n", inLinhas -> numLinhas);
	printf("Tempo para carregar o arquivo e construir o indice: %.f ms\n", tempo);
	printf("> ");
}

void buscaImprime(char x[TAMANHO], Lista * lista, Arvore * arvore, int tipo, Arquivo * inLinhas) {
	if (tipo == LISTA) buscaImprimeLista(x, lista, inLinhas);
	else buscaImprimeArvore(x, arvore, inLinhas);
}

int main(int argc, char ** argv) {
	if (argc != 3)
		return 1;

	int tipo;

	if (!strcmp(argv[2], "lista"))
		tipo = LISTA;
	else if (!strcmp(argv[2], "arvore"))
		tipo = ARVORE;
	else return 2;
	
	clock_t inicio = clock();

	FILE * in = fopen(argv[1], "r");

	if (!in) return 3;

	Lista * lista = criaLista();
	Arvore * arvore = criaArvore();
	Arquivo * inLinhas = armazenaArquivo(in, lista, arvore, tipo);
	
	clock_t fim = clock();

	imprimeInicio(argv, inLinhas, tipo, (double) 1000.0*(fim-inicio)/CLOCKS_PER_SEC);
	
	char * entrada = NULL;

	while (true) {
		long unsigned int tam = TAMANHO;
		getline(&entrada, &tam, stdin);
		if (!strcmp(entrada, "fim\n")) return 0;
	        if (strncmp(entrada, "busca", strlen("busca"))) {
			printf("Opcao invalida!\n> ");
			continue;
		}
		entrada = &entrada[strlen("busca ")];
		entrada[strlen(entrada)-1] = '\0';
		buscaImprime(entrada, lista, arvore, tipo, inLinhas);
	}	
			
	return 0;
}
