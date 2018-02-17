#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "map.h"
#include "ncurses.h"

/* file_path x y */
int main(int argc, char *argv[])
{
	int fd = 0, x, y, carac;
	WINDOW* fenetre = NULL, *jeu = NULL;
	map_t* map = NULL;
	if (argc != 4)
	{
		fprintf(stderr,
				"Pas assez d'argument : un nom de fichier est nécessaire.\n");
		exit(EXIT_FAILURE);
	}
	x = atoi(argv[2]), y = atoi(argv[3]);
	if (y > x)
	{
		int tmp = x;
		x = y;
		y = tmp;
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
	if ((jeu = subwin(fenetre, y, x, 2, 2)) == NULL)
	{
		ncurses_stopper();
		fprintf(stderr, "Echec de la création de la fenêtre de l'éditeur.\n");
		exit(EXIT_FAILURE);
	}
	scrollok(jeu, TRUE);
	box(jeu, 0, 0);
	printw(
			"F1 pour l'aide, F2 pour quitter. F3 pour enregistrer pendant l'édition.\n\tJeu");
	/*move(1, 1);*/
	wrefresh(fenetre);
	wrefresh(jeu);
	map = creerMap((unsigned int) x, (unsigned int) y);
	while ((carac = getch()) != KEY_F(2))
		;
	if (fd == 0)
		if ((fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
		{
			ncurses_stopper();
			perror("Erreur ouverture du fichier ");
			exit(EXIT_FAILURE);
		}
	if (close(fd) == -1)
	{
		ncurses_stopper();
		perror("Erreur lors de la fermeture du fichier ");
		exit(EXIT_FAILURE);
	}
	delMap(map);
	delwin(jeu);
	delwin(fenetre);
	ncurses_stopper();
	return EXIT_SUCCESS;
}
