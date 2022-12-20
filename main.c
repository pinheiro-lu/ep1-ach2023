/*
 * Este arquivo contém a funcionalidade principal do programa.
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LISTA 0
#define ARVORE 1
#define TAMANHO 1000

int main(int argc, char ** argv) {
	if (argc != 3)
		return 1;

	int tipo;

	if (!strcmp(argv[2], "lista"))
		tipo = LISTA;
	else if (!strcmp(argv[2], "arvore"))
		tipo = ARVORE;
	else return 2;

	FILE * in = fopen(argv[1], "r");

	if (!in)
		return 3;

	Lista * lista;
	Arvore * arvore;
	char ** inLinhas = armazenaArquivo(in, lista, arvore, tipo);

	printInicio(argv);
	
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
