#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int fd;
    long int size;
    if (argc != 2)
    {
        fprintf(stderr, "Pas assez d'argument : un nom de fichier est nécessaire.\n");
        exit(EXIT_FAILURE);
    }
    if ((fd = open(argv[1], O_RDONLY, S_IRUSR)) == -1)
    {
        perror("Erreur ouverture du fichier ");
        exit(EXIT_FAILURE);
    }
    printf("Le fichier existe !\n");
    if ((size = lseek(fd, 0, SEEK_END)) == -1)
    {
        perror("Erreur de parcours de fichier ");
        exit(EXIT_FAILURE);
    }
    printf("Taille du fichier : %ld\n", size);
    if (close(fd) == -1)
    {
        perror("Erreur lors de la fermeture du fichier ");
        exit(EXIT_FAILURE);
    }
    printf("Fichier fermé.\n");
    return EXIT_SUCCESS;
}
