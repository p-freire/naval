#include "funcoesJogada.h"
#include "funcoesNavios.h"

// funcao para realizar a jogada
int joga(jogador *jogadorDaVez, jogador *oponente, coordenada coord)
{
    // verifica se as coordenadas sao validas
    if(coord.x > jogadorDaVez->nLinhas - 1 || coord.x < 0
       || coord.y > jogadorDaVez->nColunas - 1 || coord.y < 0
       || jogadorDaVez->matrizControle[coord.x][coord.y] != '-')
    {
        printf("Coordenadas invalidas ou ja utilizadas.\n");
        return -1;
    }
    else
    {
        if(oponente->tabuleiro[coord.x][coord.y].caractere_atual == '-') // tiro na agua
        {
            // atualiza tabuleiro e matriz
            jogadorDaVez->matrizControle[coord.x][coord.y] = 'X';
            oponente->tabuleiro[coord.x][coord.y].caractere_atual = 'X';
            printf("Tiro na agua.\n");
            return 1;
        }
        else // acertou algum navio
        {
            int controleNaviosDestruidos = oponente->nNaviosDestruidos;
            jogadorDaVez->matrizControle[coord.x][coord.y] = 'O';
            oponente->tabuleiro[coord.x][coord.y].caractere_atual = 'O';
            danificaNavio(oponente, oponente->tabuleiro[coord.x][coord.y].nome_navio, oponente->tabuleiro[coord.x][coord.y].id_navio);

            // se todos os navios foram destruidos, o jogo acabou
            if(oponente->nNaviosDestruidos == oponente->totalNavios)
            {
                printf("FIM DE JOGO!\n");
                jogadorDaVez->ganhou = 1;
                return 0;
            }
            else if(oponente->nNaviosDestruidos > controleNaviosDestruidos) // verifica se o navio foi destruido
                printf("Navio destruido! Falta(m) agora %d navio(s).\n", oponente->totalNavios - oponente->nNaviosDestruidos);
            else // navio foi atingido, mas nao destruido
                printf("Navio atingido! Coordenada: %d %d\n", coord.x, coord.y);

            return 1;
        }
    }
}
