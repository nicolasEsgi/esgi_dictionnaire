#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>     // Pour l'utilisation des dossiers
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
    scanf("\n%s[^\n]", fileName);

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
            printf("Saisissez un nouveau nom sans espace :\n ");
            scanf("\n%s[^\n]", fileName);

            strcpy(path,dirStr);
            strcat(path,strcat(fileName, extension));
        }else{
            break;
        }

    }while((fExiste(f) != 1) && ((choice != 'n') || (choice != 'N')));

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
    scanf("\n%s[^\n]", fileName);
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


// ---------------------------------------------------------------------------------


/*
 *      Qu'est-ce que c'est sys/types ?
 *      Cela fait partie des changements dont j'ai parlé précédemment. Ces lignes de codes signifient :
 *      « Si on n'utilise pas un système d'exploitation Windows, alors on inclut sys/types.h ».
 */
#ifndef WIN32

    #include <sys/types.h>

#endif

/*
 *      Enumération pour le menu du début
 *      avec les code ASCII (49 == 1)
 */

enum reponseStartMenu{
    creer = 49,
    modifier = 50,
    recherche = 51,
    parcourir = 52,
    supprimer = 53,
    quitter = 54
};



/*
 *      Fonction qui lance le menu du début
 */

void startMenu(){
    unsigned char answer = ' ';
    enum reponseStartMenu;
    const char folder[100] = ".\\ressources\\";

    printf("Bienvenue dans notre dictionnaire.\n");
    printf("/!\\ Attention chaque saisie est sensible a la casse.\n\n");
    getchar();

    do{
         system("cls"); // clear la cmd
         printf("1 - Creer un dictionnaire\n");
         printf("2 - Modifier un dictionnaire\n");
         printf("3 - Effectuer une recherche\n");
         printf("4 - Parcourir les dictionnaires\n");
         printf("5 - Supprimer\n");
         printf("6 - Quitter\n");
         printf("\nVotre choix -> ");
         scanf("\n%[^\n]", &answer);
    }while(answer<49 || answer>55);

    unsigned int result;
    DIR* repertory = opendir(folder);
    switch(answer){
        case creer:
            break;
        case modifier:
            break;
        case recherche:
            break;
        case parcourir:
            result = dListe(repertory);

            if(result == 0){
                printf("Probleme d'ouverture du dossier");
            }else{

                printf("Que voulez-vous faire ?\n");
                printf("1 - Utiliser un dictionnaire\n");
                printf("2 - Retour au menu principal\n");
                printf("\nVotre choix -> ");
                scanf("\n%[^\n]", &answer);
                if(answer == 49){ // == 1
                    fUse();
                }
            }
            break;
        case supprimer:
            break;
        case quitter:
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("default --- %d", (int)answer);
            break;

    }
}



/*
 *      Fonction vérifie si l'éxistance du fichier (option r)
 *      Prend un FILE en paramètre
 *      Retourne 0 en cas d'erreur sinon 1
 */

unsigned int fExiste(FILE* fileToTest){
    if(fileToTest == NULL){
        return 0; // ERREUR
    }else{
        return 1; // OK
    }
}



/*
 *      Fonction qui liste un repertoire
 *      Prends un DIR en paramètre
 *      Retourne 0 en cas d'erreur sinon 1
 */

unsigned int dListe(DIR* rep){
    if(rep == NULL){
        printf("Probleme d'ouverture\n");
        return 0; // Dossier mal ouvert
    }

    struct dirent* fichierLu = NULL; // Vers structure dirent   // cette structure, elle simule le fichier du dossier qui sera lu
    char* format;
    //fichierLu = readdir(rep); // On lit le premier répertoire du dossier
    while((fichierLu = readdir(rep)) != NULL){  //readdir() renvoie NULL s'il n'y a plus de fichier à lire.
        format = fNameDecoupage(fichierLu->d_name);
        if(format != NULL && strcmp(format, "txt") == 0){
            printf("while -> '%s'\n", fichierLu->d_name);
        }
    }

    free(format);
    //fichierLu = readdir(rep); // On lit le premier répertoire du dossier
    if(closedir(rep) == -1){
        printf("Dossier mal fermer\n");
        return 0; // Dossier mal fermé
    }

    return 1; // OK

    /* Pour savoir quel fichier readdir() doit lire, un curseur virtuel est créé :
     * à chaque appel de cette fonction(), le curseur avance d'un pas.
     */
}



/*
 *      Permet d'utiliser un dico choisi a la main
 *      Prend aucun paramètre
 *      Retourne un STRING /!\ MALLOC
 */

char* fUse(){
    char fName[50];
    const char folder[250] = ".\\ressources\\";
    const char fextension[5] = ".txt";
    int pathLenght = strlen(fName) + strlen(folder) + strlen(fextension); // Longueur du path en int pour faire un malloc;
    char* path = malloc(sizeof(char) * pathLenght + 1);

    printf("Choisir un nom de dictionnaire\n");
    scanf("%s", fName);

    strcpy(path, folder);
    strcat (path, fName);
    strcat (path, fextension);
    printf("%s\n", path); // DEBUGGAGE

    return path;
}



/*
 *      Fonction qui permet de connaitre l'extension du fichier
 *      Prendre une chaine de caractère en paramètre
 *      Retourne une chaine de caractère (MALLOC pensez à free)
 */

char* fNameDecoupage(char* str){
    const char caracDecoup[2] = ".";
    str = strtok(str, caracDecoup);
    str = strtok(NULL, caracDecoup);
    char* res = malloc(sizeof(char)*5+1);
    res = str;
    return res;
}


/*
 *      Fonction qui permet l'insertion d'un mot dans le dictionnaire
 *      Ne prends rien en parametre
 *      Ne renvoi rien
 */

unsigned int wordInsert(char* path){
    FILE* fSource = fopen(path, "r"); // ecriture lecture
    int result = fExiste(fSource);
    if(result == 0){
        printf("Le fichier n'exite pas");
        return 0;
    }
    FILE* fSortie = fopen(".\\ressources\\temp.txt", "w");
    result = fExiste(fSortie);

    char line[1024];
    char words [50]; // mot à chercher
    char ch = ' ';
    printf("Saisir le mot a ajouter -> ");
    scanf("\n%s[^\n]", words);
    int resSearch = 0;
    int index = 0;
    while ((ch = getc ( fSource )) != EOF ) { // parcours tant que pas fin de fichier
        if ( ch != '\n'){
            line[index++] = ch; // insére à la suite tant que pas \n
        }else {
            line[index] = '\0'; // remplace \n par un \0 fin de chaine
            index=0;
           if (resSearch != 0){
               fprintf(fSortie, "%s\n", line);
           }else{
               if(strcmp(words,line) < 0) {
                    fprintf(fSortie, "%s\n", words);
                    fprintf(fSortie, "%s\n", line);
                    printf("Insertion effectuer\n");
                    resSearch = 1;
                }else if (strcmp(line,words) == 0) {
                    printf("Le mot existe deja\n");
                    fprintf(fSortie, "%s\n", line);
                    resSearch = 1;
                }else{
                    fprintf(fSortie, "%s\n", line);
                }
            }
        }
    }
    if (1 != resSearch) {
        fprintf(fSortie, "%s\n", words);
        printf("Insertion effectuer\n");
    }
    fclose(fSource);
    fclose(fSortie);
    remove(path);
    rename(".\\ressources\\temp.txt", path);
    remove(".\\ressources\\temp.txt");
    return 1;
}

unsigned int wordSuppr(){
    char folder[250] = ".\\ressources\\";
    const char fName[100] = "test";
    const char fextension[5] = ".txt";
    strcat (folder, fName);
    strcat (folder, fextension);
    printf("%s\n", folder); // DEBUGGAGE
    FILE* fSource = fopen(folder, "r"); // ecriture lecture
    int result = fExiste(fSource);
    if(result == 0){
        printf("Le fichier n'exite pas");
        return 0;
    }
    FILE* fSortie = fopen(".\\ressources\\temp.txt", "w");
    int resSearch = 0;

    char line[1024];
    char words [50]; // mot à chercher
    char ch = ' ';
    printf("Saisir un mot a supprimer -> ");
    scanf("\n%s[^\n]", words);
    int index = 0;
    while ((ch = getc ( fSource )) != EOF ) { // parcours tant que pas fin de fichier
        if ( ch != '\n'){
            line[index++] = ch; // insére à la suite tant que pas \n
        }else {
            line[index] = '\0'; // remplace \n par un \0 fin de chaine
            index=0;
               if(strcmp(words,line) != 0) {
                    fprintf(fSortie, "%s\n", line);
                }else{
                    resSearch = 1;
                    printf("Suppression effectuer\n");
                }
            }
        }
    if(resSearch == 0){
        printf("Le mot n'est pas present dans le dictionnaire\n");
        return 0;
    }
    fclose(fSource);
    fclose(fSortie);
    remove(folder);
    rename(".\\ressources\\temp.txt", folder);
    remove(".\\ressources\\temp.txt");
    return 1;   // OK
}

// --------------------------------------------------------------------


char * remove_spaces(const char *input, char *result)
{
  int i, j = 0;
  for (i = 0; input[i] != '\0'; i++) {
    if (!isspace((unsigned char) input[i])) {
      result[j++] = input[i];
    }
  }
  result[j] = '\0';

  return result;
}

unsigned int fsearch (char * words,FILE* fp ) {

    char line[1024];
    char ch = getc ( fp );
    int x = 0;
    int index = 0;
    while ((ch = getc (fp)) != EOF ) { // parcours tant que pas fin de fichier
        if ( ch != '\n'){
            line[index++] = ch; // insére à la suite tant que pas \n
        }else {
            line[index] = '\0'; // remplace \n par un \0 fin de chaine
            index=0;
            printf("line = %s\nwords = %s\n", line,words);
           if(strcmp(line,words) == 0) {
                printf("trouver");
                x = 1;
                break;
            }
        }
    }

    fclose ( fp );

    if (1 != x) {
        printf("mot introuvable");
        return 0;
    }
    return 1;
}
