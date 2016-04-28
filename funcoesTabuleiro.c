#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesTabuleiro.h"
#include "misc.h"

ponto **alocaTabuleiro(int nLinhas, int nColunas)
{
    ponto **tab;
    int i = 0;

    tab = (ponto **) malloc(nLinhas * sizeof(ponto*));
    if(tab == NULL)
    {
        printf("Sem memoria suficiente!\n");
        return NULL;
    }
    else
    {
        for(i = 0; i < nLinhas; ++i)
        {
            tab[i] = (ponto*) malloc(nColunas * sizeof(ponto));
            if(tab[i] == NULL)
            {
                printf("Sem memoria suficiente!\n");
                return NULL;
            }
        }
    }
    // Se chegou ate aqui, o tabuleiro foi alocado
    // Basta preenche-lo agora
    preencheTabuleiro(tab, nLinhas, nColunas);
    return tab;
}

void desalocaTabuleiro(ponto **tab, int nLinhas, int nColunas)
{
    int i;
    for(i = 0; i < nLinhas; ++i)
        free(tab[i]);
    free(tab);
}

void preencheTabuleiro(ponto **tab, int nLinhas, int nColunas)
{
    int i, j;
    for(i = 0; i < nLinhas; ++i)
        for(j = 0; j < nColunas; ++j)
        {
            tab[i][j].caractere_atual = '-';
            tab[i][j].id_navio = -1;
            strcpy(tab[i][j].nome_navio, "");
        }
}

void imprimeTabuleiro(ponto **tab, int nLinhas, int nColunas)
{
    int i, j;
    printf("    ");
    for (i = 0; i < nColunas; ++i)
        printf("%d  ", i);
    printf("\n");

    for(i = 0; i < nLinhas; ++i)
    {
        i <= 9 ? printf("%d   %c", i, tab[i][0].caractere_atual) : printf("%d  %c", i, tab[i][0].caractere_atual);
        for(j = 1; j < nColunas; ++j)
            j <= 10 ? printf("  %c", tab[i][j].caractere_atual) : printf("   %c", tab[i][j].caractere_atual);
        printf("\n");
    }
}

char **alocaMatriz(int nLinhas, int nColunas)
{
    char **matriz;
    int i;

    matriz = (char**) malloc(nLinhas * sizeof(char*));
    if(matriz == NULL)
    {
        printf("Sem memoria suficiente!\n");
        return NULL;
    }
    for(i = 0; i < nLinhas; ++i)
    {
        matriz[i] = (char*) malloc(nColunas * sizeof(char));
        if(matriz[i] == NULL)
        {
            printf("Sem memoria suficiente!\n");
            return NULL;
        }
    }
    preencheMatriz(matriz, nLinhas, nColunas);
    return matriz;
}

void desalocaMatriz(char **matriz, int nLinhas, int nColunas)
{
    int i;
    for(i = 0; i < nLinhas; ++i)
        free(matriz[i]);
    free(matriz);
}

void preencheMatriz(char **matriz, int nLinhas, int nColunas)
{
    int i, j;
    for(i = 0; i < nLinhas; ++i)
        for(j = 0; j < nColunas; ++j)
            matriz[i][j] = '-';
}

void imprimeMatriz(char **matriz, int nLinhas, int nColunas)
{
    int i, j;
    printf("    ");
    for (i = 0; i < nColunas; ++i)
        printf("%d  ", i);
    printf("\n");

    for(i = 0; i < nLinhas; ++i)
    {
        i <= 9 ? printf("%d   %c", i, matriz[i][0]) : printf("%d  %c", i, matriz[i][0]);
        for(j = 1; j < nColunas; ++j)
            j <= 10 ? printf("  %c", matriz[i][j]) : printf("   %c", matriz[i][j]);
        printf("\n");
    }
}


void atualizaTabuleiro(ponto **tab, int nLinhas, int nColunas)
{
    // to do
}
