#ifndef MAP_H_
#define MAP_H_

#define BOMB 1
#define TRESOR 2

typedef struct
{
	int** map;
	unsigned int sizeX;
	unsigned int sizeY;
	unsigned int nbrBomb;
	unsigned int nbrTresor;
} map_t;

map_t* creerMap(unsigned int sizeX, unsigned int sizeY);
void addBomb(int x, int y, map_t* map);
void addTresor(int x, int y, map_t* map);
void delBomb(int x, int y, map_t* map);
void delTresor(int x, int y, map_t* map);
void delMap(map_t* map);

#endif /* MAP_H_ */
