# Indexador e Buscador de Palavras

Este programa realiza a indexação e busca de palavras através das estruturas de dados lista sequencial ordenada e árvore binária de busca.

## Como compilar

Digite `gcc main.c lista.c arvore.c auxiliarEstruturas.c -o out.out`;
O arquivo `out.out` será o executável.

## Como interagir

Execute o programa passando dois argumentos:

	1. O arquivo de texto que você deseja realizar a indexação e busca de palavras;
	2. A estrutura que você deseja utilizar ('lista' ou 'arvore').

	Exemplo:
	
		./out.out teste.txt arvore

Digite 'busca' seguido da palavra que você deseja buscar;
Digite 'fim' para finalizar o programa.	

## Como funciona a implementação

As linhas do arquivo de texto são armazenadas por completo em um arranjo.
As palavras do arquivo são armazenadas na estrutura escolhida pelo usuário. Junto às palavras são também armazenadas informações úteis, tais como o número de ocorrências de determinada palavra e os números das linhas dessas ocorrências. Estes últimos são guardados por meio de uma fila (os primeiros a entrarem são os primeiros a serem impressos).
A busca simplesmente faz uso das características de cada estrutura, imprimindo a palavra buscada, o número de ocorrências e as linhas de ocorrência na íntegra.

**Obs**: O programa tem funcionamento limitado a arquivos de texto com linhas de até mil caracteres.

