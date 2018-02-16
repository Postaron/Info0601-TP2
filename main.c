#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

/* file_path x y */
int main(int argc, char *argv[])
{
	int fd;
	int x, y;
	if (argc != 3)
	{
		fprintf(stderr,
				"Pas assez d'argument : un nom de fichier est nécessaire.\n");
		exit(EXIT_FAILURE);
	}
	x = atoi(argv[2]), y = atoi(argv[3]);
	if ((fd = open(argv[1], O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR))
			== -1)
	{
		perror("Erreur ouverture du fichier ");
		exit(EXIT_FAILURE);
	}
	if (close(fd) == -1)
	{
		perror("Erreur lors de la fermeture du fichier ");
		exit(EXIT_FAILURE);
	}
	printf("Fichier fermé.\n");
	return EXIT_SUCCESS;
}
