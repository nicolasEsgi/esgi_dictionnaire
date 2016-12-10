#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include "gestbib.h"

#ifndef WIN32

    #include <sys/types.h>

#endif

int main(int argc, char** argv)
{
    int result = 0;
    startMenu();
    /*result = f_create();//*/

    char* strPath;

    /*strPath = fUse();
    result = wordInsert(strPath);//*/

    /*strPath = fUse();
    result = wordSuppr(strPath);//*/

    /*strPath = fUse();
    result = wordSearch(strPath);//*/

    /*result = f_destroyer(strPath);
    printf("DEBUG -> %d ||;\n", result); // DEBUGGAGE*/
    return 0;
}
