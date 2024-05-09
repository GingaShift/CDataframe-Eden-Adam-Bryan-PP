#pragma once
#include <stdio.h>
#include "Colonne.h"
#include "Divers.h"

#define NOMBRE_CHAR_MAX_NOM_DATAFRAME 256
#define TAILLE_MAX_STRING 256

#pragma region CDataframe 1

typedef struct Dataframe1
{
    char titre[NOMBRE_CHAR_MAX_NOM_DATAFRAME];
    int taille;
    COLONNE** colonnes;
} DATAFRAME1;

DATAFRAME1* creer_cdataframe(bool* dataframe_exists, const char* nom_dataframe);

int ajouter_colonne(DATAFRAME1* dataframe, const char* nom_colonne);

int renommer_colonne(DATAFRAME1* dataframe, int num_colonne, const char* nouveau_nom);

int supprimer_colonne(DATAFRAME1* dataframe, int num_col);

int nom_colonne_existe(DATAFRAME1* dataframe, char* nom_colonne, int taille_CDataframe);

int inserer_valeur_avec_gestion_memoire_data_colonnes(DATAFRAME1* dataframe, int num_col, int valeur);

int egaliser_taille_des_tabs_data_des_colonnes(DATAFRAME1* dataframe);

int afficher_nombre_colonnes(DATAFRAME1* dataframe);

int afficher_noms_colonnes(DATAFRAME1* dataframe);

int afficher_les_colonnes(DATAFRAME1* dataframe);

int afficher_cdataframe(DATAFRAME1* dataframe, int num_col_max, int int_num_ligne_max);

int obtenir_nombre_lignes(DATAFRAME1* dataframe);

int modifier_valeur(DATAFRAME1* dataframe, int num_col, int num_ligne, int valeur);

int afficher_valeur(DATAFRAME1* dataframe, int num_col, int num_ligne);

int ajouter_valeur_par_utilisateur(DATAFRAME1* dataframe, int num_col, int valeur);

#pragma endregion Fin CDataframe 1

#pragma region CDataframe 2

typedef struct Dataframe2
{
    char title[NOMBRE_CHAR_MAX_NOM_DATAFRAME];
    int size;
    COLUMN** columns;
} DATAFRAME2;

DATAFRAME2* create_cdataframe(bool* dataframe_exists, char* dataframe_title);

int add_column(DATAFRAME2* dataframe, ENUM_TYPE column_type, const char* column_title);

int rename_column(DATAFRAME2* dataframe, int column_num, char* new_name);

// TODO:
//int supprimer_colonne(DATAFRAME1* dataframe, int num_col);

int column_name_exists(DATAFRAME2* dataframe, char* column_name);

//int inserer_valeur_avec_gestion_memoire_data_colonnes(DATAFRAME1* dataframe, int num_col, int valeur);
//
//int egaliser_taille_des_tabs_data_des_colonnes(DATAFRAME1* dataframe);
//
//int afficher_nombre_colonnes(DATAFRAME1* dataframe);
//
//int afficher_noms_colonnes(DATAFRAME1* dataframe);
//
//int afficher_les_colonnes(DATAFRAME1* dataframe);
//
//int afficher_cdataframe(DATAFRAME1* dataframe, int num_col_max, int int_num_ligne_max);
//
//int obtenir_nombre_lignes(DATAFRAME1* dataframe);
//
//int modifier_valeur(DATAFRAME1* dataframe, int num_col, int num_ligne, int valeur);
//
//int afficher_valeur(DATAFRAME1* dataframe, int num_col, int num_ligne);
//
//int ajouter_valeur_par_utilisateur(DATAFRAME1* dataframe, int num_col, int valeur);
//
//int delete_column(DATAFRAME2* dataframe, int num_col);

#pragma endregion Fin CDataframe 2