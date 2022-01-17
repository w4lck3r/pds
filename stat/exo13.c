#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main(int argc, char* argv[])
{
    struct stat st;
    struct passwd *pws;
    int res;
    int nb , us , gr ,ot ;

    nb = 0;
    us = 0;
    gr = 0;
    ot = 0;

    assert(argc >= 2);
    
    res = stat(argv[1], &st);
    
    assert((pwd = getpwuid(statbuf.st_uid)) != NULL)
    assert(res != -1);
    
    if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
    printf(" name %-s", pwd->pw_name);
    else
    printf(" id %-d", statbuf.st_uid);

    if(st.st_mode & S_ISREG){
    	printf("reg file");
    }
    else if(st.st_mode & S_ISDIR){
    	printf("directory file");
    }
    else{
    	printf("other type");
    }
    // les permissions du I-noeud
    printf("\ndroits d'access: ");
    if (st.st_mode & R_OK)
        nb += 4;
    if (st.st_mode & W_OK)
        nb += 2;
    if (st.st_mode & X_OK)
        nb += 1;
    printf("%d", nb);
    printf("\n-----------------------------------------------\n");
    //les permissions du I-noeud separemment : 
    printf("\ndroits d'access: USER , GROUP , OTHER\n");
    printf("\npour USER\n");
    if (st.st_mode & S_IRUSR)
        us += 4;
    if (st.st_mode & S_IWUSR)
        us += 2;
    if (st.st_mode & S_IXUSR)
        us += 1;
    printf("user = %d\t", us);
    printf("\n--------------------------");
    printf("\npour GROUP\n");
    if (st.st_mode & S_IRGRP)
        gr += 4;
    if (st.st_mode & S_IWGRP)
        gr += 2;
    if (st.st_mode & S_IXGRP)
        gr += 1;
    printf("group = %d\t", gr);
    printf("\n--------------------------\n");
    printf("pour OTHER\n");
    if (st.st_mode & S_IROTH)
        ot += 4;
    if (st.st_mode & S_IWOTH)
        ot += 2;
    if (st.st_mode & S_IXOTH)
        ot += 1;

    printf("other = %d\n", ot);
    return 0;
}
