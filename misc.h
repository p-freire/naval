#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAM_NOME 20
#define NUM_JOGADORES 2
#define TAM_DESTROYER 4
#define TAM_PORTAAVIOES 5
#define TAM_PATRULHA 2

#define JOG_1 0
#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif // _WIN32


// estrutura para coordenada
typedef struct
{
    int x, y;
} coordenada;

// estrutura para o navio
typedef struct
{
    int id;
    int tamanho;
    int pontos_atingidos;
    char nome[TAM_NOME];
    coordenada coord_ini;
    coordenada coord_fim;
} navio;

// estrutura de um ponto do tabuleiro (menor unidade do tabuleiro)
typedef struct
{
    char caractere_atual;
    char nome_navio[TAM_NOME];
    int id_navio;
} ponto;

// estrutura do jogador
typedef struct
{
    ponto **tabuleiro;
    char **matrizControle;
    navio *destroyers, *patrulhas, *porta_avioes;
    int nDestroyers, nPatrulhas, nPortaAvioes;
    int totalNavios, nNaviosDestruidos;
    int nLinhas, nColunas, ganhou, id_jogador;
} jogador;

// verifica se o input e valido
int checaInput(int, int, int, int, int);

#endif // MISC_H_INCLUDED
