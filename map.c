#include "map.h"

#include <stdio.h>
#include <stdlib.h>

map_t* creerMap(unsigned int sizeX, unsigned int sizeY)
{
	unsigned int i;
	map_t* map = NULL;
	if ((map = (map_t*) malloc(sizeof(map_t))) == NULL)
	{
		fprintf(stderr, "Erreur allocation map\n");
		exit(EXIT_FAILURE);
	}
	map->sizeX = sizeX, map->sizeY = sizeY, map->nbrBomb = 0, map->nbrTresor = 0;
	if ((map->map = (int**) malloc(sizeof(int*) * sizeY)) == NULL)
	{
		fprintf(stderr, "Erreur allocation carte, lignes\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < sizeY; ++i)
	{
		if ((map->map[i] = (int*) calloc(sizeX, sizeof(int))) == NULL)
		{
			fprintf(stderr, "Erreur allocation carte, colonne %d\n", i);
			exit(EXIT_FAILURE);
		}
	}
	return map;
}
/* 1 = bombe présente, 0 aucune bombe. */
void addBomb(int x, int y, map_t* map)
{
	map->map[y][x] = BOMB;
	++map->nbrBomb;
}

void addTresor(int x, int y, map_t* map)
{
	map->map[y][x] = TRESOR;
	++map->nbrTresor;
}

void delBomb(int x, int y, map_t* map)
{
	map->map[y][x] = 0;
	--map->nbrBomb;
}

void delTresor(int x, int y, map_t* map)
{
	map->map[y][x] = 0;
	--map->nbrTresor;
}

void delMap(map_t* map)
{
	unsigned int i;
	for (i = 0; i < map->sizeY; ++i)
	{
		free(map->map[i]);
	}
	free(map);
}
