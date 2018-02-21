#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "map.h"
#include "file.h"
#include "ncurses.h"

/* file_path x y */
int main(int argc, char *argv[])
{
	int x, y, carac, bouton;
	WINDOW* fenetre = NULL, *jeu = NULL;
	map_t* map = NULL;
	file_t* file = NULL;
	if (argc == 4)
	{
		x = atoi(argv[2]), y = atoi(argv[3]);
		file = openFile(argv[1]);
		if (y > x)
		{
			int tmp = x;
			x = y;
			y = tmp;
		}
		map = creerMap((unsigned int) x, (unsigned int) y);
	}
	else if (argc == 2)
	{
		file = openFile(argv[1]);
		loadMap(&map, file);
	}
	else
	{
		fprintf(stderr,
				"Pas assez d'argument : un nom de fichier est nécessaire.\n");
		exit(EXIT_FAILURE);
	}

	ncurses_initialiser(), ncurses_couleurs(), ncurses_souris();
	if (LINES < (y + 3) || COLS < (x + 10))
	{
		ncurses_stopper();
		fprintf(stderr, "Erreur, terminal trop petit\n");
		exit(EXIT_FAILURE);
	}
	if ((fenetre = newwin(0, 0, 0, 0)) == NULL)
	{
		ncurses_stopper();
		fprintf(stderr, "Echec création de la fenêtre principale.\n");
		exit(EXIT_FAILURE);
	}
	if ((jeu = subwin(fenetre, y, x, (LINES - y) / 2, (COLS - x) / 2)) == NULL)
	{
		ncurses_stopper();
		fprintf(stderr, "Echec de la création de la fenêtre de l'éditeur.\n");
		exit(EXIT_FAILURE);
	}
	scrollok(jeu, TRUE);
	box(jeu, 0, 0);
	printw(
			"F1 pour l'aide, F2 pour quitter. F3 pour passer en mode suppression.\n");
	mvprintw(getbegy(jeu) - 1, getbegx(jeu), "Jeu");
	wrefresh(fenetre);
	wrefresh(jeu);
	while ((carac = getch()) != KEY_F(2))
	{
		bool delete;
		if (carac == KEY_F(3))
			delete = true;
		else
			delete = false;
		if ((carac == KEY_MOUSE) && (souris_getpos(&x, &y, &bouton) == OK))
		{
			int begx = getbegx(jeu), begy = getbegy(jeu);
			if (bouton & BUTTON1_CLICKED)
			{
				if (((begx <= x) && (x <= (begx + getmaxx(jeu))))
						&& (((begy <= y) && (y <= (begy + getmaxy(jeu))))))
				{
					if (delete)
					{
						mvdelch(y, x);
						delBomb(x, y, map);
					}
					else
					{
						attroff(COLOR_PAIR(3));
						attron(COLOR_PAIR(2));
						mvprintw(y, x, "X");
						x -= begx, y -= begy;
						addBomb(x, y, map);
					}
				}
			}
			if (bouton & BUTTON3_CLICKED)
			{
				if (((begx <= x) && (x <= (begx + getmaxx(jeu))))
						&& (((begy <= y) && (y <= (begy + getmaxy(jeu))))))
				{
					if (delete)
					{
						mvdelch(y, x);
					}
					else
					{
						attroff(COLOR_PAIR(2));
						attron(COLOR_PAIR(3));
						mvprintw(y, x, "O");
						x -= begx, y -= begy;
						addTresor(x, y, map);
					}
				}
			}
			wrefresh(jeu);
		}
	}
	delwin(jeu);
	delwin(fenetre);
	ncurses_stopper();
	writeMap(map, file);
	delMap(map);
	closeFile(file);
	return EXIT_SUCCESS;
}
