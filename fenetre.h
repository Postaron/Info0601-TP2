#ifndef FENETRE_H_
#define FENETRE_H_

#include "ncurses.h"

typedef struct
{
	WINDOW* fenetre;
	int x, y, posX, posY;
} fenetre_t;

fenetre_t* creerWin(int x, int y, int posX, int posY);
void delWin(fenetre_t** fen);

#endif /* FENETRE_H_ */
