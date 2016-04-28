all: naval

naval: funcoesNavios.o funcoesJogada.o funcoesTabuleiro.o misc.o main.o
	gcc funcoesNavios.o funcoesJogada.o funcoesTabuleiro.o misc.o main.o -o naval

funcoesNavios.o: funcoesNavios.c
	gcc -c funcoesNavios.c

funcoesJogada.o: funcoesJogada.c
	gcc -c funcoesJogada.c

funcoesTabuleiro.o: funcoesTabuleiro.c
	gcc -c funcoesTabuleiro.c

misc.o: misc.c
	gcc -c misc.c

main.o: main.c
	gcc -c main.c

clean:
	rm -f *.o naval