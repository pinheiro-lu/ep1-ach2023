/*
 * Este arquivo contém a funcionalidade principal do programa.
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "comum.h"
#include "lista.h"
#include "arvore.h"

#define LISTA 0
#define ARVORE 1

Arquivo * armazenaArquivo(FILE * in, Lista * lista, Arvore * arvore, int tipo) {
	if (tipo == LISTA) {
		lista = criaLista();
		return armazenaArquivoLista(in, lista);
	} 
	arvore = criaArvore();
	return armazenaArquivoArvore(in, arvore);
}

void imprimeInicio(char ** argv, Arquivo * inLinhas, int tipo, double tempo) {
	printf("Tipo de indice: '%s'\n", argv[2]);
	printf("Arquivo texto: '%s'\n", argv[1]);
	printf("Numero de linhas no arquivo: %d\n", inLinhas -> qtdLinhas);
	printf("Tempo para carregar o arquivo e construir o indice: %.f ms\n", tempo);
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
	
	time_t inicio = time(NULL);

	FILE * in = fopen(argv[1], "r");

	if (!in) return 3;

	Lista * lista;
	Arvore * arvore;
	Arquivo * inLinhas = armazenaArquivo(in, lista, arvore, tipo);
	
	time_t fim = time(NULL);

	imprimeInicio(argv, inLinhas, tipo, difftime(inicio, fim) * 1000);
	
	char entrada[TAMANHO + 1];

	while (true) {
		scanf("%s", entrada);
		if (!strcmp(entrada, "fim")) return 0;
	        if (strcmp(entrada, "busca")) {
			printf("Opcao invalida!\n> ");
			break;
		}
		scanf("%s", entrada);
		buscaImprime(entrada, lista, arvore, tipo, inLinhas);
	}	
			
	return 0;
}
