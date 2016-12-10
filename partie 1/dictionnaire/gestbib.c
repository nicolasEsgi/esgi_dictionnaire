#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>     // Pour l'utilisation des dossiers
#include "gestbib.h"



/// Crï¿½e un fichier en prenant en paramï¿½tre le
/// le chemin du fichier
/// Exemple :
/// unsigned int i = f_create();
/// Retourne 1 si le fichier a ï¿½tï¿½ crï¿½ï¿½
/// En cas d'erreur, il retourn 0
unsigned int f_create(){
    unsigned int valReturn = 0;
    const char dirStr[17] = ".\\ressources\\";
    const char extension[6] = ".txt";

    char fileName[50];
    printf("Saisissez le nom du fichier sans espace :\n [A fr annul] :");
    scanf("\n%s[^\n]", fileName);

    if(annulprocedure(fileName) == 1){
        return 0;
    }

    int pathLenght = strlen(fileName) + strlen(dirStr) + strlen(extension); // Longueur du path en int pour faire un malloc

    char* path = malloc(sizeof(char) * pathLenght + 1);

    strcpy(path,dirStr);
    strcat(path,strcat(fileName, extension));

    char choice;
    FILE *f = fopen(path, "r");
    int result = fExiste(f);
    // printf("%d", result);
    while((result == 1) && (((choice != 'n') || (choice != 'N'))) && (choice != 'A' || choice !=  'a')){
        fclose(f);
        do{
            printf("Le fichier existe deja !\nVoulez-vous renommer %s ?\nSi non le fichier %s sera ecrase. [O/N] : \n [A for annul] : ", fileName, fileName);
            scanf("\n%s[^\n]", &choice);
        }while(!(choice == 'O' || choice == 'N'
               || choice == 'o' || 'n' == choice || choice == 'A' || choice == 'a'));

        if ((choice == 'A') || (choice == 'a')){
            printf("Vous avez annule\n");
            return 0;
        }

        if(choice == 'O' || choice == 'o'){
            printf("Saisissez un nouveau nom sans espace :\n");
            scanf("\n%s[^\n]", fileName);

            strcpy(path,dirStr);
            strcat(path,strcat(fileName, extension));
            f = fopen(path, "r");
            result = fExiste(f);
        }else{
            break;
        }
    }
    f = fopen(path, "w+");
    if(f != NULL){
        fclose(f);
        valReturn = 1;
    }

    printf("Le fichier a ete cree avec succes !\n");


    free(path);

    return valReturn;

}



/// Supprime un fichier en prenant en paramï¿½tre le
/// le chemin du fichier
/// Exemple :
/// unsigned int i = f_destroyer();
/// Retourne 1 si le fichier a ï¿½tï¿½ supprimï¿½
/// En cas d'erreur, il retourn 0
unsigned int f_destroyer(char* path) {

    FILE* f = fopen(path, "r");
    int result = fExiste(f);

    if(result == 0){
        printf("Le dictionnaire n'existe pas !");
        return 0;
    }
    fclose(f);

    // Confirmation utilisateur
    int ret = remove(path);
    if(ret == 0)
    {
       printf("Dictionnaire supprime avec succes !");
       return 1;
    }
    else
    {
       printf("Erreur : Suppression du dictionnaire impossible !");
       return 0;
    }

    free(path);
}


// ---------------------------------------------------------------------------------


/*
 *      Qu'est-ce que c'est sys/types ?
 *      Cela fait partie des changements dont j'ai parlï¿½ prï¿½cï¿½demment. Ces lignes de codes signifient :
 *      ï¿½ Si on n'utilise pas un systï¿½me d'exploitation Windows, alors on inclut sys/types.h ï¿½.
 */
#ifndef WIN32

    #include <sys/types.h>

#endif

/*
 *      Enumï¿½ration pour le menu du dï¿½but
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
 *      Fonction qui lance le menu du dï¿½but
 */

void startMenu(){
    unsigned char answer = ' ';
    enum reponseStartMenu;
    const char folder[100] = ".\\ressources\\";

    printf("Bienvenue dans notre dictionnaire.\n");
    printf("/!\\ Attention chaque saisie est sensible a la casse.\n");
    printf("Appuyez sur ENTRER pour continuer.\n\n");
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
            if(f_create() == 0){
                printf("Une erreur est survenue !");
            }
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
            // f_destroyer(path);
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
 *      Fonction vï¿½rifie si l'ï¿½xistance du fichier (option r)
 *      Prend un FILE en paramï¿½tre
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
 *      Prends un DIR en paramï¿½tre
 *      Retourne 0 en cas d'erreur sinon 1
 */

unsigned int dListe(DIR* rep){
    if(rep == NULL){
        printf("Probleme d'ouverture\n");
        return 0; // Dossier mal ouvert
    }

    struct dirent* fichierLu = NULL; // Vers structure dirent   // cette structure, elle simule le fichier du dossier qui sera lu
    char* format;
    //fichierLu = readdir(rep); // On lit le premier rï¿½pertoire du dossier
    while((fichierLu = readdir(rep)) != NULL){  //readdir() renvoie NULL s'il n'y a plus de fichier ï¿½ lire.
        format = fNameDecoupage(fichierLu->d_name);
        if(format != NULL && strcmp(format, "txt") == 0){
            printf("while -> '%s'\n", fichierLu->d_name);
        }
    }

    free(format);
    //fichierLu = readdir(rep); // On lit le premier rï¿½pertoire du dossier
    if(closedir(rep) == -1){
        printf("Dossier mal fermer\n");
        return 0; // Dossier mal fermï¿½
    }

    return 1; // OK

    /* Pour savoir quel fichier readdir() doit lire, un curseur virtuel est crï¿½ï¿½ :
     * ï¿½ chaque appel de cette fonction(), le curseur avance d'un pas.
     */
}



/*
 *      Permet d'utiliser un dico choisi a la main
 *      Prend aucun paramètre
 *      Retourne le chemin du fichier
 *      Sinon null
 *      Retourne un STRING /!\ MALLOC
 */

char* fUse(){
    char fName[50];
    const char folder[250] = ".\\ressources\\";
    const char fextension[5] = ".txt";
    int pathLenght = strlen(fName) + strlen(folder) + strlen(fextension); // Longueur du path en int pour faire un malloc;
    char* path = malloc(sizeof(char) * pathLenght + 1);

    printf("Choisir un nom de dictionnaire\n [A for annul] : ");
    scanf("%s", fName);
    if(annulprocedure(fName) == 1){
        return NULL;
    }
    strcpy(path, folder);
    strcat (path, fName);
    strcat (path, fextension);

    return path;
}



/*
 *      Fonction qui permet de connaitre l'extension du fichier
 *      Prendre une chaine de caractï¿½re en paramï¿½tre
 *      Retourne une chaine de caractï¿½re (MALLOC pensez ï¿½ free)
 */

char* fNameDecoupage(char* str){
    const char caracDecoup[2] = ".";
    str = strtok(str, caracDecoup);
    str = strtok(NULL, caracDecoup);
    char* res = malloc(sizeof(char)*5+1);
    res = str;
    return res;
}

////////////////////////////////////////////////////////////////////////////////////
/*
 *      Fonction qui permet l'insertion d'un mot dans le dictionnaire
 *      Ne prends rien en parametre
 *      Ne renvoi rien
 */


unsigned int jPP(char* path, int func, poubelle* p1){
    p1->fSource = fopen(path, "r"); // ecriture lecture;

    if(fExiste(p1->fSource) == 0){
        printf("Le fichier n'exite pas");
        return 0; // ECHEC
    }

    escro(func);

    scanf("\n%s[^\n]", p1->words);
    if(annulprocedure(p1->words) == 1){
        return 0; // ECHEC
    }
    return 1;
}

unsigned int wordInsert(char* path){
    int typeFunc = 1;
    poubelle* p = malloc(sizeof(poubelle));
    p->resSearch = 0;

    if(jPP(path, typeFunc, p) == 0){
        free(p);
        return 0; // ECHEC
    }
    laSuite(typeFunc, p);
    remplaceTempToDico(path, p);
    free(p);
    return 1;
}

void laSuite(int tf, poubelle* p1){
    p1->fSortie = fopen(".\\ressources\\temp.txt", "w");
    char ch = ' ';
    int index = 0;
    while ((ch = getc ( p1->fSource )) != EOF ) { // parcours tant que pas fin de fichier
        if ( ch != '\n'){
            p1->line[index++] = ch; // insére à la suite tant que pas \n
        }else {
            p1->line[index] = '\0'; // remplace \n par un \0 fin de chaine
            index=0;
            //--------------
            if(tf == 1){
                // WORDINSERT
                partWordInsert(p1);
            }else if(tf == 2){
                // WORDSUPPR
                partWordSuppr(p1);
            }else if(tf == 3){
                // FSCEARCH
                partSearch(p1);
            }
            //--------------
        }
        if((p1->resSearch == 1) && (tf == 3)){
            break;
        }
    }
    typeErr(tf, p1);
}

void partWordInsert(poubelle* p2){
    if (p2->resSearch != 0){
        fprintf(p2->fSortie, "%s\n", p2->line);
    }else{
       if(strcmp(p2->words,p2->line) < 0) {
            fprintf(p2->fSortie, "%s\n", p2->words);
            fprintf(p2->fSortie, "%s\n", p2->line);
            printf("Insertion effectue\n");
            p2->resSearch = 1;
        }else if (strcmp(p2->words,p2->line) == 0) {
            printf("Le mot existe deja\n");
            fprintf(p2->fSortie, "%s\n", p2->line);
            p2->resSearch = 2; // Deja présent = 2
        }else{
            fprintf(p2->fSortie, "%s\n", p2->line);
        }
    }
}

void partWordSuppr(poubelle* p2){
    if(strcmp(p2->words,p2->line) != 0) {
        fprintf(p2->fSortie, "%s\n", p2->line);
    }else{
        p2->resSearch = 1;
        printf("Suppression effectuer\n");
    }
}

<<<<<<< HEAD
void partSearch(poubelle* p2){
    if(p2->resSearch != 1){
        if(strcmp(p2->line,p2->words) == 0) {
            printf("trouver");
            p2->resSearch = 1;
        }
    }
}

unsigned int wordSuppr(char* path){
    int typeFunc = 2;
    poubelle* p = malloc(sizeof(poubelle));
    p->resSearch = 0;
    if(jPP(path, typeFunc, p) == 0){
        free(p);
        return 0; // ECHEC
    }
    laSuite(typeFunc, p);
    remplaceTempToDico(path, p);
    free(p);
    return 1;
}

unsigned int wordSearch(char* path){
    int typeFunc = 3;
    poubelle* p = malloc(sizeof(poubelle));
    p->resSearch = 0;
    if(jPP(path, typeFunc, p) == 0){
        free(p);
        return 0; // ECHEC
    }
    laSuite(typeFunc, p);
    free(p);
    return 1;
}

unsigned int remplaceTempToDico(char* path, poubelle* p1){
    fclose(p1->fSource);
    fclose(p1->fSortie);
    remove(path);
    rename(".\\ressources\\temp.txt", path);
    remove(".\\ressources\\temp.txt");
    free(path);
    return 1;   // OK
}

unsigned int annulprocedure(char* carac){
    if ((strcmp(carac, "A") == 0) || (strcmp(carac, "a") == 0)){
        printf("Vous avez annule\n");
        return 1;
    }
    return 0;
}

void escro(int nb){ // printPrompt
    switch(nb){
        case 1:
            printf("Saisir un mot a inserer -> [A for annul] : ");
            break;
        case 2:
            printf("Saisir un mot a supprimer -> [A for annul] : ");
            break;
        case 3:
            printf("Saisir un mot a rechercher -> [A for annul] : ");
            break;
    }
}

void typeErr(int tf, poubelle* p2){
    if(p2->resSearch == 0){
        switch(tf){
            case 1:
                fprintf(p2->fSortie, "%s\n", p2->words);
                printf("Insertion effectue\n");
                break;
            case 2:
            case 3:
                printf("Le mot n'est pas present dans le dictionnaire\n");
                break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////

// --------------------------------------------------------------------

unsigned int fsearch (char * words, char * path) {
    FILE *fp = fopen(path,"r");
    unsigned int exist = fExiste(fp);
    if (0 == exist) {
        return 0;
    }
    char line[1024];
    char ch = getc ( fp );
    int x = 0;
    int index = 0;
    while ((ch = getc (fp)) != EOF ) { // parcours tant que pas fin de fichier
        if ( ch != '\n'){
            line[index++] = ch; // insï¿½re ï¿½ la suite tant que pas \n
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
        printf("Mot introuvable");
        return 0;
    }
    return 1;
}
