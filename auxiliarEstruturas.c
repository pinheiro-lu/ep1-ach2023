#include "auxiliarEstruturas.h"

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

void converteParaMinuscula (char * palavra) {
	for (int i = 0; i < strlen(palavra); i++)
		palavra[i] = tolower(palavra[i]);
}

void insereFila (Fila * fila, int x) {
	NoFila * novo = (NoFila *) malloc(sizeof(NoFila));

	novo -> linhaOcorrencia = x;
	novo -> proximo = NULL;

	fila -> ultimo -> proximo = novo;
	fila -> ultimo = novo;
}

void imprimeFila(Fila * fila, Arquivo * arquivo) {
	NoFila * no = fila -> primeiro;
	int linhaAnt = -1;
	while(no) {
		if (linhaAnt != no->linhaOcorrencia)
			printf("%05d: %s\n", no->linhaOcorrencia+1, arquivo->linhasArquivo[no->linhaOcorrencia]);
		linhaAnt = no->linhaOcorrencia;
		no = no->proximo;
	}
}
