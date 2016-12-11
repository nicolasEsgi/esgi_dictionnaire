#ifndef GESTBIB_H_INCLUDED
#define GESTBIB_H_INCLUDED


typedef struct poubelle{
    char words[30]; //d'apres la source d'Ahmed
    char line[30];
    FILE* fSource;
    FILE* fSortie;
    int resSearch;
}poubelle;

/// Cr�e un fichier en prenant en param�tre le
/// le chemin du fichier
/// Exemple :
/// unsigned int i = f_create();
/// Retourne 1 si le fichier a �t� cr��
/// En cas d'erreur, il retourn 0
unsigned int f_create();


/// Supprime un fichier en prenant en param�tre le
/// le chemin du fichier
/// Exemple :
/// unsigned int i = f_destroyer();
/// Retourne 1 si le fichier a �t� supprim�
/// En cas d'erreur, il retourn 0
unsigned int f_destroyer(char* path);


// -------------------------------------------------

void startMenu();


/*
 *      Fonction v�rifie si l'�xistance du fichier (option r)
 *      Prend un FILE en param�tre
 *      Retourne 0 en cas d'erreur sinon 1
 */
unsigned int fExiste(FILE* fileToTest);




/*
 *      Fonction qui liste un repertoire
 *      Prends un DIR en param�tre
 *      Retourne 0 en cas d'erreur sinon 1
 */
unsigned int dListe(DIR* rep);



/*
 *      Permet d'utiliser un dico choisi a la main
 *      Prend aucun param�tre
 *      Retourne 0 en cas d'erreur sinon 1
 */

char* fUse();



/*
 *      Fonction qui permet de connaitre l'extension du fichier
 *      Prendre une chaine de caract�re en param�tre
 *      Retourne une chaine de caract�re (MALLOC pensez � free)
 */

char* fNameDecoupage(char* str);



/*
 *      Fonction qui permet l'insertion d'un mot dans le dictionnaire
 *      Ne prends rien en parametre
 *      Retourne 0 en cas d'erreur sinon 1
 */
unsigned int wordInsert(char* path);


/*
 *      Fonction qui permet la suppression d'un mot dans le dictionnaire
 *      Ne prends rien en parametre
 *      Retourne 0 en cas d'erreur sinon 1
 */
unsigned int wordSuppr(char* path);

/*
 *      Supprime l'ancien fichier
 *      et renomme le fichier temp
 *      avec le nom de l'ancien fichier
 *      return 1 ou 0 si probleme
 */
unsigned int remplaceTempToDico(char* path, poubelle* p1);

/*
 *      Permet a l'utilisateur d'annuler
 *      la foncrtion
 *      Retourne 1 si OK
 *      Sinon 0
 */
unsigned int annulprocedure(char* carac);

/*
 *      D�but des fonction wordInsert et wordSuppr
 */
unsigned int jeSaisPasCommentLappeller(char* path, int func);

void partSearch(poubelle* p2);

void partWordInsert(poubelle* p2);

void partWordSuppr(poubelle* p2);

void escro(int nb);

void typeErr(int tf, poubelle* p2);

void laSuite(int tf, poubelle* p1);

unsigned int jPP(char* path, int func, poubelle* p1);

unsigned int wordSearch(char* path);

// -------------------------------------------------------------------------------

// cherche un mot et printf si oui ou non le mot est dans le fichier

unsigned int fsearch (char * words, char * path);


#endif // GESTBIB_H_INCLUDED
