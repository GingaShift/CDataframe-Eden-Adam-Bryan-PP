#pragma once
#include <stdio.h>
#include "Colonne.h"
#include "Divers.h"

typedef struct Dataframe
{
    char titre[256];
    int taille;
    COLONNE** colonnes;
} DATAFRAME;

int ajouter_colonne(DATAFRAME* dataframe, const char* nom_colonne);

int obtenir_nombre_lignes(DATAFRAME* dataframe);

int ajouter_bloc_lignes_aux_colonnes(COLONNE** dataframe, int taille_dataframe, int num_colonne_a_ignorer);

int inserer_valeur_avec_gestion_memoire_data_colonnes_new(DATAFRAME* dataframe, int num_col, int valeur);

int nom_colonne_existe(COLONNE** dataframe, char* nom_colonne, int taille_CDataframe);

DATAFRAME creer_cdataframe(bool* dataframe_exists, const char* nom_dataframe);

int afficher_les_colonnes(COLONNE** dataframe, int taille_dataframe);

int afficher_noms_colonnes(DATAFRAME dataframe);

int afficher_cdataframe(DATAFRAME* dataframe);

int modifier_valeur(DATAFRAME* dataframe, int num_col, int num_ligne, int valeur);

int renommer_colonne(DATAFRAME* dataframe, int num_colonne, const char* nouveau_nom);