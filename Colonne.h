#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOMBRE_LIGNES_PAR_BLOC 256
#define VALEUR_PAR_DEFAUT_DATA_COLONNE NULL

typedef struct Colonne
{
    char nom[255];
    int* data;
    int taille_physique;
    int taille_logique;
} COLONNE;

COLONNE* creer_colonne(const char* nom);

int ajouter_colonne(COLONNE*** dataframe, int* taille_dataframe, const char* nom_colonne);

void afficher_colonne(COLONNE** dataframe, int taille_dataframe, int indice_colonne);

void renommer_colonne(COLONNE** dataframe, int taille_dataframe, int indice_colonne, const char* nouveau_nom);
