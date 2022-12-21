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
