#include "misc.h"

// verifica se o input e valido
int checaInput(int nDestroyers, int nPatrulhas, int nPortaAvioes, int nLinhas, int nColunas)
{
    int espacoNavios = (nDestroyers * TAM_DESTROYER) + (nPatrulhas * TAM_PATRULHA) + (nPortaAvioes * TAM_PORTAAVIOES);
    int maior = MAX(nLinhas, nColunas);
    if(espacoNavios < nLinhas * nColunas) // se a area dos navios cabe na area do tabuleiro
    {
        if(nPortaAvioes) // se ha porta-avioes, verifica se ele cabe no tabuleiro
        {
            if(TAM_PORTAAVIOES > maior || nDestroyers < 0 || nPatrulhas < 0)
                return 0;
        }
        else if(nDestroyers) // se nao ha porta-avioes, mas ha destroyers, verifica se ele cabe no tabuleiro
        {
            if(TAM_DESTROYER > maior || nPortaAvioes < 0 || nPatrulhas < 0)
                return 0;
        }
        else if(nPatrulhas) // se ha apenas patrulas, verifica se cabe no tabuleiro
        {
            if(TAM_PATRULHA > maior || nDestroyers < 0 || nPortaAvioes < 0)
                return 0;
        }
        else
            return 0;
        return 1; // se o input esta correto, retorna true (1)
    }
    else if(espacoNavios == nLinhas * nColunas)
    {
        printf("O tabuleiro vai ficar tomado de navios; escolha quantidades menores\n");
        return 0;
    }
    else
        return 0;
}
