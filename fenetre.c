#include "fenetre.h"

#include <stdlib.h>

fenetre_t* creerWin(int x, int y, int posX, int posY)
{
	fenetre_t* fen = (fenetre_t*) malloc(sizeof(fenetre_t));
	if (fen == NULL)
	{
		ncurses_stopper();
		fprintf(stderr, "Erreur, allocation fenetre_t\n");
		exit(EXIT_FAILURE);
	}
	fen->x = x;
	fen->y = y;
	fen->posX = posX;
	fen->posY = posY;
	return fen;
}

void delWin(fenetre_t** fen)
{
	delwin((*fen)->fenetre);
	free(*fen);
	*fen = NULL;
}
