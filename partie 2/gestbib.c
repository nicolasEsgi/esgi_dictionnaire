#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "gestbib.h"



/// Crée un fichier en prenant en paramètre le
/// le chemin du fichier
/// Exemple :
/// unsigned int i = f_create();
/// Retourne 1 si le fichier a été créé
/// En cas d'erreur, il retourn 0
unsigned int f_create(){
    unsigned int valReturn = 0;
    const char dirStr[17] = ".\\ressources\\";
    const char extension[6] = ".txt";

    char fileName[50];
    printf("Saisissez le nom du fichier sans espace :\n ");
    scanf("\n%s[^\n]", &fileName);

    int pathLenght = strlen(fileName) + strlen(dirStr) + strlen(extension); // Longueur du path en int pour faire un malloc

    char* path = malloc(sizeof(char) * pathLenght + 1);

    strcpy(path,dirStr);
    strcat(path,strcat(fileName, extension));

    char choice;
    FILE *f = fopen(path, "r");
    do{
        fclose(f);
        do{
            printf("Le fichier existe deja !\nVoulez-vous renommer %s ?\n Si non le fichier %s sera ecrase. [O/N] : ", fileName, fileName);
            scanf("\n%s[^\n]", &choice);
        }while(!(choice == 'O' || choice == 'N'
               || choice == 'o' || 'n' == choice));
        if(choice == 'O' || choice == 'o'){
            printf("Saisissez un nouveau sans espace :\n ");
            scanf("\n%s[^\n]", &fileName);

            strcpy(path,dirStr);
            strcat(path,strcat(fileName, extension));
        }else{
            break;
        }

    }while(fExiste(f) != 1 && choice != 'n' || choice != 'N');

    f = fopen(path, "w+");
    if(f != NULL){
        fclose(f);
        valReturn = 1;
    }

    printf("Le fichier a ete cree avec succes !");


    free(path);

    return valReturn;
}
//strcat(dirStr,strcat(fileName, extension))

/// Supprime un fichier en prenant en paramètre le
/// le chemin du fichier
/// Exemple :
/// unsigned int i = f_destroyer();
/// Retourne 1 si le fichier a été supprimé
/// En cas d'erreur, il retourn 0
unsigned int f_destroyer(){
    char fileName[50];
    printf("Saisissez le nom du fichier sans espace :\n ");
    scanf("\n%s[^\n]", &fileName);
    const char dirStr[17] = ".\\ressources\\";
    const char extension[6] = ".txt";
    int pathLenght = strlen(fileName) + strlen(dirStr) + strlen(extension); // Longueur du path en int pour faire un malloc
    char* path = malloc(sizeof(char) * pathLenght + 1);

    strcpy(path,dirStr);
    strcat(path,strcat(fileName, extension));

    FILE* f = fopen(path, "r");

    if(f == NULL){
        printf("Le fichier n'existe pas !");
        fclose(f);
        return 0;
    }
    fclose(f);

    // Confirmation utilisateur
    int ret = remove(path);
    free(path);
    if(ret == 0)
    {
       printf("Fichier supprimé avec succes !");
       return 1;
    }
    else
    {
       printf("Erreur : Suppression impossible !");
       return 0;
    }
}

unsigned int fExiste(FILE* fileToTest){
    if(fileToTest == NULL){
        return 1; // OK
    }else{
        return 0; // ERREUR
    }
}

