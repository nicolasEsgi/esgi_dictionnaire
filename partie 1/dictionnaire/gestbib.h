#ifndef GESTBIB_H_INCLUDED
#define GESTBIB_H_INCLUDED


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
unsigned int f_destroyer();


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

unsigned int fUse();



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
unsigned int wordInsert();


/*
 *      Fonction qui permet la suppression d'un mot dans le dictionnaire
 *      Ne prends rien en parametre
 *      Retourne 0 en cas d'erreur sinon 1
 */
unsigned int wordSuppr();

// -------------------------------------------------------------------------------

// trim les chaines de caract�re et
char * remove_spaces(const char *input, char *result);

// cherche un mot et printf si oui ou non le mot est dans le fichier
void fsearch (char * words,FILE *fp);

#endif // GESTBIB_H_INCLUDED
