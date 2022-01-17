#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "arrondi512.h"

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
#define nb 2
#define DATE_BUFFER_SIZE 12
int main(int argc, char *argv[]) {
    int fd;

    if (argc > 1 ) {
        fd = open(argv[1], O_RDONLY);
        if (fd < 1) {
            printf("Cannot open file %s\n", argv[1]);
            exit(-1);
        }
    } else {
        fd = STDIN_FILENO; // filling the ph struct
        //test that we convert the file to a struct data
        //if(fd>0) printf("passed");
    }

    struct posix_header hs;

    // loop to pass by every single file "can read 2  file bc of i"
   // int i = 0;

    char version[2];
    memcpy(version , &hs.version[0],2);

    //while(read(fd, &hs, sizeof(hs))>1 && i<nb) {
  while(read(fd, &hs , sizeof(hs))>1){    // to pass all the files
        //get size of file 
       long long file_size = strtoll(hs.size, NULL, 8);
       int file_size_arrondie = arrondi512(file_size);
       int file_blocks_number = file_size_arrondie / BUFFER;
       printf("%lld\n", file_size);
       // i++;
       // </!\> it works but to be more precise we should verify magic and version should be compatible with the structur
       if(strcmp(TMAGIC,hs.magic) != 0 || strcmp(TVERSION,version) != 0){
           break;
       }

        //file name
        printf("%s", strcat(strcat(hs.prefix,"/"),hs.uname));

        //file type
        char flags= hs.typeflag;
        switch (flags)
	        {
	        case  '0':
		    printf("type du fichier: regular file\n");
		    break;
	        case '1':
		    printf("type du fichier: Link\n");
		    break;
	        case '2':
		    printf("type du fichier: reserved\n");
		    break;
	        case '3':
		    printf("type du fichier: Character special\n");
		    break;
	        case '4':
		    printf("type du fichier: Block special\n");
		    break;
	        case '5':
		    printf("type du fichier: Directory\n");
		    break;
	        case '6':
		    printf("type du fichier: FIFO\n");
		    break;

	        default:
		    printf("type du fichier: Error! flag type is not correct\n");
	    }

        //size of the file
        printf(" %d  ", file_size);

        //file mode

        int long mode = strtol(hs.mode,NULL,8);
        printf((S_ISDIR(mode)) ? "d" : "-");
        printf((mode&S_IRUSR) ? "r" : "-");
        printf((mode&S_IWUSR) ? "w" : "-");
        printf((mode&S_IXUSR) ? "x" : "-");
        printf((mode&S_IRGRP) ? "r" : "-");
        printf((mode&S_IWGRP) ? "w" : "-");
        printf((mode&S_IXGRP) ? "x" : "-");
        printf((mode&S_IROTH) ? "r" : "-");
        printf((mode&S_IWOTH) ? "w" : "-");
        printf((mode&S_IXOTH) ? "X" : "-");
        printf("\t");

        //recuperation et affichage du date fichier
        struct tm *info;
        char buffer[DATE_BUFFER_SIZE]; //un buffer pour le stockage du format date à 12 octets
        time_t time_l= strtol(hs.mtime,NULL, 8);
        info = localtime(&time_l);
        printf( "%s ", asctime( info));



        //checksum
        memset(hs.chksum, ' ', 8);
	    hs. chksum[6]='\0';
	    hs. chksum[7]=' ';

	    size_t checksum = 0;
	    const unsigned char* bytes= &hs;
	    for ( int i = 0; i < sizeof(struct posix_header); i++ ){
	    	    checksum += bytes[i];
	        }

	    snprintf( hs.chksum, 8, "%06o", decimalToOctal(checksum ));
        assert(hs.chksum == decimalToOctal(checksum));
        //  skipe to the end to get the next file
            // possède de blocs de données de 512 octets
        int i;
        for(i = 0; i < file_blocks_number ; i++) {
                lseek(fd, 0, SEEK_END);
            }
    }
                close(fd);

        return 0;
}   
