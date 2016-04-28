#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "misc.h"
#include "funcoesTabuleiro.h"
#include "funcoesJogada.h"
#include "funcoesNavios.h"

int main(int argc, char **argv)
{
    int nLinhas, nColunas, i, j, aleatorio, aux;
    int nDestroyers, nPatrulhas, nPortaAvioes;
    jogador jogadores[NUM_JOGADORES];
    coordenada coord_ataque;

    printf("Entre com a dimensao do tabuleiro (quadrado): ");
    scanf("%d", &nLinhas);
    nColunas = nLinhas;

    do
    {
        printf("\n------------------\n");
        printf("Tamanho dos navios:\n");
        printf("Destroyer = 4, Patrulha = 2, Porta-avioes = 5\n");
        printf("------------------\n");
        printf("Entre com o numero de destroyers, patrulhas e porta avioes (separados por espaco): ");
        scanf("%d %d %d", &nDestroyers, &nPatrulhas, &nPortaAvioes);
        aux = checaInput(nDestroyers, nPatrulhas, nPortaAvioes, nLinhas, nColunas);
        if(aux == 0)
            printf("\nAVISO: o tabuleiro nao suporta a quantidade de navios desejada! Entre com novos valores.\n");
    }while(!aux);

    srand(time(NULL));

    // Inicializacao dos jogadores e posicionamento dos navios
    for(i = 0; i < NUM_JOGADORES; ++i)
    {
        jogadores[i].nLinhas = nLinhas;
        jogadores[i].nColunas = nColunas;
        jogadores[i].nDestroyers = nDestroyers;
        jogadores[i].nPatrulhas = nPatrulhas;
        jogadores[i].nPortaAvioes = nPortaAvioes;
        jogadores[i].totalNavios = nDestroyers + nPatrulhas + nPortaAvioes;
        jogadores[i].nNaviosDestruidos = 0;
        jogadores[i].ganhou = 0;
        jogadores[i].id_jogador = i;
        jogadores[i].destroyers = alocaDestroyers(jogadores[i].nDestroyers);
        jogadores[i].patrulhas = alocaPatrulhas(jogadores[i].nPatrulhas);
        jogadores[i].porta_avioes = alocaPortaAvioes(jogadores[i].nPortaAvioes);

        jogadores[i].tabuleiro = alocaTabuleiro(jogadores[i].nLinhas, jogadores[i].nColunas);
        if(jogadores[i].tabuleiro == NULL)
            return -1;

        jogadores[i].matrizControle = alocaMatriz(jogadores[i].nLinhas, jogadores[i].nColunas);
        if(jogadores[i].matrizControle == NULL)
            return -1;

        // Posicionamento dos navios
        if(i == 0)
        {
            do
            {
                printf("\nDeseja posicionar os navios de maneira aleatoria? (0 - NAO, 1 - SIM): ");
                scanf("%d", &aleatorio);
                if(aleatorio != 0 && aleatorio != 1)
                    printf("Opcao invalida!\n");

            }while(aleatorio != 1 && aleatorio != 0);
        }
        else
            aleatorio = 1; // o posicionamento dos navios da máquina é sempre feito de forma aleatória

        // Coloca os navios de maneira aleatoria no tabuleiro
        if(aleatorio)
        {
            printf("Posicionando destroyers do JOGADOR %d...\n", i);
            for(j = 0; j < jogadores[i].nDestroyers; ++j)
            {
                do
                {
                    jogadores[i].destroyers[j].coord_ini.x = rand() % jogadores[i].nLinhas;
                    jogadores[i].destroyers[j].coord_ini.y = rand() % jogadores[i].nColunas;
                    jogadores[i].destroyers[j].coord_fim.x = rand() % jogadores[i].nLinhas;
                    jogadores[i].destroyers[j].coord_fim.y = rand() % jogadores[i].nColunas;
                }while(posicionaNavio(jogadores[i].tabuleiro, jogadores[i].destroyers[j], jogadores[i].nLinhas, jogadores[i].nColunas) == -1);
            }

            printf("Posicionando patrulhas do JOGADOR %d...\n", i);
            for(j = 0; j < jogadores[i].nPatrulhas; ++j)
            {
                do
                {
                    jogadores[i].patrulhas[j].coord_ini.x = rand() % jogadores[i].nLinhas;
                    jogadores[i].patrulhas[j].coord_ini.y = rand() % jogadores[i].nColunas;
                    jogadores[i].patrulhas[j].coord_fim.x = rand() % jogadores[i].nLinhas;
                    jogadores[i].patrulhas[j].coord_fim.y = rand() % jogadores[i].nColunas;
                }while(posicionaNavio(jogadores[i].tabuleiro, jogadores[i].patrulhas[j], jogadores[i].nLinhas, jogadores[i].nColunas) == -1);
            }

            printf("Posicionando porta-avioes do JOGADOR %d...\n", i);
            for(j = 0; j < jogadores[i].nPortaAvioes; ++j)
            {
                do
                {
                    jogadores[i].porta_avioes[j].coord_ini.x = rand() % jogadores[i].nLinhas;
                    jogadores[i].porta_avioes[j].coord_ini.y = rand() % jogadores[i].nColunas;
                    jogadores[i].porta_avioes[j].coord_fim.x = rand() % jogadores[i].nLinhas;
                    jogadores[i].porta_avioes[j].coord_fim.y = rand() % jogadores[i].nColunas;
                }while(posicionaNavio(jogadores[i].tabuleiro, jogadores[i].porta_avioes[j], jogadores[i].nLinhas, jogadores[i].nColunas) == -1);
            }
        }
        else
        {
            printf("Posicionando destroyers do JOGADOR %d...\n", i);
            for(j = 0; j < jogadores[i].nDestroyers; ++j)
            {
                do
                {
                    printf("Entre com as coordenadas (X, Y) da proa (frente) do navio seperadas por espaco: ");
                    scanf("%d %d", &jogadores[i].destroyers[j].coord_ini.x, &jogadores[i].destroyers[j].coord_ini.y);

                    printf("Entre com as coordenadas (X, Y) da popa (traseira) do navio seperadas por espaco: ");
                    scanf("%d %d", &jogadores[i].destroyers[j].coord_fim.x, &jogadores[i].destroyers[j].coord_fim.y);
                }while(posicionaNavio(jogadores[i].tabuleiro, jogadores[i].destroyers[j], jogadores[i].nLinhas, jogadores[i].nColunas) == -1);
                if(i == 0)
                {
                    system(CLEAR);
                    imprimeTabuleiro(jogadores[i].tabuleiro, jogadores[i].nLinhas, jogadores[i].nColunas);
                }
            }

            printf("Posicionando patrulhas do JOGADOR %d...\n", i);;
            for(j = 0; j < jogadores[i].nPatrulhas; ++j)
            {
                do
                {
                    printf("Entre com as coordenadas (X, Y) da proa (frente) do navio seperadas por espaco: ");
                    scanf("%d %d", &jogadores[i].patrulhas[j].coord_ini.x, &jogadores[i].patrulhas[j].coord_ini.y);

                    printf("Entre com as coordenadas (X, Y) da popa (traseira) do navio seperadas por espaco: ");
                    scanf("%d %d", &jogadores[i].patrulhas[j].coord_fim.x, &jogadores[i].patrulhas[j].coord_fim.y);
                }while(posicionaNavio(jogadores[i].tabuleiro, jogadores[i].patrulhas[j], jogadores[i].nLinhas, jogadores[i].nColunas) == -1);
                if(i == 0)
                {
                    system(CLEAR);
                    imprimeTabuleiro(jogadores[i].tabuleiro, jogadores[i].nLinhas, jogadores[i].nColunas);
                }
            }


            printf("Posicionando porta-avioes do JOGADOR %d...\n", i);
            for(j = 0; j < jogadores[i].nPortaAvioes; ++j)
            {
                do
                {
                    printf("Entre com as coordenadas (X, Y) da proa (frente) do navio seperadas por espaco: ");
                    scanf("%d %d", &jogadores[i].porta_avioes[j].coord_ini.x, &jogadores[i].porta_avioes[j].coord_ini.y);

                    printf("Entre com as coordenadas (X, Y) da popa (traseira) do navio seperadas por espaco: ");
                    scanf("%d %d", &jogadores[i].porta_avioes[j].coord_fim.x, &jogadores[i].porta_avioes[j].coord_fim.y);
                }while(posicionaNavio(jogadores[i].tabuleiro, jogadores[i].porta_avioes[j], jogadores[i].nLinhas, jogadores[i].nColunas) == -1);
                if(i == 0)
                {
                    system(CLEAR);
                    imprimeTabuleiro(jogadores[i].tabuleiro, jogadores[i].nLinhas, jogadores[i].nColunas);
                }
            }
        }
    }

    i = 1;
    int controle;
    printf("\nO jogo vai comecar!\n");

    do
    {
        ++i;
        do
        {
            if(i % NUM_JOGADORES == 0)
            {
                //system(CLEAR);
                //coord_ataque.x = rand() % nLinhas;
                //coord_ataque.y = rand() % nColunas;
                printf("\n\nTabuleiro dos navios\n");
                imprimeTabuleiro(jogadores[JOG_1].tabuleiro, jogadores[JOG_1].nLinhas, jogadores[JOG_1].nColunas);
                printf("\n\nMatriz de controle\n");
                imprimeMatriz(jogadores[JOG_1].matrizControle, jogadores[JOG_1].nLinhas, jogadores[JOG_1].nColunas);
                printf("\n\n");
                printf("Digite as coordendas (X, Y) separadas por espaco do seu ataque: ");
                scanf("%d %d", &coord_ataque.x, &coord_ataque.y);
                printf("\n");
            }
            else
            {
                coord_ataque.x = rand() % nLinhas;
                coord_ataque.y = rand() % nColunas;
            }
            printf("Jogador %d:\n", (i % NUM_JOGADORES) + 1);
            controle = joga(&jogadores[i % NUM_JOGADORES], &jogadores[(i + 1) % NUM_JOGADORES], coord_ataque);
            printf("\n");
        }while(controle == -1);
    }
    while(controle != 0);

    if(jogadores[JOG_1].ganhou)
        printf("Voce ganhou.\n");
    else
        printf("Voce perdeu.\n");


    // Libera memoria
    for(i = 0; i < NUM_JOGADORES; ++i)
    {
        desalocaDestroyers(jogadores[i].destroyers);
        desalocaPatrulhas(jogadores[i].patrulhas);
        desalocaPortaAvioes(jogadores[i].porta_avioes);
        desalocaMatriz(jogadores[i].matrizControle, jogadores[i].nLinhas, jogadores[i].nColunas);
        desalocaTabuleiro(jogadores[i].tabuleiro, jogadores[i].nLinhas, jogadores[i].nColunas);
    }

    return 0;
}

