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
    //startMenu();
    //fInsert();
    //wordSuppr();
    fUse();
    return 0;
}
