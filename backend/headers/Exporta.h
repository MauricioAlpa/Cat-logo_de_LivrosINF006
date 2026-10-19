#ifndef EXPORTA_H
#define EXPORTA_H
#include <stdio.h>
#include <string.h>
#include <backend/headers/structs.h>

/* Mostra a lista no terminal. */
void imprimeLivros(livros lista[], int qtd);

/* Gera o arquivo dados.js lido pelo front end, com a lista
   ja ordenada das 4 formas pelas funcoes em C.
   Retorna 0 se deu certo e 1 se nao conseguiu criar o arquivo. */
int exportaWeb(livros lista[], int qtd, const char *caminho);

#endif
