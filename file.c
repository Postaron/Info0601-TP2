#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void checkIOFun(ssize_t err)
{
	if (err == -1)
	{
		perror("Erreur ");
		exit(EXIT_FAILURE);
	}
}

file_t* openFile(const char* path)
{
	file_t* file = NULL;
	if (path == NULL)
	{
		fprintf(stderr, "Erreur, chemin spécifié inexistant\n");
		exit(EXIT_FAILURE);
	}
	if ((file = (file_t*) malloc(sizeof(file_t))) == NULL)
	{
		fprintf(stderr, "Erreur allocation file_t\n");
		exit(EXIT_FAILURE);
	}
	checkIOFun(file->fd = open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR));
	return file;
}

void writeMap(map_t* map, file_t* file)
{
	unsigned int i, j;
	/**
	 * On met d'abord X puis Y
	 */
	checkIOFun(
			write(file->fd, (unsigned char*) &map->sizeX,
					sizeof(unsigned char)));
	checkIOFun(
			write(file->fd, (unsigned char*) &map->sizeY,
					sizeof(unsigned char)));
	/**
	 * Le nombre de bombe dans la map
	 */
	checkIOFun(
			write(file->fd, (unsigned char*) &map->nbrBomb,
					sizeof(unsigned char)));
	for (i = 0; i < map->sizeX; ++i)
	{
		for (j = 0; j < map->sizeY; ++j)
		{
			if (map->map[j][i] == BOMB)
			{
				/**
				 * Y de la bombe
				 * X de la bombe
				 */
				checkIOFun(
						write(file->fd, (unsigned char*) &j,
								sizeof(unsigned char)));
				checkIOFun(
						write(file->fd, (unsigned char*) &i,
								sizeof(unsigned char)));
			}
		}
	}
	checkIOFun(
			write(file->fd, (unsigned char*) &map->nbrTresor,
					sizeof(unsigned char)));
	for (i = 0; i < map->sizeX; ++i)
	{
		for (j = 0; j < map->sizeY; ++j)
		{
			if (map->map[j][i] == TRESOR)
			{
				checkIOFun(
						write(file->fd, (unsigned char*) &j,
								sizeof(unsigned char)));
				checkIOFun(
						write(file->fd, (unsigned char*) &i,
								sizeof(unsigned char)));
			}
		}
	}
}

void loadMap(map_t** map, file_t* file)
{
	unsigned int x, y, i;
	checkIOFun(read(file->fd, (void*) &x, sizeof(unsigned char)));
	checkIOFun(read(file->fd, (void*) &y, sizeof(unsigned char)));
	*map = creerMap(x, y);
	checkIOFun(read(file->fd, (void*) &(*map)->nbrBomb, sizeof(unsigned char)));
	for (i = 0; i < (*map)->nbrBomb; ++i)
	{
		checkIOFun(read(file->fd, (void*) &y, sizeof(unsigned char)));
		checkIOFun(read(file->fd, (void*) &x, sizeof(unsigned char)));
		addBomb((int) x, (int) y, *map);
	}
	checkIOFun(
			read(file->fd, (void*) &(*map)->nbrTresor, sizeof(unsigned char)));
	for (i = 0; i < (*map)->nbrTresor; ++i)
	{
		checkIOFun(read(file->fd, (void*) &y, sizeof(unsigned char)));
		checkIOFun(read(file->fd, (void*) &x, sizeof(unsigned char)));
		addTresor((int) x, (int) y, *map);
	}
}

void closeFile(file_t* file)
{
	checkIOFun(close(file->fd));
	free(file);
}
