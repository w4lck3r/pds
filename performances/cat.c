#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if(argc != 3) {
        printf("Commande invalide \n");
        exit(1);
    }
    int fd;

    int sizeTampon = (argv[1], 10, stdin);

    // using atoi is better for handling errors
    // int sizeTampon = atoi(argv[1]);

    char buffer[sizeTampon];

    if ( (fd = open(argv[2], O_RDONLY , O_WRONLY )) == -1) {
        perror("open");
        exit(1);
    }

    int readen;

    while( (readen = read (fd, buffer, sizeof(buffer))) > 0 ) {
       if (write(0, buffer, readen) == -1) {
            perror("write :");
            exit(1);
        }
    }
    close(fd);
    return 0;
}
