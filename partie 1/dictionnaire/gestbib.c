#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>     // Pour l'utilisation des dossiers
#include "gestbib.h"



/// Cree un fichier en prenant en parametre le
/// le chemin du fichier
/// Exemple :
/// unsigned int i = f_create();
/// Retourne 1 si le fichier a ete cree
/// En cas d'erreur, il retourn 0
unsigned int f_create(){
    const char dirStr[17] = ".\\ressources\\";
    const char extension[6] = ".txt";

    char fileName[50];
    printf("Saisissez le nom du fichier sans espace :\n [A fr annul] :");
    scanf("\n%s[^\n]", fileName);

    if(annulProcedure(fileName) == 1){
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

    free(path);

    return 1;

}



/// Supprime un fichier en prenant en parametre le
/// le chemin du fichier
/// Exemple :
/// unsigned int i = f_destroyer();
/// Retourne 1 si le fichier a ete supprime
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
    if(ret != 0)
    {
       printf("Erreur : Suppression du dictionnaire impossible !");
       return 0;
    }

    free(path);
    return 1;
}


// ---------------------------------------------------------------------------------


/*
 *      Qu'est-ce que c'est sys/types ?
 *      Cela fait partie des changements dont j'ai parlï¿½ precedemment. Ces lignes de codes signifient :
 *      Si on n'utilise pas un systeme d'exploitation Windows, alors on inclut sys/types.h.
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
    importer = 50,
    motInsert = 51,
    motSuppr = 52,
    recherche = 53,
    supprimer = 54,
    quitter = 55
};



/*
 *      Fonction qui lance le menu du début
 */

void startMenu(){
    unsigned char answer = ' ';
    enum reponseStartMenu;
    char* str;
    printf("Bienvenue dans notre dictionnaire.\n");
    printf("/!\\ Attention chaque saisie est sensible a la casse.\n");
    printf("Appuyez sur ENTRER pour continuer.\n\n");
while(1){
        getch();
        do{
             system("cls"); // clear la cmd
             printf("\tMENU PRINCIPAL\n\n");
             printf("1 - Creer un dictionnaire\n");
             printf("2 - Importer un fichier txt\n");
             printf("3 - Inserer un mot\n");
             printf("4 - Suprimer un mot\n");
             printf("5 - Effectuer une recherche\n");
             printf("6 - Supprimer un dictionnaire\n");
             printf("7 - Quitter\n");
             printf("\nVotre choix -> ");
             scanf("\n%[^\n]", &answer);
        }while(answer<49 || answer>55);

        switch(answer){
            case creer:
                if(f_create() == 1){
                    printf("Le dictionnaire a ete cree\n");
                }
                break;
            case importer:
                //------------------------------>
                break;
            case motInsert:
                str = fUse();
                if(str == NULL){
                    break;
                }
                mainWord(str, 1);
                break;
            case motSuppr:
                str = fUse();
                if(str == NULL){
                    break;
                }
                mainWord(str, 2);
                break;
            case recherche:
                str = fUse();
                if(str == NULL){
                    break;
                }
                mainWord(str, 3);
                break;
            case supprimer:
                str = fUse();
                if(str == NULL){
                    break;
                }
                if(f_destroyer(str) == 1){
                    printf("Dictionnaire supprime avec succes !\n");
                }
                break;
            case quitter:
                exit(EXIT_SUCCESS);
                break;
        }
    }
}



/*
 *      Fonction verifie si l'existance du fichier (option r)
 *      Prend un FILE en parametre
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
 *      Prends un DIR en parametre
 *      Retourne 0 en cas d'erreur sinon 1
 */

unsigned int dListe(DIR* rep){
    if(rep == NULL){
        printf("Probleme d'ouverture\n");
        return 0; // Dossier mal ouvert
    }

    struct dirent* fichierLu = NULL; // Vers structure dirent   // cette structure, elle simule le fichier du dossier qui sera lu
    char* format;
    //fichierLu = readdir(rep); // On lit le premier repertoire du dossier
    while((fichierLu = readdir(rep)) != NULL){  //readdir() renvoie NULL s'il n'y a plus de fichier a lire.
        format = fNameDecoupage(fichierLu->d_name);
        if(format != NULL && strcmp(format, "txt") == 0){
            printf("\t%s\n", fichierLu->d_name);
        }
    }
    printf("\n");

    free(format);
    //fichierLu = readdir(rep); // On lit le premier repertoire du dossier
    if(closedir(rep) == -1){
        printf("Dossier mal fermer\n");
        return 0; // Dossier mal fermï¿½
    }

    return 1; // OK

    /* Pour savoir quel fichier readdir() doit lire, un curseur virtuel est cree :
     * a chaque appel de cette fonction(), le curseur avance d'un pas.
     */
}



/*
 *      Permet d'utiliser un dico choisi a la main
 *      Prend aucun parametre
 *      Retourne le chemin du fichier
 *      Sinon NULL
 *      Retourne un STRING /!\ MALLOC
 */

char* fUse(){
    const char folder[250] = ".\\ressources\\";
    DIR* repertory;
    char fName[50];
    const char fextension[5] = ".txt";
    int pathLenght = strlen(fName) + strlen(folder) + strlen(fextension); // Longueur du path en int pour faire un malloc;
    char* path = malloc(sizeof(char) * pathLenght + 1);
    FILE*f=fopen(path, "r");
    do{
        system("cls");
        printf("Voici les dictionnaires present.\n\n");
        repertory = opendir(folder);
        dListe(repertory);
        printf("Choisir un nom de dictionnaire\n [A for annul] : ");
        scanf("%s", fName);
        if(annulProcedure(fName) == 1){
            return NULL;
        }
        strcpy(path, folder);
        strcat (path, fName);
        strcat (path, fextension);
        f = fopen(path, "r");
    }while(fExiste(f) == 0);
    return path;
}



/*
 *      Fonction qui decoupe le nom du fichier et l'extension
 *      Prendre une chaine de caractere en parametre
 *      Retourne une chaine de caractere (MALLOC pensez a free)
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
 *      Fonction qui test l'exitance du fichier
 *      et saisit du mot
 *      Retourne 0 en cas d'erreur
 *      1 si tout est correct
 */

unsigned int wordsScan(char* path, int func, poubelle* p1){
     p1->fSource = fopen(path, "r"); // lecture

    if(fExiste(p1->fSource) == 0){
        printf("Le fichier n'exite pas");
        return 0; // ECHEC
    }

    printPrompt(func);

    scanf("\n%s[^\n]", p1->words);
    if(annulProcedure(p1->words) == 1){
        return 0; // ECHEC
    }
    return 1;
}

/*
 *      Fonction principale pour les traitements suivant
 *      Insertion, suppresion de mots
 *      Recherche de mot
 *      Retourne 0 en cas d'erreur
 *      1 si tout est bon
 */
unsigned int mainWord(char* path, int typeFunc){
    poubelle* p = malloc(sizeof(poubelle));
    p->resSearch = 0;
    if(wordsScan(path, typeFunc, p) == 0){
        free(p);
        return 0; // ECHEC
    }
    wordTraitement(typeFunc, p);
    if(typeFunc != 3){
        remplaceTempToDico(path, p);
    }
    free(p);
    return 1;
}

/*
 *      Fonction qui effectue le traitement demander
 */
void wordTraitement(int tf, poubelle* p1){
    p1->fSortie = fopen(".\\ressources\\temp.txt", "w");
    printf("%s@\n", p1->line);
    char ch = ' ';
    int index = 0;
    while ((ch = getc ( p1->fSource )) != EOF ) { // parcours tant que pas fin de fichier
        if ( ch != '\n'){
            p1->line[index++] = ch; // insere à la suite tant que pas \n
            printf("%s || %c\n", p1->line, ch);
        }else {
            p1->line[index] = '\0'; // remplace \n par un \0 fin de chaine
            index=0;
            if(tf == 1){
                // WORDINSERT
                traitementInsert(p1);
            }else if(tf == 2){
                // WORDSUPPR
                traitementSuppr(p1);
            }else if(tf == 3){
                // FSCEARCH
                traitementSearch(p1);
            }
        }
        if((p1->resSearch == 1) && (tf == 3)){
            break;
        }
    }
    typeErr(tf, p1);
}


/*
 *      Fonction qui insert un mot
 *      dans le dictionnaire choisit
 *      Respect de l'ordre alphabétique
 */
void traitementInsert(poubelle* p2){
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
            p2->resSearch = 2; // Deja present = 2
        }else{
            fprintf(p2->fSortie, "%s\n", p2->line);
        }
    }
}


/*
 *      Fonction qui supprime un mot
 *      dans le dictionnaire choisit
 */
void traitementSuppr(poubelle* p2){
    if(strcmp(p2->words,p2->line) != 0) {
        fprintf(p2->fSortie, "%s\n", p2->line);
    }else{
        p2->resSearch = 1;
        printf("Suppression effectuer\n");
    }
}


/*
 *      Fonction qui cherche un mot
 *      dans le dictionnaire choisit
 */
void traitementSearch(poubelle* p2){
    if(p2->resSearch != 1){
            printf("DEBUG");
        if(strcmp(p2->line,p2->words) == 0) {
            printf("trouver");
            p2->resSearch = 1;
        }
    }
}

////////////////////////////////////////////////////////////////////////////
/*
 *      Supprime l'ancien fichier
 *      et renomme le fichier temp
 *      avec le nom de l'ancien fichier
 *      return 1 ou 0 si probleme
 */
unsigned int remplaceTempToDico(char* path, poubelle* p1){
    char* tmpPath = ".\\ressources\\temp.txt";
    fclose(p1->fSortie);
    fclose(p1->fSource);
    printf("%s|", path);
    printf("RM1 - %d\n", remove(path));
    printf("RN - %d\n", rename(tmpPath, path));
    printf("%s|", path);
    printf("%s|", tmpPath);
    printf("RM2 - %d\n", remove(tmpPath));
    return 1;   // OK
}
/////////////////////////////////////////////////////////////////////////////

/*
 *      Permet a l'utilisateur d'annuler
 *      la fonction
 *      Retourne 1 si OK
 *      Sinon 0
 */
unsigned int annulProcedure(char* carac){
    if ((strcmp(carac, "A") == 0) || (strcmp(carac, "a") == 0)){
        printf("Vous avez annule\n");
        return 1;
    }
    return 0;
}


/*
 *      Fonction qui affiche un texte différent
 */
void printPrompt(int nb){
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


/*
 *      Fonction qui gere les erreur de traitement
 */
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
