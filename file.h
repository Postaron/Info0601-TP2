#ifndef FILE_H_
#define FILE_H_

#include "map.h"

typedef struct
{
	int fd;
} file_t;

file_t* openFile(const char* path);
void writeMap(map_t* map, file_t* file);
void closeFile(file_t* file);

#endif /* FILE_H_ */
