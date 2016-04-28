#ifndef FUNCOESNAVIOS_H_INCLUDED
#define FUNCOESNAVIOS_H_INCLUDED

#include "misc.h"

navio* alocaPatrulhas(int);
navio* alocaDestroyers(int);
navio* alocaPortaAvioes(int);
void desalocaPatrulhas(navio*);
void desalocaDestroyers(navio*);
void desalocaPortaAvioes(navio*);
void danificaNavio(jogador*, char[TAM_NOME], int); // funcao para contabilizar dano no navio
int posicionaNavio(ponto**, navio, int, int); // funcao para posicionar o navio

#endif // FUNCOESNAVIOS_H_INCLUDED
