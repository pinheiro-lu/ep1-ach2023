#include <ctype.h>

#include "comum.h"

typedef struct __no_fila__ {
	int linhaOcorrencia;
	struct __no_fila__ * proximo;
} NoFila;

typedef struct {
	NoFila * primeiro;
	NoFila * ultimo;
} Fila;

void trocaHifenPorEspaco (char * frase);
void tiraPontuacao (char * palavra);
void converteParaMinuscula (char * palavra);
void insereFila (Fila * fila, int x);
void imprimeFila(Fila * fila, Arquivo * arquivo);
