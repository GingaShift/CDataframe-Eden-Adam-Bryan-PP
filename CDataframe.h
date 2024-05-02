#pragma once
#include <stdio.h>
#include "Colonne.h"
#include "Divers.h"

#define NOMBRE_CHAR_MAX_NOM_DATAFRAME 256

typedef struct Dataframe
{
    char titre[NOMBRE_CHAR_MAX_NOM_DATAFRAME];
    int taille;
    COLONNE** colonnes;
} DATAFRAME;

int ajouter_colonne(DATAFRAME* dataframe, const char* nom_colonne);

int obtenir_nombre_lignes(DATAFRAME* dataframe);

int egaliser_taille_des_tabs_data_des_colonnes(DATAFRAME* dataframe);

int inserer_valeur_avec_gestion_memoire_data_colonnes(DATAFRAME* dataframe, int num_col, int valeur);

int nom_colonne_existe(COLONNE** colonne, char* nom_colonne, int taille_CDataframe);

DATAFRAME* creer_cdataframe(bool* dataframe_exists, const char* nom_dataframe);

int afficher_les_colonnes(COLONNE** dataframe, int taille_dataframe);

int afficher_noms_colonnes(DATAFRAME* dataframe);

int afficher_cdataframe(DATAFRAME* dataframe, int num_col_max, int int_num_ligne_max);

int modifier_valeur(DATAFRAME* dataframe, int num_col, int num_ligne, int valeur);

int renommer_colonne(DATAFRAME* dataframe, int num_colonne, const char* nouveau_nom);

int afficher_valeur(DATAFRAME* dataframe, int num_col, int num_ligne);

int remplacer_valeur(DATAFRAME* dataframe, int num_col, int num_ligne, int new_val);

int supprimer_colonne_du_cdataframe(DATAFRAME* dataframe, int num_col);

int afficher_nombre_colonnes(DATAFRAME* dataframe);
