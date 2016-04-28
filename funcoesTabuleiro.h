#ifndef FUNCOESTABULEIRO_H_INCLUDED
#define FUNCOESTABULEIRO_H_INCLUDED
#include "misc.h"

// Protipos
ponto** alocaTabuleiro(int, int);
void desalocaTabuleiro(ponto**, int, int);
void preencheTabuleiro(ponto**, int, int); // inicializa o tabuleiro
void imprimeTabuleiro(ponto**, int, int); // imprime o tabuleiro

char** alocaMatriz(int, int);
void desalocaMatriz(char**, int, int);
void preencheMatriz(char**, int, int); // inicializa a matriz de controle
void imprimeMatriz(char**, int, int); // imprime a matriz de controle

void atualizaTabuleiro(ponto**, int, int);

#endif // FUNCOESTABULEIRO_H_INCLUDED
