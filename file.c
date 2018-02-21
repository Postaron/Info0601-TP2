#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

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
	if ((file->fd = open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
	{
		perror("Erreur ");
		exit(EXIT_FAILURE);
	}
	return file;
}

inline void checkIOFun(ssize_t err)
{
	if (err == -1)
	{
		perror("Erreur ");
		exit(EXIT_FAILURE);
	}
}

void writeMap(map_t* map, file_t* file)
{
	checkIOFun(
			write(file->fd, (void*) &((unsigned char) map->sizeX),
					sizeof(unsigned char)));
	checkIOFun(
				write(file->fd, (void*) &((unsigned char) map->sizeY),
						sizeof(unsigned char)));
	checkIOFun(
				write(file->fd, (void*) &((unsigned char) map->nbrBomb),
						sizeof(unsigned char)));
	/* Work in Progress */
}

void closeFile(file_t* file)
{

}
