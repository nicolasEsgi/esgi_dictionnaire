#ifndef GESTBIB_H_INCLUDED
#define GESTBIB_H_INCLUDED


typedef struct poubelle{
    char words[30]; //d'apres la source d'Ahmed
    char line[30];
    FILE* fSource;
    FILE* fSortie;
    int resSearch;
}poubelle;

/// Crée un fichier en prenant en paramètre le
/// le chemin du fichier
/// Exemple :
/// unsigned int i = f_create();
/// Retourne 1 si le fichier a été créé
/// En cas d'erreur, il retourn 0
unsigned int f_create();


/// Supprime un fichier en prenant en paramètre le
/// le chemin du fichier
/// Exemple :
/// unsigned int i = f_destroyer();
/// Retourne 1 si le fichier a été supprimé
/// En cas d'erreur, il retourn 0
unsigned int f_destroyer(char* path);

/*
 *      Menu principale
 */
void startMenu();


/*
 *      Fonction vérifie si l'éxistance du fichier (option r)
 *      Prend un FILE en paramètre
 *      Retourne 0 en cas d'erreur sinon 1
 */
unsigned int fExiste(FILE* fileToTest);




/*
 *      Fonction qui liste un repertoire
 *      Prends un DIR en paramètre
 *      Retourne 0 en cas d'erreur sinon 1
 */
unsigned int dListe(DIR* rep);



/*
 *      Permet d'utiliser un dico choisi a la main
 *      Prend aucun paramètre
 *      Retourne 0 en cas d'erreur sinon 1
 */

char* fUse();



/*
 *      Fonction qui permet de connaitre l'extension du fichier
 *      Prendre une chaine de caractère en paramètre
 *      Retourne une chaine de caractère (MALLOC pensez à free)
 */

char* fNameDecoupage(char* str);



/*
 *      Fonction principale pour les traitements suivant
 *      Insertion, suppresion de mots
 *      Recherche de mot
 *      Retourne 0 en cas d'erreur
 *      1 si tout est bon
 */
unsigned int mainWord(char* path, int typeFunc);


/*
 *      Supprime l'ancien fichier
 *      et renomme le fichier temp
 *      avec le nom de l'ancien fichier
 *      return 1 ou 0 si probleme
 */
unsigned int remplaceTempToDico(char* path, poubelle* p1);

/*
 *      Permet a l'utilisateur d'annuler
 *      la fonction
 *      Retourne 1 si OK
 *      Sinon 0
 */
unsigned int annulProcedure(char* carac);


/*
 *      Fonction qui cherche un mot
 *      dans le dictionnaire choisit
 */
void traitementSearch(poubelle* p2);


/*
 *      Fonction qui insert un mot
 *      dans le dictionnaire choisit
 *      Respect de l'ordre alphabétique
 */
void traitementInsert(poubelle* p2);

/*
 *      Fonction qui supprime un mot
 *      dans le dictionnaire choisit
 */
void traitementSuppr(poubelle* p2);

/*
 *      Fonction qui affiche un texte différent
 */
void printPrompt(int nb);

/*
 *      Fonction qui gere les erreur de traitement
 */
void typeErr(int tf, poubelle* p2);


/*
 *      Fonction qui effectue le traitement demander
 */
void wordTraitement(int tf, poubelle* p1);


/*
 *      Fonction qui test l'exitance
 *      et moment ou l'on saisit le mot
 *      Retourne 0 en cas d'erreur
 *      1 si tout est correct
 */
unsigned int wordsScan(char* path, int func, poubelle* p1);


// cherche un mot et printf si oui ou non le mot est dans le fichier

unsigned int fsearch (char * words, char * path);


#endif // GESTBIB_H_INCLUDED
