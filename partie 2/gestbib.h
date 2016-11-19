#ifndef GESTBIB_H_INCLUDED
#define GESTBIB_H_INCLUDED

#include "gestbib.h"

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

unsigned int fExiste(FILE* fileToTest);

#endif // GESTBIB_H_INCLUDED
