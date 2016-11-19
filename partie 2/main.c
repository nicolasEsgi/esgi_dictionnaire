#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "gestbib.h"
#include "gestrech.h"

#ifndef WIN32
#include <sys/types.h>
#endif


int main(int argc, char **argv)
{
/*
    printf("Saisir mot 1 -->  ");
    char str[100];
    scanf("\n%[^\n]", str);

    printf("Saisir mot 2 -->  ");
    char str0[100];
    scanf("\n%[^\n]", str0);

    char *str1 = (char*)malloc((strlen(str) + 1));
    strcpy(str1,str);

    char *str2 = malloc(sizeof(char) * (strlen(str0) + 1));
    strcpy(str2,str0);

    printf("%d", strDiff(str1,str2));

    free(str1);
    free(str2);
*/
     m_searchWithCharDiff();

    return 0;
}

/*
#include <stdio.h>

int main ( int argc, char **argv ) {

}*/
