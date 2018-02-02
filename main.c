#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int fd;
    if (argc != 2)
    {
        fprintf(stderr, "Pas assez d'argument : un nom de fichier " st nécessaire.\n);
        exit(EXIT_FAILURE);
        it(EXIT_FAILURE);
    }
    if ((fd = open(argv[1], O_RDONLY, S_IRUSR)) == -1)
    {
        perror("Erreur ouverture du fichier : ");
        exit(EXIT_FAILURE);
    }
    printf("Le fichier existe !\n");
    if (close(fd) == -1)
    {
        perror("Erreur lors de la fermeture du fichier : ");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
