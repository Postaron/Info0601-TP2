#ifndef MAP_H_
#define MAP_H_

typedef struct{
	int** map;
	unsigned int sizeX;
	unsigned int sizeY;
} map_t;

map_t* creerMap(unsigned int sizeX, unsigned int sizeY);
void delMap(map_t* map);

#endif /* MAP_H_ */
