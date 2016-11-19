#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "gestrech.h"

#ifndef WIN32
#include <sys/types.h>
#endif

unsigned int strDiff(char *str1Input, char *str2Input){
    //printf("%s", str1Input);
    // printf("%s", str2Input);

    unsigned int charDiff = 0;
    int i = 0;
    int exit = 0;
    while(exit == 0){
        if(str1Input[i] != str2Input[i]){
            charDiff++;
        }
        i++;
        if(str1Input[i] == '\0' || str2Input[i] == '\0')
        {
            charDiff += (strlen(str1Input) > strlen(str2Input) ? strlen(str1Input) - strlen(str2Input) : strlen(str2Input) - strlen(str1Input));
            exit = 1;
        }
    }
    return charDiff;
}

int m_searchWithCharDiff(){
    FILE *fp = fopen ( "test.txt", "r");
    char* line = malloc(sizeof(char)*1024 + 1);
    char* words = malloc(sizeof(char) * 50);
    words = "av ff"; // mot à chercher
    int seuil = 2;
    char ch;
    int index = 0;
    unsigned int v = 0;
    while ((ch = getc(fp)) != EOF ) { // parcours tant que pas fin de fichier
        if ( ch != '\n'){
            line[index++] = ch; // insére à la suite tant que pas \n
        }else {
            line[index] = '\0'; // remplace \n par un \0 fin de chaine
            index=0;
            if((v=strDiff(words, line)) <= seuil){
                printf("%s\n", line);
            }
        }
    }

    fclose ( fp );
    free(line);
    free(words);
    return 0;
}



