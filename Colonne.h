#pragma once
#pragma once
#include <stdbool.h>
// #ifndef COLONNE_H
// #define COLONNE_H

#define NOMBRE_LIGNES_PAR_COLONNE 16 //256
#define VALEUR_PAR_DEFAUT_DATA_COLONNE NULL

typedef struct Colonne
{
    char nom[255];
    int data[NOMBRE_LIGNES_PAR_COLONNE];
    int taille_physique;
    int taille_logique;
} COLONNE;

//#endif /* COLONNE_H */

COLONNE CreerColonne(char* nom);

bool IniValeursColonne(COLONNE* col);

void AfficherColonne(COLONNE col);

void InsererValeurDansColonne();

void RechercherValeurDansColonne(COLONNE col, int valeur);

