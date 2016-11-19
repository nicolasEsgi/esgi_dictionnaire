#ifndef GESTBIB_H_INCLUDED
#define GESTBIB_H_INCLUDED

#include "gestbib.h"

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
unsigned int f_destroyer();

unsigned int fExiste(FILE* fileToTest);

#endif // GESTBIB_H_INCLUDED
