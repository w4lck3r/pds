#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

struct posix_header
{                    /* Byte offset    Field type                 */
  char name[100];            /*   0    NUL-terminated if NUL fits */
  char mode[8];              /* 100                               */
  char uid[8];               /* 108                               */
  char gid[8];               /* 116                               */
  char size[12];             /* 124                               */
  char mtime[12];            /* 136                               */
  char chksum[8];            /* 148                               */
  char typeflag;             /* 156    see below                  */
  char linkname[100];        /* 157    NUL-terminated if NUL fits */
  char magic[6];             /* 257    must be TMAGIC (NUL term.) */
  char version[2];           /* 263    must be TVERSION           */
  char uname[32];            /* 265    NUL-terminated             */
  char gname[32];            /* 297    NUL-terminated             */
  char devmajor[8];          /* 329                               */
  char devminor[8];          /* 337                               */
  char prefix[155];          /* 345    NUL-terminated if NUL fits */
                             /* 500                               */
/* If the first character of prefix is '\0', the file name is name;
   otherwise, it is prefix/name.  Files whose pathnames don't fit in
   that length can not be stored in a tar archive.  */
};

#define TMAGIC   "ustar"        /* ustar and a null */
#define TMAGLEN  6
#define TVERSION "00"           /* 00 and no null */
#define TVERSLEN 2

int main(int argc, char *argv[]){
    struct posix_header ph;
    int r;
    int fd;
    char *fixIt;
    long int size_oct;
    
    char buffer[513];
    fd = open(argv[1], O_RDONLY , O_WRONLY );
    assert(fd != -1);
    r = read(STDIN_FILENO, &ph, sizeof(ph));
    assert(r == sizeof(ph)); // !<doesnt passe>! 
    // < /!\ > another solution has be promoted in lstar2 
    //oct -> dec
    long long file_size = strtoll(ph.size, NULL, 8);
    //size_oct = strtol(ph.size, &fixIt, 8);
    /*convertir d'un char vers un int et apres de l'octal vers hexadecimal ?*/

    printf("%lld\n", file_size);
}


