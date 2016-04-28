#include "funcoesNavios.h"

int id_navios = 0;

navio *alocaPatrulhas(int nPatrulhas)
{
    navio *patrulhas;
    int i;
    patrulhas = (navio*) malloc(nPatrulhas * sizeof(navio));
    if(patrulhas == NULL)
        return NULL;

    for(i = 0; i < nPatrulhas; ++i)
    {
        patrulhas[i].id = id_navios++;
        strcpy(patrulhas[i].nome, "Patrulha");
        patrulhas[i].tamanho = TAM_PATRULHA;
        patrulhas[i].pontos_atingidos = 0;

        patrulhas[i].coord_ini.x = 0;
        patrulhas[i].coord_ini.y = 0;
        patrulhas[i].coord_fim.x = 0;
        patrulhas[i].coord_fim.y = 0;
    }
    return patrulhas;
}

navio *alocaDestroyers(int nDestroyers)
{
    navio *destroyers;
    int i;
    destroyers = (navio*) malloc(nDestroyers * sizeof(navio));
    if(destroyers == NULL)
        return NULL;

    for(i = 0; i < nDestroyers; ++i)
    {
        destroyers[i].id = id_navios++;
        strcpy(destroyers[i].nome, "Destroyer");
        destroyers[i].tamanho = TAM_DESTROYER;
        destroyers[i].pontos_atingidos = 0;

        destroyers[i].coord_ini.x = 0;
        destroyers[i].coord_ini.y = 0;
        destroyers[i].coord_fim.x = 0;
        destroyers[i].coord_fim.y = 0;
    }
    return destroyers;
}

navio *alocaPortaAvioes(int nPortaAvioes)
{
    navio *porta_avioes;
    int i;
    porta_avioes = (navio*) malloc(nPortaAvioes * sizeof(navio));
    if(porta_avioes == NULL)
        return NULL;

    for(i = 0; i < nPortaAvioes; ++i)
    {
        porta_avioes[i].id = id_navios++;
        strcpy(porta_avioes[i].nome, "Porta-avioes");
        porta_avioes[i].tamanho = TAM_PORTAAVIOES;
        porta_avioes[i].pontos_atingidos = 0;

        porta_avioes[i].coord_ini.x = 0;
        porta_avioes[i].coord_ini.y = 0;
        porta_avioes[i].coord_fim.x = 0;
        porta_avioes[i].coord_fim.y = 0;
    }
    return porta_avioes;
}

void desalocaPatrulhas(navio *patrulhas)
{
    free(patrulhas);
}

void desalocaDestroyers(navio *destroyers)
{
    free(destroyers);
}

void desalocaPortaAvioes(navio *porta_avioes)
{
    free(porta_avioes);
}

int posicionaNavio(ponto **tab, navio nav, int nLinhas, int nColunas)
{
    int i, minimo, maximo;
    // Verifica se as coordenadas estao fora dos limites do tabuleiro
    if(nav.coord_ini.x < 0 || nav.coord_ini.x > nLinhas - 1
       || nav.coord_ini.y < 0 || nav.coord_fim.y > nColunas - 1)
            return -1;

    // Verifica se o navio esta na vertical ou horizontal
    if(nav.coord_ini.x == nav.coord_fim.x) // horizontal
    {
        // Define as coordenadas maxima e minima
        minimo = MIN(nav.coord_ini.y, nav.coord_fim.y);
        maximo = MAX(nav.coord_ini.y, nav.coord_fim.y);

        // Checa se ha navios ja posicionados no lugar
        for(i = minimo; i <= maximo; ++i)
            if(tab[nav.coord_ini.x][i].caractere_atual != '-')
                return -1;

        // Checa se as coordenadas conferem com o tamanho do navio
        if(maximo - minimo + 1 != nav.tamanho)
            return -1;

        // Posiciona navio
        for(i = minimo; i <= maximo; ++i)
        {
            if(strcmp(nav.nome, "Destroyer") == 0)
            {
                tab[nav.coord_ini.x][i].caractere_atual = 'D';
                tab[nav.coord_ini.x][i].id_navio = nav.id;
                strcpy(tab[nav.coord_ini.x][i].nome_navio, nav.nome);
            }
            else if(strcmp(nav.nome, "Patrulha") == 0)
            {
                tab[nav.coord_ini.x][i].caractere_atual = 'P';
                tab[nav.coord_ini.x][i].id_navio = nav.id;
                strcpy(tab[nav.coord_ini.x][i].nome_navio, nav.nome);
            }
            else // sobrou porta-avioes
            {
                tab[nav.coord_ini.x][i].caractere_atual = 'A';
                tab[nav.coord_ini.x][i].id_navio = nav.id;
                strcpy(tab[nav.coord_ini.x][i].nome_navio, nav.nome);
            }
        }
    }
    else if(nav.coord_ini.y == nav.coord_fim.y) // vertical
    {
        // Define as coordenadas maxima e minima
        minimo = MIN(nav.coord_ini.x, nav.coord_fim.x);
        maximo = MAX(nav.coord_ini.x, nav.coord_fim.x);

        // Checa se ha navios ja posicionados no lugar
        for(i = minimo; i <= maximo; ++i)
            if(tab[i][nav.coord_ini.y].caractere_atual != '-')
                return -1;

        // Checa se as coordenadas conferem com o tamanho do navio
        if(maximo - minimo + 1 != nav.tamanho)
            return -1;

        // Posiciona navio
        for(i = minimo; i <= maximo; ++i)
        {
            if(strcmp(nav.nome, "Destroyer") == 0)
            {
                tab[i][nav.coord_ini.y].caractere_atual = 'D';
                tab[i][nav.coord_ini.y].id_navio = nav.id;
                strcpy(tab[i][nav.coord_ini.y].nome_navio, nav.nome);
            }
            else if(strcmp(nav.nome, "Patrulha") == 0)
            {
                tab[i][nav.coord_ini.y].caractere_atual = 'P';
                tab[i][nav.coord_ini.y].id_navio = nav.id;
                strcpy(tab[i][nav.coord_ini.y].nome_navio, nav.nome);
            }
            else // sobrou porta-avioes
            {
                tab[i][nav.coord_ini.y].caractere_atual = 'A';
                tab[i][nav.coord_ini.y].id_navio = nav.id;
                strcpy(tab[i][nav.coord_ini.y].nome_navio, nav.nome);
            }
        }
    }
    else // coordenadas inconsistentes
        return -1;

    return 0;
}

void danificaNavio(jogador *jog, char nome[TAM_NOME], int id_navio)
{
    int i;
    if(strcmp(nome, "Destroyer") == 0)
    {
        for(i = 0; i < jog->nDestroyers; ++i)
        {
            if(jog->destroyers[i].id == id_navio) // achou o navio que vai sofrer dano
            {
                ++jog->destroyers[i].pontos_atingidos;
                if(jog->destroyers[i].pontos_atingidos == jog->destroyers[i].tamanho)
                    ++jog->nNaviosDestruidos;
            }
        }
    }
    else if(strcmp(nome, "Patrulha") == 0)
    {
        for(i = 0; i < jog->nPatrulhas; ++i)
        {
            if(jog->patrulhas[i].id == id_navio) // achou o navio que vai sofrer dano
            {
                ++jog->patrulhas[i].pontos_atingidos;
                if(jog->patrulhas[i].pontos_atingidos == jog->patrulhas[i].tamanho)
                    ++jog->nNaviosDestruidos;
            }
        }
    }
    else
    {
        for(i = 0; i < jog->nPortaAvioes; ++i)
        {
            if(jog->porta_avioes[i].id == id_navio) // achou o navio que vai sofrer dano
            {
                ++jog->porta_avioes[i].pontos_atingidos;
                if(jog->porta_avioes[i].pontos_atingidos == jog->porta_avioes[i].tamanho)
                    ++jog->nNaviosDestruidos;
            }
        }
    }
}
